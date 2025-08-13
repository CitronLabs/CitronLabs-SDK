#pragma once
#include "../extern.h"


#define MEM_READ    1
#define MEM_WRITE   2
#define MEM_EXECUTE 4

typedef void* dynlibHandle;
Interface(memory,
	errvt 		vmethod(initSystem);
	errvt 		vmethod(exitSystem);
	void* 		vmethod(newMemory,    void* atAddress, u64 numPages, u16 flags);
	errvt 		vmethod(updateMemory, void* memoryBlock, u64 numPages, u16 flags);
	errvt 		vmethod(freeMemory,   void* memoryBlock, u64 numPages);
	u32 		vmethod(getPageSize);
	dynlibHandle 	vmethod(loadDynLib,   cstr path);
	void* 		vmethod(findSymbol,   dynlibHandle handle, cstr symbol);
	errvt 		vmethod(unloadDynLib, dynlibHandle handle);
	errvt 		vmethod(handleEvents, dynlibHandle handle, Queue(OSEvent) evntQueue);
	u64  	 	vmethod(pollEvents);
)
