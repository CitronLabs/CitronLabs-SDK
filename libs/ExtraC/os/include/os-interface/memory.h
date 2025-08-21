#pragma once
#include "../extern.h"


#define MEM_READ    1
#define MEM_WRITE   2
#define MEM_EXECUTE 4
#define MEM_RESERVE 8
#define MEM_SHARED  16


Type(systemMemoryInfo,
    size_t total_Physical_Memory;
    size_t total_Virtual_Memory;
    size_t available_Physical_Memory;
    size_t available_Virtual_Memory;	
)

Type(memoryInfo,
	u16 flags;
     	size_t size;
     	u64 alignment;
     	void* address;
)

typedef void* dynlibHandle;
typedef void* memoryHandle;
Interface(memory,
	const cstr stdVersion;
	errvt 		vmethod(initSystem);
	errvt 		vmethod(exitSystem);
	// the MEM_SHARED flag is set then at Address refers to the path where the shared memory object is going to be stored
	memoryHandle	vmethod(openMemory,   cstr memObjPath);
	memoryHandle	vmethod(newMemory,    void* atAddress, size_t size, u16 flags, u64 alignment);
	memoryHandle	vmethod(mapMemory,    void* atAddress, size_t size, u16 flags, memoryHandle handle);
	u64		vmethod(getSize,      memoryHandle handle);
	errvt 		vmethod(setMemProt,   memoryHandle handle, u16 flags);
	errvt 		vmethod(setMemSize,   memoryHandle handle, size_t newSize);
	errvt 		vmethod(freeMemory,   memoryHandle handle);
	errvt 		vmethod(watchMemory,  memoryHandle handle);
	errvt 		vmethod(setSwappable, memoryHandle handle, bool swappable);
	u32 		vmethod(getPageSize);
	errvt 		vmethod(getSystemInfo,systemMemoryInfo* info);
	errvt 		vmethod(getMemoryInfo,memoryHandle handle, memoryInfo* info);
	void*		vmethod(getAddress,   memoryHandle handle);
	dynlibHandle 	vmethod(loadDynLib,   cstr path);
	void* 		vmethod(findSymbol,   dynlibHandle handle, cstr symbol);
	errvt 		vmethod(unloadDynLib, dynlibHandle handle);
	errvt 		vmethod(handleEvents, dynlibHandle handle, Queue(OSEvent) evntQueue);
	u64  	 	vmethod(pollEvents);
)
