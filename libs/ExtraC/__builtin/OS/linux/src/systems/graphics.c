#include "__systems.h"

#if 	__LinuxEnv_DisplayBackend == LinuxEnv_Display_X11
	#include "../backends/x11.c"
#elif 	__LinuxEnv_DisplayBackend == LinuxEnv_Display_Wayland
#endif


const ImplAs(graphics, LinuxGraphics){	
	.initSystem = LinuxEnv_Graphics_initSystem,
	.exitSystem = LinuxEnv_Graphics_exitSystem,
	.initDisplay = LinuxEnv_Graphics_initDisplay,
	.enumDisplays = LinuxEnv_Graphics_enumDisplayDevices,
	.grabDisplay = LinuxEnv_Graphics_grabDisplayDevice,
	.closeDisplay = LinuxEnv_Graphics_closeDisplay,
	.isDisplayClosed = LinuxEnv_Graphics_isDisplayClosed
};
