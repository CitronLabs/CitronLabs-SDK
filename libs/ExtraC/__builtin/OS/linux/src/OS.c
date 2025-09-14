#include "../include/extern.h"
#include "systems/network.c"
#include "systems/filesys.c"
#include "systems/scheduler.c"
#include "systems/graphics.c"
#include "systems/memory.c"

errvt initLinuxEnv(){
	
	OSDevices = new(OSDeviceManager,
		// OS Device Manager Config Settings Here	
	);

	iferr(initVideoInputSystem()){
		return err;
	}

return OK;
}

errvt exitLinuxEnv(){
		

}

Impl(OS){
	.OSName = "Linux",
	.initOS 	= initLinuxEnv,
	.exitOS 	= exitLinuxEnv,
	.storage 	= LinuxFS,
	.network 	= LinuxNetwork,
	.scheduler 	= LinuxScheduler,
	.graphics 	= LinuxGraphics,	
	.memory 	= LinuxMemory,
	.input 		= LinuxInput,
	.user 		= LinuxUser,
	.audio 		= LinuxAudio
   
};
