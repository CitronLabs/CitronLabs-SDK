#pragma once
#include "../extern.h"

typedef void* threadHandle;
typedef void* mutexHandle;
typedef void* semaphoreHandle;
typedef void* processHandle;

#define PROCFLAG_DEBUG 0x01

Interface(scheduler,
	errvt 		vmethod(initSystem);
	errvt 		vmethod(exitSystem);
	threadHandle  	vmethod(newThread,  	  void fn(thread_start, void* args), void* args);
	errvt 		vmethod(exitThread, 	  threadHandle handle);
	errvt 		vmethod(waitThread, 	  threadHandle handle);
	threadHandle 	vmethod(getCurrentThread);
	errvt 		vmethod(handleThrdEvents, threadHandle handle, Queue(OSEvent) evntQueue);
	processHandle 	vmethod(newProcess,  	  cstr exePath, cstr args, u32 flags);
	errvt 		vmethod(killProcess, 	  processHandle handle);
	bool 		vmethod(isProcessRunning, processHandle handle);
	errvt 		vmethod(traceProcess,     processHandle handle);
	errvt 		vmethod(handleProcEvents, processHandle handle, Queue(OSEvent) evntQueue);
	void 		vmethod(sleep, 		  u64 millisec);
	mutexHandle  	vmethod(newMutex);
	errvt 		vmethod(lockMutex,    	  mutexHandle handle);
	errvt 		vmethod(unlockMutex,  	  mutexHandle handle);
	errvt 		vmethod(tryLockMutex, 	  mutexHandle handle);
	semaphoreHandle vmethod(newSemaphore, 	  size_t num);
	errvt 		vmethod(waitSemaphore, 	  semaphoreHandle handle);
	errvt 		vmethod(postSemaphore, 	  semaphoreHandle handle);
	errvt 		vmethod(tryWaitSemaphore, semaphoreHandle handle);
	u64  	 	vmethod(pollEvents);
)
