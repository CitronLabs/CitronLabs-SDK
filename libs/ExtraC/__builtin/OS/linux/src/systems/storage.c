#include "__systems.h"

storageHandle vmethodimpl(LinuxStorage, fs_open, bool DIR, fsPath path, int flags){
	
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
return (storageHandle)(u64)fd;
}

errvt vmethodimpl(LinuxStorage, fs_search, fsPath path, fsEntry* entry){
	nonull(path, return err);

	struct stat statbuf;
	if(stat(path, &statbuf) == -1){
		switch (errno) {
		
		}
	}

	if(entry == NULL) return OK;

	inst(Time) time_buff = {0};

	entry->type.is.dir = S_ISDIR(statbuf.st_mode);
	
	Time.FromCTime(time_buff, statbuf.st_ctim);
	entry->time_created = time_buff;

	Time.FromCTime(time_buff, statbuf.st_mtim);
	entry->time_modified = time_buff;

	u32 nameoffset = 0, pathlen = strnlen(path, 255);
	
	loop(i, pathlen){
	   if(path[pathlen - i] == '/'){
		nameoffset = pathlen - i + 1;
		break;
	   }
	}
	loop(i, pathlen - nameoffset)
		entry->name[i] = path[nameoffset + i];
return OK;
}

errvt vmethodimpl(LinuxStorage, fs_delete, fsPath path){
	nonull(path, return err)	
	if(-1 == remove(path)){
		switch (errno) {
		
		}	
	}
return OK;
}
i64 vmethodimpl(LinuxStorage, read, storageHandle handle, void* buff, u64 size){
	nonull(buff, return err)
	u64 bytesread = 0;
	if(-1 == (bytesread = read(addrasval(handle), buff, size))){
		switch (errno) {
		
		}	
	}
return bytesread;
}





i64 vmethodimpl(LinuxStorage, write, storageHandle handle, void* buff, u64 size){
	nonull(buff, return err)
	u64 byteswritten = 0;
	if(-1 == (byteswritten = write(addrasval(handle), buff, size))){
		switch (errno) {
		
		}	
	}
return byteswritten;
}
errvt vmethodimpl(LinuxStorage, fs_chdir, fsPath path){
	nonull(path, return err)
	if(-1 == chdir(path)){
		switch (errno) {
		
		}	
	}
return OK;
}

errvt vmethodimpl(LinuxStorage, close, storageHandle handle){
	if(handle == (storageHandle)0 || handle == (storageHandle)1 || handle == (storageHandle)2) 
		return ERR(ERR_INVALID, "cannot close the stdout, stdin, or stderr");
	if((close(addrasval(handle))) == -1){
		switch (errno) {
		
		}
	}
return OK;
}


const ImplAs(storage, LinuxStorage){
    .fs = {
	.flags = {
	  .WRITE 	= O_WRONLY,
	  .ASYNC 	= O_NONBLOCK,
	  .READ 	= O_RDONLY,
	  .CREATE 	= O_CREAT,
	  .APPEND 	= O_APPEND,
	},
	.open 	= LinuxStorage_fs_open,
	.search = LinuxStorage_fs_search,
	.delete = LinuxStorage_fs_delete,
	.chdir 	= LinuxStorage_fs_chdir
    },
	.close 	= LinuxStorage_close,
	.read 	= LinuxStorage_read,
	.write 	= LinuxStorage_write,
};
