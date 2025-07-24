#include "os.h"
#include "types.h"
#include "utils.h"
#include <fcntl.h>

fsHandle vmethodimpl(LinuxEnv_FileSys, open, bool DIR, fsPath path, int flags){
	
	int fd = -1;

	if(getbitflag(flags, O_WRONLY) && getbitflag(flags, O_RDONLY)){
		flags ^= O_WRONLY;
		flags ^= O_RDONLY;
		flags |= O_RDWR;
	}

	if((fd = open(path, flags)) == -1){
		switch (errno) {
		
		}
	}
return (fsHandle)(u64)fd;
}


const ImplAs(filesys, LinuxFS){
	.WRITE_FLAG = O_WRONLY,
	.ASYNC_FLAG = O_NONBLOCK,
	.READ_FLAG = O_RDONLY,
	.CREATE_FLAG = O_CREAT,
	.APPEND_FLAG = O_APPEND,
	.open = LinuxEnv_FileSys_open,
	

};
