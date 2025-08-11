#define Time 	_X11_Time
#define Display _X11_Display
#define Connection _X11_Connection
#include <X11/Xlib.h>
#include <X11/X.h>
#include <X11/extensions/Xrandr.h>
#include <X11/extensions/randr.h>
#include <X11/Xatom.h>
#undef Time
#undef Display
#undef Connection

#include "../systems/__systems.h"

typedef struct {
	u8 active : 1, init : 1;
	Window window;
}X11_Window;

static struct{
	u8 running : 1;
	u8 init : 1;
	struct _XDisplay* display;
	List(X11_Window) windows;
	List(displayDevice) screens;
}X11_EnvData;

static inline inst(String) getX11Property(struct _XDisplay* display, RROutput output, Atom property){
	char* prop;
	int format;
	u64 nitems, bytes_after;
	Atom actual_type;
	inst(String) result = NULL;
	
	if (XRRGetOutputProperty(display, output, property, 0, 100, False, False, AnyPropertyType,
	                         &actual_type, &format, &nitems, &bytes_after, (unsigned char**)&prop) == Success) {
	    if (nitems > 0) {
	        result = new(String, prop, UINT64_MAX);
	    }
	    XFree(prop);
	}

return result;
}

static inline DisplayMode* getSupportedModes(
	arry(XRRModeInfo) modes, 
	size_t len, 
	XRRCrtcInfo* crt, 
	DisplayMode** currentModeResult
){
	
	inst modesList = pushList(DisplayMode);
	i32 currentModeIndex = -1;

	loop(j, len){
		List.Append(modesList, &(DisplayMode){
			.height = modes[j].height,
			.width  = modes[j].width,
			.refreshRate = (u16)
				round((double)modes[j].dotClock /
				     ((double)modes[j].vTotal * (double)modes[j].hTotal)
				)
		}, 1);
		if(modes[j].id == crt->mode) currentModeIndex = j;
	}

	if(currentModeIndex != -1){

	}

	*currentModeResult = List.GetPointer(modesList, currentModeIndex);

return List.GetPointer(modesList, 0);
}

List(displayDevice) getDisplayDeviceList(){
	
	inst screens = newList(displayDevice);
	
      	u32 screensNum = XScreenCount(X11_EnvData.display);
	loop(s, screensNum){
	    Window screenRoot = RootWindow(X11_EnvData.display, s);
	    XRRScreenResources* screensSrcs = XRRGetScreenResources(
			X11_EnvData.display, 
			screenRoot
	    );

	    if(!screensSrcs) continue;

	    loop(i, screensSrcs->noutput){
		XRROutputInfo* out = XRRGetOutputInfo(
			X11_EnvData.display,
			screensSrcs, 
			screensSrcs->outputs[i]);

		if(out && out->connection == RR_Connected){
			displayDevice device = {0};
			XRRCrtcInfo* crt = XRRGetCrtcInfo(
				X11_EnvData.display, 
				screensSrcs,
				out->crtc);			
		
			device.name = new(String, out->name, out->nameLen);
			device.uniqueID = (pntr)(u64)s;
		
			populateDisplayDevInfo(device.name, &device);

			if(!device.model){
				device.model = getX11Property(
					X11_EnvData.display,
					screensSrcs->outputs[i],
					XInternAtom(X11_EnvData.display, "EDID_PRODUCT_ID", False)
				);
			}
			if(!device.manufacturer){
				device.model = getX11Property(
					X11_EnvData.display,
					screensSrcs->outputs[i],
					XInternAtom(X11_EnvData.display, "EDID_VERSION", False)
				);
			}
			if(!device.supportedModes){
				DisplayMode* currentMode = NULL;
				device.supportedModes = getSupportedModes(
					screensSrcs->modes, 
					screensSrcs->nmode,
					crt, &currentMode
				);
				if(currentMode != NULL){
					device.currentRefreshRate = currentMode->refreshRate;
					device.currentWidth  = currentMode->width;
					device.currentHeight = currentMode->height;
				}
			}
			if(!device.physicalHeight_mm)
				device.physicalHeight_mm = out->mm_height;

			if(!device.physicalWidth_mm)
				device.physicalWidth_mm = out->mm_width;

			if(!device.connectionType)
				device.connectionType = device.name;

			if(!device.bitDepth){
				XWindowAttributes attrbs;
				XGetWindowAttributes(
					X11_EnvData.display, 
					screenRoot, 
					&attrbs
				);
				device.bitDepth = (u16)attrbs.depth;
			}
			if(!device.dpi && device.physicalWidth_mm > 0) {
				const float mm_to_inch_mult_factor = 25.4f;
				device.dpi = (u16)
					round((device.currentWidth * mm_to_inch_mult_factor)
			    			/ device.physicalWidth_mm
	   			);
			}
			device.rotation = crt->rotation & RR_Rotate_90  ? 90  :
    					  crt->rotation & RR_Rotate_180 ? 180 :
    					  crt->rotation & RR_Rotate_270 ? 270 :
    					  0;
			device.primary = screensSrcs->outputs[i] == 
					XRRGetOutputPrimary(
						X11_EnvData.display, 
						screenRoot
					);

			XRRFreeOutputInfo(out);
			XRRFreeCrtcInfo(crt);

		}
	    }
	    XRRFreeScreenResources(screensSrcs);
      	}

return screens;
}

errvt vmethodimpl(LinuxEnv_Graphics, initSystem){
	if(X11_EnvData.init)
		return ERR(ERR_INITFAIL, "X11 already initialized");
	
	X11_EnvData.display = XOpenDisplay(NULL);
	
	if(X11_EnvData.display == NULL)
		return ERR(ERR_INITFAIL, "Failed to open display");
	
	Window root = DefaultRootWindow(X11_EnvData.display);
	
	if(root == None) {
		XCloseDisplay(X11_EnvData.display);
		return ERR(ERR_INITFAIL, "No root window found");
	}
	X11_EnvData.windows = newList(X11_Window, 
		(X11_Window){.window = root, .active = true, .init = true}
	);

	X11_EnvData.screens = getDisplayDeviceList();

	X11_EnvData.init = true;

return OK;
}
errvt vmethodimpl(LinuxEnv_Graphics, exitSystem){
	if(!X11_EnvData.init) 
		return ERR(ERR_FAIL, "display system not initialized");

	foreach(X11_EnvData.windows, X11_Window, win){
	    if(win.init)
		XDestroyWindow(X11_EnvData.display, win.window);
	}

	del(X11_EnvData.windows);

	XCloseDisplay(X11_EnvData.display);

	X11_EnvData.init = false;

return OK;
}

displayHandle vmethodimpl(LinuxEnv_Graphics, initDisplay, u32 x, u32 y, u32 w, u32 h, displayHandle parent){

	//if parent == NULL then the 0th X11_Window will be selected which is the root window
	X11_Window* parentData = List.GetPointer(X11_EnvData.windows, addrasval(parent));

	if(!parentData){
		ERR(ERR_INITFAIL, "could not find specified parent");
		return NULL;
	}

	Window parentWindow = parentData->window;

	X11_Window win = {
		.window = XCreateSimpleWindow(
			X11_EnvData.display,
			parentWindow,
			x, y, w, h,
			0,0,0x00000000
		)
	};
	if(win.window == None){
		ERR(ERR_INITFAIL, "could not create window");
		return NULL;
	}

	iferr(List.Append(X11_EnvData.windows, &win, 1)){
		XDestroyWindow(X11_EnvData.display, win.window);
		ERR(ERR_INITFAIL, "failed to append window to X11 window list");
		return NULL;
	}
	
	displayHandle result = (displayHandle)List.Size(X11_EnvData.windows);

return result;
}

displayDevice* vmethodimpl(LinuxEnv_Graphics, enumDisplayDevices, u64* num){
	nonull(num, return NULL);

	if(X11_EnvData.screens == NULL){
		X11_EnvData.screens = getDisplayDeviceList();
		if(X11_EnvData.screens == NULL){
			ERR(ERR_FAIL, "failed to enumerate display devices");
			return NULL;
		}
	}

	*num = List.Size(X11_EnvData.screens);

return List.GetPointer(X11_EnvData.screens, 0);
}

displayHandle vmethodimpl(LinuxEnv_Graphics, grabDisplayDevice, displayDevice* device){
	nonull(device, return NULL);
	
	X11_Window deviceWindow = {0};
	deviceWindow.window = RootWindow(X11_EnvData.display, addrasval(device->uniqueID));
	if(deviceWindow.window == None){
		ERR(ERR_INITFAIL, "could not get the window for this display device");
		return NULL;
	}
	
	deviceWindow.active = true;
	deviceWindow.init   = true;

	displayHandle result = (displayHandle)List.FillSlot(X11_EnvData.windows, &deviceWindow);

return result;
}

errvt vmethodimpl(LinuxEnv_Graphics, closeDisplay, displayHandle handle){
	nonull(handle, return nullerr);
	
	X11_Window* win = List.GetPointer(X11_EnvData.windows, addrasval(handle));
	
	if(!win)
		return ERR(ERR_INVALID, "invalid display handle");
	
	if(win->active){
		//close the window
	}

	win->init = false;

	XDestroyWindow(X11_EnvData.display, win->window);

	List.SetFree(X11_EnvData.windows, addrasval(handle));

return OK;
}

bool vmethodimpl(LinuxEnv_Graphics, isDisplayClosed, displayHandle handle){
	nonull(handle, return nullerr);
	
	X11_Window* win = List.GetPointer(X11_EnvData.windows, addrasval(handle));
	
	if(!win){
		ERR(ERR_INVALID, "invalid display handle");
		return -1;
	}

return win->active;
}
