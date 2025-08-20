#include "extern.h"

Enum(EnvDevice_Type, 
	EnvDevice_Video,
	EnvDevice_Sound,
	EnvDevice_Input,
	EnvDevice_Render,
     #define EnvDevice_Top EnvDevice_Render 
)
Enum(OSDevice_Type, 
	OSDevice_Graphics,
	OSDevice_Audio,
	OSDevice_Input,
     #define OSDevice_Top OSDevice_Input 
)

Type(EnvDevice_Video_Data,
	inst(String) name;
     	int fd;
)
Type(EnvDevice_Sound_Data,
	data(String) 
     	* name,
     	* vendorName,
     	* productName,
     	* serialCode;
);
Type(EnvDevice_Input_SubData,
	inst(String) fullName;
	inst(String) inputType;
)
Type(EnvDevice_Input_Data,
	data(String) 
     	* name,
     	* vendorName,
     	* productName,
     	* serialCode;
	List(EnvDevice_Input_SubData) inputs; 
);
struct EnvDevice_Input_Data;
Type(EnvDevice_Render_Data,
	inst(String) name;
     	int fd;
)

Type(OSDeviceResouce,
	intf(Object) interface;
     	inst(Object) object;
);
#define OSresource(_interface, _object) (OSDeviceResouce){.interface = (intf(Object))_interface, .object = generic _object}
#define OSPointer NULL

typedef i64 Device_ID;
#define DEVICE_ID_NULL ((Device_ID)-1)

Class(OSDeviceManager,
__INIT(),
__FIELD(),
errvt method(OSDeviceManager, registerOSDevice,, 
      	EnvDevice_Type envDevType, void* envDevUnqID, 
      	OSDevice_Type osDevType,   void* deviceData, 
	Buffer(OSDeviceResouce) res
);
errvt method(OSDeviceManager, addOSDeviceResources,, Device_ID id, Buffer(OSDeviceResouce) res);
Device_ID method(OSDeviceManager, findDevice,, void* uniqueID);
bool method(OSDeviceManager, isConnected,, Device_ID id);
errvt method(OSDeviceManager, freeDevice,, Device_ID id);
void* method(OSDeviceManager, getEnvDeviceFromOSDevice,, Device_ID id);
errvt method(OSDeviceManager, getEnvDevices,, EnvDevice_Type type, inst(List) envDevicesList);
errvt method(OSDeviceManager, getOSDevices,, OSDevice_Type type, inst(List) osDevicesList);
);

static inst(OSDeviceManager) OSDevices = NULL;

