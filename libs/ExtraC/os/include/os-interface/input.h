#pragma once
#include "../extern.h"

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
	u64 		  vmethod(pollEvents);
)

Enum(inputEventType,
	INPUT_EVENT_UPDATE,
	INPUT_EVENT_CLOSE
)

Type(inputEvent,
	inputDevice* device;
	inputEventType type;
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
