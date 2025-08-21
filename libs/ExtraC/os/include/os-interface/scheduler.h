#pragma once
#include "../extern.h"

typedef void* threadHandle;
typedef void* mutexHandle;
typedef void* semaphoreHandle;
typedef void* processHandle;

#define PROCFLAG_DEBUG 0x01


Enum(processEvent_Type,
	processEvent_Breakpoint,
	processEvent_Exception,
	processEvent_CreateProcess,
	processEvent_ExitProcess,
	processEvent_LoadLib,
	processEvent_UnloadLib
);

Type(processEvent,
	processHandle handle;
	processEvent_Type type;
     	union {
     		struct {void* address;} breakpoint;
	 

     	}data;
)
typedef struct {

} ProcessEvent;


Interface(scheduler,
	const cstr stdVersion;
	namespace(flags,
		int PROC_DEBUG;
	)
	errvt 		vmethod(initSystem);
	errvt 		vmethod(exitSystem);
	noFail 		vmethod(sleep, 		  u64 millisec);
	threadHandle  	vmethod(newThread,  	  void fn(thread_start, void* args), void* args);
	errvt 		vmethod(exitThread, 	  threadHandle handle);
	errvt 		vmethod(waitThread, 	  threadHandle handle);
	threadHandle 	vmethod(getCurrentThread);
	processHandle 	vmethod(newProcess,  	  cstr exePath, cstr args, u32 flags);
	errvt 		vmethod(killProcess, 	  processHandle handle);
	bool 		vmethod(isProcessRunning, processHandle handle);
	errvt 		vmethod(handleThrdEvents, threadHandle handle, Queue(OSEvent) evntQueue);
	errvt 		vmethod(handleProcEvents, processHandle handle, Queue(OSEvent) evntQueue);
	u64  	 	vmethod(pollEvents);
	struct {
		errvt 		vmethod(readProcessMem,    processHandle handle, void* address, void* buffer, size_t size);
		errvt 		vmethod(writeProcessMem,   processHandle handle, void* address, void* buffer, size_t size);
		errvt 		vmethod(continueProcess,   processHandle handle);
		errvt 		vmethod(detachProcess,     processHandle handle);
	} processUtils;
	struct {
		mutexHandle  	vmethod(newMutex);
		errvt 		vmethod(lockMutex,    	  mutexHandle handle);
		errvt 		vmethod(unlockMutex,  	  mutexHandle handle);
		errvt 		vmethod(tryLockMutex, 	  mutexHandle handle);
		errvt 		vmethod(destroyMutex, 	  mutexHandle handle);
		semaphoreHandle vmethod(newSemaphore, 	  size_t num);
		errvt 		vmethod(waitSemaphore, 	  semaphoreHandle handle);
		errvt 		vmethod(postSemaphore, 	  semaphoreHandle handle);
		errvt 		vmethod(tryWaitSemaphore, semaphoreHandle handle);
		errvt 		vmethod(destroySemaphore, semaphoreHandle handle);
	}threadUtils;
)
