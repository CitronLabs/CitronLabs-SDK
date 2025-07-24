#pragma once
#include "../../APIs/XC/core.h"
#include "types.h"
/*--------------------------------------|
	      File System		|
--------------------------------------*/
#define FS_DIR true
#define FS_FILE false

typedef void* fsHandle;
typedef char fsPath[256];
Type(fsEntry,
	bool is_dir;
	char name[256];
	size_t size;
	inst(Time) time_created;
	inst(Time) time_modified;
)

Interface(filesys,
	const int CREATE_FLAG, APPEND_FLAG, WRITE_FLAG, READ_FLAG, ASYNC_FLAG;
	fsHandle vmethod(open,    bool DIR, fsPath path, int flags);
	i64 	 vmethod(write,   fsHandle handle, pntr data, size_t size);
	i64 	 vmethod(read,    fsHandle handle, pntr data, size_t size);
	errvt 	 vmethod(search,  fsPath path, fsEntry* ent);
	errvt  	 vmethod(close,   fsHandle handle);
	errvt  	 vmethod(delete,  fsPath path);
	errvt  	 vmethod(chdir,   fsPath path);
)

/*--------------------------------------|
	      User Input		|
--------------------------------------*/

typedef void* inputHandle;

Type(keyInput,
     	inst(String) locale;	
	chartype encoding;
)
Enum(posRangeType,
     	POS_NULL,
	POS_VECTOR,
     	POS_EXACT,
     	POS_STATEFUL
)

Type(posInput,
	u8 dimension  : 2;
     	posRangeType type : 2;
	float low;
	float high;
)
	  
Type(inputDevice,
	inst(String) name;
	inst(String) uniqueID;
	u16 vendorID, productID;
     	u16 num_posInputs;
     	u16 num_keyInputs;
     	arry(posInput) posInputs;
     	arry(keyInput) keyInputs;
)
Type(inputEvent,
	bool type;
     	union {
	  struct{
		float axis[3];
	  	u16 ID;
	  }pos;
     	}data;

)
Interface(input,
#define AXIS_X 0
#define AXIS_Y 1
#define AXIS_Z 2
	errvt vmethod(clearEvents,      inputHandle handle);
	errvt vmethod(popEvent,         inputHandle handle, inputEvent* evnt);
	errvt vmethod(pushEvent,        inputHandle handle, inputEvent* evnt);
	bool  vmethod(checkEvent,	inputHandle handle);
	errvt vmethod(setEventCallback, inputHandle handle, void fn(evntCallback, inputEvent, inputDevice*, void*), void* userData);
	errvt vmethod(freeDevice,       inputHandle handle);
	inputHandle vmethod(grabDevice, inputDevice* dev);
	arry(inputDevice) vmethod(enumDevices, u64* numDevices);
)

/*--------------------------------------|
	        Graphics		|
--------------------------------------*/
Type(displayDevice,
	inst(String) name;
	inst(String) uniqueID;
     	u32 width, height;
     	u16 dpi;
     	u16 refreshRate;
)
typedef void* displayHandle;

Interface(graphics,
	errvt vmethod(setDestructor, displayHandle handle, void fn(destructor, displayHandle, pntr), pntr userData);
	displayHandle vmethod(initDisplay, u32 x, u32 y, u32 w, u32 h, displayHandle parent);
	displayHandle vmethod(grabDevice, displayDevice* device);
	arry(displayDevice) vmethod(enumDevices, u64* numDevices);
)
Interface(audio,)

typedef void* threadHandle;
typedef void* mutexHandle;
typedef void* semaphoreHandle;
typedef void* processHandle;

Interface(scheduler,
	threadHandle  vmethod(newThread, void fn(thread_start, void* args), void* args);
	processHandle vmethod(newProcess, cstr exePath, cstr args);
	errvt vmethod(killProcess, processHandle handle);
	void vmethod(sleep, u64 millisec);
	mutexHandle  vmethod(newMutex);
	mutexHandle  vmethod(lockMutex);
	mutexHandle  vmethod(unlockMutex);
	mutexHandle  vmethod(tryLockMutex);
	semaphoreHandle  vmethod(newSemaphore);
	semaphoreHandle  vmethod(waitSemaphore);
	semaphoreHandle  vmethod(postSemaphore);
	semaphoreHandle  vmethod(tryWaitSemaphore);
)

typedef void* dynlibHandle;
Interface(memory,
	void* 		vmethod(newMemory, u64 numPages, u16 flags);
	errvt 		vmethod(updateMemory, void* memoryBlock, u16 flags);
	errvt 		vmethod(freeMemory, void* memoryBlock);
	u32 		vmethod(getPageSize);
	dynlibHandle 	vmethod(loadDynLib, cstr path);
	void* 		vmethod(findSymbol, dynlibHandle handle);
	errvt 		vmethod(unloadDynLib, dynlibHandle handle);
)
Interface(network,)
Interface(terminal,)
Interface(disk,)


Interface(OS,
	interface(filesys);
	interface(input);
	interface(graphics);
	interface(audio);
	interface(scheduler);
	interface(memory);
	interface(network);
	interface(terminal);
	interface(disk);
);



extern intf(OS) userOS;

