#include "extern.h"
#include "OS.h"
#include "filesys.c"
#include "network.c"
#include "graphics.c"
#include "scheduler.c"
intf(OS) userOS = &LinuxEnv.OS;


Impl(LinuxEnv){
    .OS = {
	.filesys = LinuxFS,
	.network = LinuxNetwork,
	.scheduler = LinuxScheduler,
	.graphics = LinuxGraphics	
    }
};
