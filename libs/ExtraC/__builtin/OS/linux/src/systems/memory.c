#include "__systems.h"
#include <fcntl.h>
#include <sys/mman.h>
#include <dlfcn.h>
#include <sys/stat.h>

static u32 Linux_PageSize = 4096;

errvt vmethodimpl(LinuxMemory, initSystem) {
	i32 result = -1;
	if((result = sysconf(_SC_PAGESIZE)) == -1) {
		switch (errno) {
	    
		};
	}
	Linux_PageSize = (u32)result;

return OK;
}

errvt vmethodimpl(LinuxMemory, exitSystem) {
return OK;
}


u32 vmethodimpl(LinuxMemory, getPageSize) {
return Linux_PageSize;
}

void* vmethodimpl(LinuxMemory, newMemory, void* atAddress, u64 numPages, u16 flags){
	
	int prot = 0;
	    
	if (flags & MEM_READ) { prot |= PROT_READ; }
	if (flags & MEM_WRITE) { prot |= PROT_WRITE; }
	if (flags & MEM_EXECUTE) { prot |= PROT_EXEC; }
	
	int mapFlags = MAP_PRIVATE | MAP_ANONYMOUS;
	if (atAddress != NULL) {
	    	mapFlags |= MAP_FIXED;
	}
	
	size_t size = numPages * Linux_PageSize;
	void* result = mmap(atAddress, size, prot, mapFlags, -1, 0);
	
	if (result == MAP_FAILED) {
		switch (errno) {
		}
	    	return NULL;
	}
	
return result;
}




errvt vmethodimpl(LinuxMemory, updateMemory, void* memoryBlock,  u64 numPages, u16 flags) {
	int prot = 0;
	if (flags & MEM_READ) { prot |= PROT_READ; }
	if (flags & MEM_WRITE) { prot |= PROT_WRITE; }
	if (flags & MEM_EXECUTE) { prot |= PROT_EXEC; }
	
	if (mprotect(memoryBlock, numPages * Linux_PageSize, prot) == -1) {
		switch(errno){
		};
	}
	
return OK; 
}

errvt vmethodimpl(LinuxMemory, freeMemory, void* memoryBlock, u64 numPages) {
	
	if (munmap(memoryBlock, numPages * Linux_PageSize) == -1) {
		switch(errno){
		};
	}

return OK; 
}

dynlibHandle vmethodimpl(LinuxMemory, loadDynLib, cstr path) {
	dynlibHandle result = dlopen(path, RTLD_LAZY);

	if(result == NULL){
		struct stat temp;
		if(stat(path, &temp) == -1)
			ERR(ERR_INVALID, "invalid dynamic lib path");
		else
			ERR(ERR_FAIL, "failed to load dynamic lib");
	}
return result;
}

void* vmethodimpl(LinuxMemory, findSymbol, dynlibHandle handle, cstr symbol) {
	void* result = dlsym(handle, symbol);
	
	if(result == NULL)
		ERR(ERR_INVALID, "could not find symbol");

return result;    
}

errvt vmethodimpl(LinuxMemory, unloadDynLib, dynlibHandle handle) {
	if (dlclose(handle) != 0) {
		switch(errno){
		};
	}
return OK;
}

errvt vmethodimpl(LinuxMemory, handleEvents, dynlibHandle handle, Queue(OSEvent) evntQueue) {
    
return OK;
}

ImplAs(memory, LinuxMemory){
	.initSystem 	= LinuxMemory_initSystem,
	.exitSystem 	= LinuxMemory_exitSystem,
	.newMemory 	= LinuxMemory_newMemory,
	.updateMemory 	= LinuxMemory_updateMemory,
	.freeMemory 	= LinuxMemory_freeMemory,
	.getPageSize 	= LinuxMemory_getPageSize,
	.loadDynLib 	= LinuxMemory_loadDynLib,
	.findSymbol 	= LinuxMemory_findSymbol,
	.unloadDynLib 	= LinuxMemory_unloadDynLib,
	.handleEvents 	= LinuxMemory_handleEvents
};
