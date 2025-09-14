#pragma once
#include "extern.h"

typedef i64 Device_ID;
#define DEVICE_ID_NULL ((Device_ID)-1)

Enum(EnvDevice_Type, 
	EnvDevice_Video,
	EnvDevice_Sound,
	EnvDevice_Network,
	EnvDevice_Storage,
	EnvDevice_Input,
     #define EnvDevice_Top EnvDevice_Input 
)
Enum(OSDevice_Type, 
	OSDevice_Graphics,
	OSDevice_Audio,
	OSDevice_Network,
	OSDevice_Storage,
	OSDevice_Input,
     #define OSDevice_Top OSDevice_Input 
)
Type(EnvDevice_ID,
	data(String) 
     	* name,
     	* vendorName,
     	* productName,
     	* serialCode,
     	* devPath;
     	Device_ID id;
)
Type(EnvDevice_Network_Data,
     	EnvDevice_ID info;
)
Type(EnvDevice_Storage_Data,
     	EnvDevice_ID info;
)
Type(EnvDevice_Video_Data,
     	EnvDevice_ID info;
     	videoDirection direction;
)
Type(EnvDevice_Sound_Data,
     	EnvDevice_ID info;
);
Type(EnvDevice_Input_Data,
     	EnvDevice_ID info;
	List(String) inputs; 
);
Type(OSDeviceResouce,
	intf(Object) interface;
     	inst(Object) object;
);
#define OSresource(_interface, _object) (OSDeviceResouce){.interface = (intf(Object))_interface, .object = generic _object}
#define OSPointer NULL


Class(OSDeviceManager,
__INIT(),
__FIELD(),
errvt method(OSDeviceManager, registerOSDevice,, 
      	EnvDevice_Type envDevType, Device_ID envDevUnqID, 
      	OSDevice_Type osDevType,   void* deviceData, 
	Buffer(OSDeviceResouce) res
);
errvt 	  method(OSDeviceManager, addOSDeviceResources,, Device_ID id, Buffer(OSDeviceResouce) res);
Device_ID method(OSDeviceManager, findDevice,, inst(String) key);
bool 	  method(OSDeviceManager, isConnected,, Device_ID id);
errvt 	  method(OSDeviceManager, freeDevice,, Device_ID id);
void* 	  method(OSDeviceManager, getOSDevice,, Device_ID id);
void* 	  method(OSDeviceManager, getEnvDevice,, Device_ID id);
void* 	  method(OSDeviceManager, getEnvDeviceFromOSDevice,, Device_ID id);
errvt 	  method(OSDeviceManager, getEnvDevices,, EnvDevice_Type type, inst(List) envDevicesList);
errvt 	  method(OSDeviceManager, getOSDevices,, OSDevice_Type type, inst(List) osDevicesList);
);

static inst(OSDeviceManager) OSDevices = NULL;

