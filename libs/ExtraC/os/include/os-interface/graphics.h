#pragma once
#include "../extern.h"

Type(VideoMode,
	u32 width;
	u32 height;
	u16 refreshRate;
)

#define VIDEO_IN
#define VIDEO_OUT

typedef bool videoDirection;

Type(graphicsDevice,
	inst(String) name;
	inst(String) manufacturer;
	inst(String) model;

	void* uniqueID;
     	
	videoDirection direction;

	u32 currentMode;
	VideoMode* supportedModes;

	union{
	  struct{
		u16 dpi;
		u16 bitDepth;
		u16 rotation;
	
		bool primary;
	  } display;
	  struct{
		


	  } video;
	} info;


)
typedef void* graphicsHandle;

Interface(graphics,
	errvt 			vmethod(initSystem);
	errvt 			vmethod(exitSystem);
	graphicsHandle 		vmethod(initDisplay, 	 u32 x, u32 y, u32 w, u32 h, graphicsHandle parent);
	graphicsHandle 		vmethod(grabDevice, 	 graphicsDevice* device);
	arry(graphicsDevice) 	vmethod(enumDevices, 	 u64* numDevices);
	errvt	 		vmethod(closeDisplay,    graphicsHandle handle);
	errvt	 		vmethod(updateDisplay,   graphicsHandle handle, u32 x, u32 y, u32 w, u32 h, graphicsHandle parent);
	bool	 		vmethod(isDisplayClosed, graphicsHandle);
	errvt			vmethod(startVideo, 	 graphicsHandle handle);
	errvt			vmethod(stopVideo,  	 graphicsHandle handle);
	errvt			vmethod(closeVideo, 	 graphicsHandle handle);
	errvt			vmethod(pullVideoFrame,	 graphicsHandle handle);
	errvt 		  	vmethod(handleEvents,    graphicsHandle handle, Queue(OSEvent) evntQueue);
	u64 		  	vmethod(pollEvents);
)

Enum(displayEventType,
    DISPLAY_EVENT_RESIZE,	
    DISPLAY_EVENT_CLOSE,	
    DISPLAY_EVENT_VISIBILITY,	
)
Type(displayEvent,
    graphicsHandle handle;
 	displayEventType type;
)

Enum(videoEventType,
    VIDEO_EVENT_NEWFRAME,
)
Type(videoEvent,
    graphicsHandle handle;
 	videoEventType type;
)
