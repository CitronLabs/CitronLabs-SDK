#include "__systems.h"

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

errvt vmethodimpl(LinuxEnv_FileSys, close, fsHandle handle){
	if(handle == (fsHandle)0 || handle == (fsHandle)1 || handle == (fsHandle)2) 
		return ERR(ERR_INVALID, "cannot close the stdout, stdin, or stderr");
	if((close(addrasval(handle))) == -1){
		switch (errno) {
		
		}
	}
return OK;
}

errvt vmethodimpl(LinuxEnv_FileSys, search, fsPath path, fsEntry* entry){
	nonull(path, return nullerr);

	struct stat statbuf;
	if(stat(path, &statbuf) == -1){
		switch (errno) {
		
		}
	}

	if(entry == NULL) return OK;

	inst(Time) time_buff = {0};

	entry->is_dir = S_ISDIR(statbuf.st_mode);
	
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

errvt vmethodimpl(LinuxEnv_FileSys, delete, fsPath path){
	nonull(path, return nullerr)	
	if(-1 == remove(path)){
		switch (errno) {
		
		}	
	}
return OK;
}
i64 vmethodimpl(LinuxEnv_FileSys, read, fsHandle handle, void* buff, u64 size){
	nonull(buff, return nullerr)
	u64 bytesread = 0;
	if(-1 == (bytesread = read(addrasval(handle), buff, size))){
		switch (errno) {
		
		}	
	}
return bytesread;
}
i64 vmethodimpl(LinuxEnv_FileSys, write, fsHandle handle, void* buff, u64 size){
	nonull(buff, return nullerr)
	u64 byteswritten = 0;
	if(-1 == (byteswritten = write(addrasval(handle), buff, size))){
		switch (errno) {
		
		}	
	}
return byteswritten;
}
errvt vmethodimpl(LinuxEnv_FileSys, chdir, fsPath path){
	nonull(path, return nullerr)
	if(-1 == chdir(path)){
		switch (errno) {
		
		}	
	}
return OK;
}

const ImplAs(filesys, LinuxFS){
	.WRITE_FLAG = O_WRONLY,
	.ASYNC_FLAG = O_NONBLOCK,
	.READ_FLAG = O_RDONLY,
	.CREATE_FLAG = O_CREAT,
	.APPEND_FLAG = O_APPEND,
	.open = LinuxEnv_FileSys_open,
	.close = LinuxEnv_FileSys_close,
	.search = LinuxEnv_FileSys_search,
	.delete = LinuxEnv_FileSys_delete,
	.read = LinuxEnv_FileSys_read,
	.write = LinuxEnv_FileSys_write,
	.chdir = LinuxEnv_FileSys_chdir
};
