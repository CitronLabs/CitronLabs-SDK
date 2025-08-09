#include "../include/extern.h"
#include "systems/filesys.c"
#include "systems/network.c"
#include "systems/graphics.c"
#include "systems/scheduler.c"

defaultOS(LinuxEnv.OS)

errvt initOSEnv(){
		

}

Impl(LinuxEnv){
    .OS = {
	.OSName = "Linux",
	.initOSBackend 	= initOSEnv,
	.filesys 	= LinuxFS,
	.network 	= LinuxNetwork,
	.scheduler 	= LinuxScheduler,
	.graphics 	= LinuxGraphics,	
	.memory 	= LinuxMemory,
	.input 		= LinuxInput,
	.terminal 	= LinuxTerminal,
	.audio 		= LinuxAudio
    }
};
