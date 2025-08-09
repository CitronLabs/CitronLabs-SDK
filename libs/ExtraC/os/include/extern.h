#pragma once
#include "../../../APIs/XC/core.h"

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
	int CREATE_FLAG, APPEND_FLAG, WRITE_FLAG, READ_FLAG, ASYNC_FLAG;
	fsHandle vmethod(open,    bool DIR, fsPath path, int flags);
	i64 	 vmethod(write,   fsHandle handle, pntr data, size_t size);
	i64 	 vmethod(read,    fsHandle handle, pntr data, size_t size);
	errvt 	 vmethod(search,  fsPath path, fsEntry* ent);
	errvt  	 vmethod(close,   fsHandle handle);
	errvt  	 vmethod(delete,  fsPath path);
	errvt  	 vmethod(chdir,   fsPath path);
	errvt  	 vmethod(handleEvents, fsHandle handle, Queue(OSEvent) evntQueue);
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
Interface(input,
#define AXIS_X 0
#define AXIS_Y 1
#define AXIS_Z 2
	arry(inputDevice) vmethod(enumDevices, 	    u64* numDevices);
	errvt 		  vmethod(freeDevice,       inputHandle handle);
	inputHandle 	  vmethod(grabDevice, 	    inputDevice* dev);
	errvt 		  vmethod(handleEvents,     inputHandle handle, Queue(OSEvent) evntQueue);
)

/*--------------------------------------|
	        Graphics		|
--------------------------------------*/
Type(DisplayMode,
	u32 width;
	u32 height;
	u16 refreshRate;
)
Type(displayDevice,
	inst(String) name;
	inst(String) manufacturer;
	inst(String) model;
	
	inst(String) connectionType; // e.g., "HDMI-A-1", "DisplayPort-0"
	
	void* uniqueID;

	u32 currentWidth;
	u32 currentHeight;
	u16 currentRefreshRate;
	u16 dpi;
	u16 bitDepth;
	u16 rotation;
	
	u32 physicalWidth_mm;
	u32 physicalHeight_mm;
	
	DisplayMode* supportedModes;
	
	bool primary;
	bool HDRSupport;
)
typedef void* displayHandle;

Interface(graphics,
	errvt 			vmethod(initSystem);
	errvt 			vmethod(exitSystem);
	displayHandle 		vmethod(initDisplay, u32 x, u32 y, u32 w, u32 h, displayHandle parent);
	displayHandle 		vmethod(grabDisplay, displayDevice* device);
	arry(displayDevice) 	vmethod(enumDisplays, u64* numDevices);
	errvt	 		vmethod(closeDisplay, displayHandle handle);
	errvt	 		vmethod(updateDisplay, displayHandle handle, u32 x, u32 y, u32 w, u32 h, displayHandle parent);
	bool	 		vmethod(isDisplayClosed, displayHandle);
	errvt 		  	vmethod(handleEvents,    displayHandle handle, Queue(OSEvent) evntQueue);
)

Type(audioDevice,
	inst(String) name;
	inst(String) manufacturer;
	inst(String) model;
	
	void* uniqueID;

)
typedef void* audioHandle;

Interface(audio,
	errvt 	vmethod(initSystem);
	errvt 	vmethod(exitSystem);
	displayHandle 		vmethod(grabDisplay, displayDevice* device);
	arry(displayDevice) 	vmethod(enumDisplays, u64* numDevices);
	


)

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
)



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
)

typedef void* socketHandle;
typedef void* connectHandle;
Enum(socketType,
	SOCKET_UNIX = 1,
	SOCKET_IPV4 = 2,
	SOCKET_IPV6 = 3,
	SOCKET_TCP  = 4,
	SOCKET_UDP  = 8,
	SOCKET_RAW  = 12,
)
typedef u8 ipv4_netaddress[4];
typedef u16 ipv6_netaddress[8];

Type(socketAddress,
     	socketType type;
	union{
	    struct{
		u16 port;
		ipv4_netaddress address;
     	    }ipv4;
	    struct{
		u16 port;
		ipv6_netaddress address;
     	    }ipv6;
	    struct{
		inst(String) path;
     	    }local;
     	}data;
)
Interface(network,
	errvt 		vmethod(initSystem);
	errvt 		vmethod(exitSystem);
	socketHandle 	vmethod(newSocket,  	socketType   type);	
	errvt 		vmethod(bindSocket, 	socketHandle handle, socketAddress address);
	errvt 		vmethod(listen,     	socketHandle handle, u32 num_connect);
	connectHandle 	vmethod(connect,    	socketHandle handle);
	connectHandle	vmethod(accept,     	socketHandle handle);
	errvt 		vmethod(send, 	    	connectHandle handle);
	errvt 		vmethod(recieve,    	connectHandle handle);
	errvt 		vmethod(groupJoin,  	connectHandle handle);
	errvt 		vmethod(groupLeave,   	connectHandle handle);
	errvt 		vmethod(groupSend,    	connectHandle handle);
	errvt 		vmethod(groupRecive,  	connectHandle handle);
	errvt 		vmethod(handleEvents, 	connectHandle handle, Queue(OSEvent) evntQueue);
)
Interface(terminal,
	errvt 		vmethod(initSystem);
	errvt 		vmethod(exitSystem);
	

)
/*--------------------------------------|
	         Events			|
--------------------------------------*/

Type(inputEvent,
	inputDevice* device;
	bool type;
     	union {
	  struct{
		float axis[3];
	  	u16 ID;
	  }pos;
	  struct{
		u32 code;
	  	u16 ID;
	  }key;
     	}data;
)
Type(socketEvent,
	socketHandle handle;
     	u32 type;
)
Type(displayEvent,
	displayHandle handle;
     	u32 type;
)
Type(OSEvent,
	u8 osSystem : 3;
     	u8 osResource : 5;
	union{
		inputEvent input;
		socketEvent socket;
		displayHandle display;
     	}data;
)

Interface(OS,
	interface(filesys);		
	interface(input);		
	interface(graphics);	
	interface(audio);		
	interface(scheduler);	
	interface(memory);		
	interface(network);		
	interface(terminal);

	cstr OSName;
	errvt vmethod(initOSBackend);
);


#define defaultOS(interface) intf(OS) userOS = &interface;
extern intf(OS) userOS;
