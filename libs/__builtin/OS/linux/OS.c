#include "extern.h"
#include "OS.h"
#include "filesys.c"
#include "network.c"
#include "graphics.c"
#include "scheduler.c"

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
