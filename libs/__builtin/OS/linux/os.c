#include "extern.h"
#include "os.h"
#include "filesys.c"

intf(OS) userOS = &LinuxEnv.OS;


Impl(LinuxEnv){
    .OS = {
	.filesys = LinuxFS 
    }
};
