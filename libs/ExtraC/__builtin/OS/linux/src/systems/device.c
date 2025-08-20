#include <dirent.h>
#include <stddef.h>
#include <sys/epoll.h>
#include <stdlib.h>
#include <unistd.h>

#include "../backends/udev.c"
#include "__systems.h"


/*======================================|
 *	   Types and Defines		|
======================================*/

#define deviceType_OS  true
#define deviceType_ENV false

Type(RegisteredDevice,
	bool isOSDevice, isAlive, isFree;
     	union {
     	    struct {
     		EnvDevice_Type type;
     		union {
			EnvDevice_Video_Data video;
			EnvDevice_Sound_Data sound;
			EnvDevice_Input_Data input;
			EnvDevice_Render_Data render;
     		} data;
		List(Device_ID) OSDevices;
     	    } env;
     	    struct {
     		OSDevice_Type type;
     		union {
			graphicsDevice graphics;
			audioDevice audio;
     			inputDevice input;
     		} data;
     		inst(String) uniqueID;
     		List(OSDeviceResouce) resources;
     		Device_ID envDeviceParent;
     		u64 envDeviceParentIndex;
     	    } os;
     	} data;
)

/*--------------|
 *   Private	|
--------------*/

private(OSDeviceManager,
	fsHandle devDir;
	List(RegisteredDevice) registeredDevices;
	Map(String, RegisteredDevice*) deviceLookupTable;
)

Blueprint(DevParser,
__IO(
	in_Map deviceLookupTable;
	in_List registeredDevices;
), 
	fsHandle dir;
)

Module(INPUT, DevParser, 
__SETUP(inst(Map)* deviceLookupTable; inst(List)* registeredDevices), 
__PARAM(), 
)

Module(DRI, DevParser, 
__SETUP(inst(Map)* deviceLookupTable; inst(List)* registeredDevices), 
__PARAM(), 
)
Module(SND, DevParser, 
__SETUP(inst(Map)* deviceLookupTable; inst(List)* registeredDevices), 
__PARAM(), 
);

/*======================================|
 *	    Helper Functions		|
======================================*/

static inline void* makeUniqueID(EnvDevice_Type Envtype, void* envDeviceData, OSDevice_Type OStype, void* OSDeviceData){
	
	inst uniqueIDBuilder = push(StringBuilder);

	switch(Envtype){
	case EnvDevice_Video:{
		StringBuilder.Append(uniqueIDBuilder, NULL, 
		      "Video-", $(((EnvDevice_Video_Data*)envDeviceData)->name), endstr);
	break;}
	case EnvDevice_Sound:{
		StringBuilder.Append(uniqueIDBuilder, NULL, 
		      "Sound-", $(((EnvDevice_Sound_Data*)envDeviceData)->name), endstr);
	break;}
	case EnvDevice_Input:{
		StringBuilder.Append(uniqueIDBuilder, NULL, 
		      "Input-", $(((EnvDevice_Input_Data*)envDeviceData)->name), endstr);
	break;}
	case EnvDevice_Render:{
		StringBuilder.Append(uniqueIDBuilder, NULL, 
		      "Render-", $(((EnvDevice_Render_Data*)envDeviceData)->name), endstr);
	break;}
	}

	switch(OStype){
	case OSDevice_Graphics:{
		StringBuilder.Append(uniqueIDBuilder, NULL, 
		      "-graphics-", $(((graphicsDevice*)OSDeviceData)->name), endstr);
	break;}
	case OSDevice_Audio:{
		StringBuilder.Append(uniqueIDBuilder, NULL, 
		      "-audio-", $(((audioDevice*)OSDeviceData)->name), endstr);
	break;}
	case OSDevice_Input:{
		StringBuilder.Append(uniqueIDBuilder, NULL, 
		      "-input-", $(((inputDevice*)OSDeviceData)->name), endstr);
	break;}

	}

	inst result = StringBuilder.CreateStr(uniqueIDBuilder);
	pop(uniqueIDBuilder);

return result;          
}

/*======================================|
 *	  Method Implementations	|
======================================*/




/*--------------------------------------|
 *       OSDeviceManager methods	|
--------------------------------------*/

errvt methodimpl(OSDeviceManager, registerOSDevice,, 
      	EnvDevice_Type envDevType, void* envDevUnqID, 
      	OSDevice_Type osDevType,   void* deviceData, 
	Buffer(OSDeviceResouce) res
){
	
	Device_ID envDevID = OSDeviceManager.findDevice(OSDevices, envDevUnqID);
	if(envDevID == DEVICE_ID_NULL)
		return ERR(ERR_INVALID, "invalid envDevice unique ID");
	
	RegisteredDevice regDev = {0}, regOSDev = {0};
	List.Index(priv->registeredDevices, LISTINDEX_READ, envDevID, 1, &regDev);
	
	if(regDev.isOSDevice == deviceType_OS)
		return ERR(ERR_INVALID, "invalid envDevice unique ID points to OS Device");
	
	shortName(regOSDev.data.os,  os);

	os->type = osDevType; 
	switch(osDevType){
	case OSDevice_Graphics:{
		os->data.graphics = *((graphicsDevice*)deviceData);
		os->data.graphics.uniqueID = 
				makeUniqueID(
					envDevType, &regDev.data.env.data,
					osDevType, deviceData
				); 
	break;}
	case OSDevice_Audio:{
		os->data.audio = *((audioDevice*)deviceData);
		os->data.audio.uniqueID = 
				makeUniqueID(
					envDevType, &regDev.data.env.data,
					osDevType, deviceData
				); 
	break;}
	case OSDevice_Input:{
		os->data.input = *((inputDevice*)deviceData);
		os->data.input.uniqueID = 
				makeUniqueID(
					envDevType, &regDev.data.env.data,
					osDevType, deviceData
				); 
	break;}
	}
	
	os->uniqueID = os->data.audio.uniqueID;

	os->resources = newList(OSDeviceResouce);
	
	List.Append(os->resources, Buffer.getPointer(res), Buffer.getItemNum(res));

	u64 index = List.FillSlot(priv->registeredDevices, &regOSDev);
	
	Map.Insert(
		priv->deviceLookupTable, 
		os->uniqueID, 
		List.GetPointer(priv->registeredDevices, index)
	);

return OK;
}
errvt methodimpl(OSDeviceManager, addOSDeviceResources,, Device_ID id, Buffer(OSDeviceResouce) res){
	
	RegisteredDevice* device = List.GetPointer(priv->registeredDevices, id);

	if(!device || !device->isAlive || !device->isOSDevice)
		return ERR(ERR_INVALID, "invalid OSdevice id");
	
	List.Append(device->data.os.resources, Buffer.getPointer(res), Buffer.getItemNum(res));

return OK;
}
Device_ID methodimpl(OSDeviceManager, findDevice,, void* uniqueID){

	Device_ID* result = Map.Search(priv->deviceLookupTable, uniqueID);
	
	if(!result){
		ERR(ERR_FAIL, "could not find device with that uniqueID");
		return -1;
	}

return *result;
}
bool methodimpl(OSDeviceManager, isConnected,, Device_ID id){
	RegisteredDevice* device = List.GetPointer(priv->registeredDevices, id);
	
	if(!device || device->isFree)
		return ERR(ERR_INVALID, "invalid OSdevice id");

return device->isAlive;
}
errvt methodimpl(OSDeviceManager, freeDevice,, Device_ID id){
	
	RegisteredDevice* device = List.GetPointer(priv->registeredDevices, id),* parent = NULL;
	
	if(!device || !device->isOSDevice || device->isFree)
		return ERR(ERR_INVALID, "invalid OSdevice id");

shortName(device->data.os,  os)
shortName(device->data.env, env)
	
	parent = List.GetPointer(priv->registeredDevices, os->envDeviceParent);
	assert(!parent->isOSDevice);

	List.SetFree(parent->data.env.OSDevices, os->envDeviceParentIndex);
	
	if(device->isAlive){
		foreach(os->resources, OSDeviceResouce, resource){
			if(resource.interface != NULL)
				resource.interface->__DESTROY(resource.object);
			free(resource.object);
		}
	}

	del(os->uniqueID);

return OK;
}
void* methodimpl(OSDeviceManager, getEnvDeviceFromOSDevice,, Device_ID id){
	
	RegisteredDevice* device = List.GetPointer(priv->registeredDevices, id),* parent = NULL;
	
	if(!device || !device->isOSDevice || device->isFree){
		ERR(ERR_INVALID, "invalid OSdevice id");
		return NULL;
	}
	
	parent = List.GetPointer(priv->registeredDevices, device->data.os.envDeviceParent);
	assert(!parent->isOSDevice);

return &parent->data.env.data;
}
errvt methodimpl(OSDeviceManager, getEnvDevices,, EnvDevice_Type type, inst(List) envDevicesList){
	nonull(self, return nullerr);
	nonull(envDevicesList, return nullerr);

	if(type > EnvDevice_Top)
		return ERR(ERR_INVALID, "invalid env device type");

	foreach(priv->registeredDevices, RegisteredDevice, dev){
		if(!dev.isOSDevice && dev.data.env.type == type)
			List.Append(envDevicesList, &dev.data.env.data, 1);
	}

return OK;
}
errvt methodimpl(OSDeviceManager, getOSDevices,, OSDevice_Type type, inst(List) osDevicesList){
	nonull(self, return nullerr);
	nonull(osDevicesList, return nullerr);

	if(type > OSDevice_Top)
		return ERR(ERR_INVALID, "invalid env device type");

	foreach(priv->registeredDevices, RegisteredDevice, dev){
		if(dev.isOSDevice && dev.data.os.type == type)
			List.Append(osDevicesList, &dev.data.env.data, 1);
	}

return OK;
}


/*--------------------------------------|
 *     OSDeviceManager destructor	|
--------------------------------------*/

errvt imethodimpl(OSDeviceManager, Destroy){
	nonull(object, return nullerr);
	self(OSDeviceManager);
    check(
	List(data_entry) lookupEntries = Map.GetEntries(priv->deviceLookupTable);
	foreach(lookupEntries, data_entry, entry){
		del((class(String)entry.key));
	}

	del(priv->deviceLookupTable);

	foreach(priv->registeredDevices, RegisteredDevice, device){

	    shortName(device.data.os, os)
	    shortName(device.data.env, env)
	    shortName(device.data.env.data, data)

	    if(device.isOSDevice){

	    	foreach(os->resources, OSDeviceResouce, resource){
	            if(resource.interface != NULL)
			resource.interface->__DESTROY(resource.object);

		    free(resource.object);
		}
		del(os->uniqueID);
	    }else{


		switch(env->type){
		case EnvDevice_Video:{ 
			close(data->video.fd);
			del(data->video.name);
		break;}
		case EnvDevice_Render:{ 
			close(data->render.fd);
			del(data->render.name);
		break;}
		case EnvDevice_Sound:{
			del(data->sound.name);
		break;}
		case EnvDevice_Input:{
			EnvDevice_Input_SubData* inputs = List.GetPointer(data->input.inputs, 0);

			del(data->input.name);
			for(int i = 0; inputs[i].fullName != NULL; i++){
				del(inputs[i].fullName);
			}
		break;}
		default:{
			logerr("invalid type device type registered, skipping...");
		}
		}

		del(env->OSDevices);
	    }
	}

	del(priv->registeredDevices);

	if(priv->devDir)   LinuxEnv.OS.filesys.close(priv->devDir);
	if(INPUT.dir) 	   LinuxEnv.OS.filesys.close(INPUT.dir);
	if(SND.dir)   	   LinuxEnv.OS.filesys.close(SND.dir);
	if(DRI.dir)   	   LinuxEnv.OS.filesys.close(DRI.dir);
    ) //check
    {return err->errorcode;}

return OK;
}



/*--------------------------------------|
 *     OSDeviceManager constructor	|
--------------------------------------*/

#define devNameStartWith(string) \
	(dev_name->len >= sizeof(string) - 2 && String.Compare(str_view(dev_name, 0, sizeof(string) - 2), s(string)))

construct(OSDeviceManager,
	.registerOSDevice 	  = OSDeviceManager_registerOSDevice,
	.getEnvDevices 	  	  = OSDeviceManager_getEnvDevices,
	.getEnvDeviceFromOSDevice = OSDeviceManager_getEnvDeviceFromOSDevice,
	.findDevice 		  = OSDeviceManager_findDevice,
	.addOSDeviceResources 	  = OSDeviceManager_addOSDeviceResources,
	.isConnected		  = OSDeviceManager_isConnected,
	.freeDevice		  = OSDeviceManager_freeDevice,
	.__DESTROY		  = OSDeviceManager_Destroy,
){
	
	priv->devDir = LinuxEnv.OS.filesys.open(FS_DIR, "/dev", DFL_READ);
	
	priv->registeredDevices = newList(RegisteredDevice);
	priv->deviceLookupTable = newMap(String, RegisteredDevice*);
	if(!priv->devDir){
		ERR(ERR_INITFAIL, "could not open /dev directory");
		return NULL;
	}

	fsEntry entries[25] = {0};
	i32 entriesRead = 0;

	while((entriesRead = LinuxEnv.OS.filesys.read(priv->devDir, entries, 25)) != 0){
	    if(entriesRead == -1){
		ERR(ERR_INITFAIL , "failed to read through /dev directory");
	    	return NULL;
	    }

	    loop(i, entriesRead){
		inst(String) dev_name = pathtostr(entries[i].name);
		
		if(entries[i].is_dir) {
			switchs(dev_name){
			cases("snd"){
				setup(SND, 
	  				.deviceLookupTable = &priv->deviceLookupTable,
	  				.registeredDevices = &priv->registeredDevices
	  			);
			break;}
			cases("input"){
				setup(INPUT, 
	  				.deviceLookupTable = &priv->deviceLookupTable,
	  				.registeredDevices = &priv->registeredDevices
	  			);
			break;}
			cases("dri"){
				setup(DRI, 
	  				.deviceLookupTable = &priv->deviceLookupTable,
	  				.registeredDevices = &priv->registeredDevices
	  			);
			break;}
			}
		}

		if(devNameStartWith("tty") || devNameStartWith("vcs"))
			continue;

		if(devNameStartWith("video")){
			int fd = open(entries[i].name, O_RDWR);
			if(!fd)	
				logerr("failed open: ", $(dev_name));
			
			List.Append(
				priv->registeredDevices, 
	       			push(EnvDevice_Video_Data, .fd = fd, .name = String.Copy(dev_name)),
	       		 	1
			);
		}
	    }	
	}

return self;
}

/*======================================|
 *	  	Modules			|
======================================*/

#define fail(err, errmsg){ 		\

	

Setup(DevEvents){
	// Initialize libudev
	static UdevData udev;
	
	udev.handle = Udev.makeNew();
	if (!udev.handle) 
		return ERR(ERR_INITFAIL, "Cannot create udev context");
	
	// Create a udev monitor for udev events
	udev.monitor = Udev.monitor.newfromNetLink(udev.handle, "XC_LINUXDEV_WATCH");

	if (!udev.monitor){
		Udev.destroy(udev.handle);	
		return ERR(ERR_INITFAIL, "Cannot create udev monitor");	
	}
	Udev.monitor.addFilterSubsystem(udev.monitor, "video4linux", NULL);
	Udev.monitor.addFilterSubsystem(udev.monitor, "sound", NULL);
	Udev.monitor.addFilterSubsystem(udev.monitor, "drm", NULL);
	
	// Enable receiving events
	if (Udev.monitor.enable(udev.monitor) < 0){ 
		Udev.monitor.destroy(udev.monitor);
		Udev.destroy(udev.handle);	
		return ERR(ERR_INITFAIL, "Cannot enable udev monitor");	
	}

	udev.fd = Udev.monitor.getFD(udev.monitor);
	struct epoll_event event = {
		.data.fd = udev.fd,
		.events = EPOLLIN
	};

	udev.poll_fd = epoll_create1(0);

	if(udev.poll_fd == -1){ 
		Udev.monitor.destroy(udev.monitor);
		Udev.destroy(udev.handle);	
		return ERR(ERR_INITFAIL, "failed to create epoll fd");	
	}


	if(epoll_ctl(udev.poll_fd, EPOLL_CTL_ADD, udev.fd, &event) == -1){
		close(udev.poll_fd);
		Udev.monitor.destroy(udev.monitor);
		Udev.destroy(udev.handle);	
		return ERR(ERR_INITFAIL, "failed to setup epoll fd");	
	}

	self->ports.handle.data = &udev;
	
return OK;
}

Logic(DevEvents){

	if (ret > 0 && (pfd.revents & POLLIN)) {
	    struct udev_device *dev = Udev.monitor.getDevice(udev.monitor);
	    if (dev) {
	        const char *action = udev_device_get_action(dev);
	        const char *devnode = udev_device_get_devnode(dev);
	        const char *subsystem = udev_device_get_subsystem(dev);
	
	        if (action && devnode && subsystem && strcmp(subsystem, "video4linux") == 0) {
	            printf("Detected new video device: %s (Action: %s)\n", devnode, action);
	            // Add further device introspection here if needed
	        }
	        udev_device_unref(dev);
	    }
	}
}


/*--------------------------------------|
 *     /dev/input Monitor Module	|
--------------------------------------*/

static inline noFail parseUdevNameScheme(
		fsPath name, 
		inst(String) IDName, 
		inst(String) vendorName,
		inst(String) productName,
		inst(String) serialCode
){

	u32 nameStartIndex = 0, nameEndIndex = 0;
	while(name[nameStartIndex] != '-')
		nameStartIndex++;
	
	nameEndIndex = nameStartIndex;

	while(name[nameEndIndex] != '-')
		nameEndIndex++;
	
	init(String, IDName, 
      		.c_str = &name[nameStartIndex], 
      		.len = nameEndIndex - nameStartIndex
      	);

	inst(String) subNames[3] = {vendorName, productName, serialCode};
	u8 subNameIndex = 0;

	loopat(i, nameStartIndex, IDName->len){
		if(name[i] == '_'){
			init(String, subNames[subNameIndex],
      				.c_str = &name[nameStartIndex], 
      				.len = i - nameStartIndex
       			);
			subNameIndex++;
		}
		if(subNameIndex == 3) break;
	}
}


Setup(INPUT){
	if(!(INPUT.dir = LinuxEnv.OS.filesys.open(FS_DIR, "/dev/input/by-id", DFL_READ))){
		logerr("failed to open /dev/input/by-id dir");
	}
	setports(INPUT){
		.deviceLookupTable.data = args.deviceLookupTable,
		.registeredDevices.data = args.registeredDevices,
		.ready = true
	};
	run(INPUT);
return OK;
}


Logic(INPUT){

	fsEntry entries[10] = {0};
	size_t numRead = 0;
	inst 
		lookup = in(deviceLookupTable) : NULL,
		devList = in(registeredDevices) : NULL
	;
	
	if(!lookup) return;

	while((numRead = LinuxEnv.OS.filesys.read(self->dir, &entries, 10)) != 0){
	    loop(i, numRead){
		if(entries[i].is_dir) continue;

		Buffer(String) nameBuff = newBuffer(data(String), 4);
		arry(data(String)) names = Buffer.getPointer(nameBuff);
		
		RegisteredDevice regDev = {
			.data.env = {
			    .type = EnvDevice_Input,
			    .data.input = {
				.name 		= &names[0],
				.vendorName 	= &names[1],
				.productName 	= &names[2],
				.serialCode 	= &names[3],
			    }
			}
		};

		shortName(regDev.data.env.data.input, input)

		parseUdevNameScheme(entries[i].name,
		      input->name, 
		      input->vendorName, 
		      input->productName, 
		      input->serialCode
		);
	
		Device_ID* idpntr = Map.Search(lookup, input->name);
		
		if(idpntr) {
			EnvDevice_Input_SubData	subdata = {
				.fullName = newString(entries[i].name, 255),
				.inputType = new(String)
			};
			
			u32 inputTypeStartIndex = subdata.fullName->len;

			while(subdata.fullName->txt[inputTypeStartIndex] != '-')
				inputTypeStartIndex--;

			subdata.inputType->txt = &subdata.fullName->txt[inputTypeStartIndex];
			subdata.inputType->len = subdata.fullName->len - inputTypeStartIndex;
			subdata.inputType->type = CT_ASCI;

			del(nameBuff);
			RegisteredDevice* regDev = List.GetPointer(devList, *idpntr);

			List.Append(regDev->data.env.data.input.inputs, &subdata, 1);

			continue;
		}

		regDev.isAlive = true;
		regDev.data.env.OSDevices = newList(Device_ID);

		u32 index = List.FillSlot(devList, &regDev);

		Map.Insert(lookup, 
	     		input->name, 
	     		List.GetPointer(devList, index)
	     	);
	    }
	}
}

/*--------------------------------------|
 *     /dev/snd Monitor Module		|
--------------------------------------*/

Setup(SND){
	if(!(SND.dir = LinuxEnv.OS.filesys.open(FS_DIR, "/dev/snd/by-id", DFL_READ))){
		logerr("failed to open /dev/snd/by-id dir");
	}
	setports(SND){
		.deviceLookupTable.data = args.deviceLookupTable,
		.registeredDevices.data = args.registeredDevices,
		.ready = true
	};
	run(SND);
return OK;
}
Logic(SND){ // exact same process as Logic(INPUT) but with out the collection of subdata devices

	fsEntry entries[10] = {0};
	size_t numRead = 0;
	inst 
		lookup = in(deviceLookupTable) : NULL,
		devList = in(registeredDevices) : NULL
	;
	
	if(!lookup) return;

	while((numRead = LinuxEnv.OS.filesys.read(self->dir, &entries, 10)) != 0){
	    loop(i, numRead){
		if(entries[i].is_dir) continue;

		Buffer(String) nameBuff = newBuffer(data(String), 4);
		arry(data(String)) names = Buffer.getPointer(nameBuff);
		
		RegisteredDevice regDev = {
			.data.env = {
			    .type = EnvDevice_Input,
			    .data.sound = {
				.name 		= &names[0],
				.vendorName 	= &names[1],
				.productName 	= &names[2],
				.serialCode 	= &names[3],
			    }
			}
		};

		shortName(regDev.data.env.data.sound, sound)

		parseUdevNameScheme(entries[i].name,
		      sound->name, 
		      sound->vendorName, 
		      sound->productName, 
		      sound->serialCode
		);
	
		Device_ID* idpntr = Map.Search(lookup, sound->name);

		if(idpntr) {
			del(nameBuff);
			continue;
		}
		regDev.isAlive = true;
		regDev.data.env.OSDevices = newList(Device_ID);

		u32 index = List.FillSlot(devList, &regDev);

		Map.Insert(lookup, 
	     		sound->name, 
	     		List.GetPointer(devList, index)
	     	);
	    }
	}
}


/*--------------------------------------|
 *     /dev/dri Monitor Module		|
--------------------------------------*/
Setup(DRI){

	if(!(DRI.dir = LinuxEnv.OS.filesys.open(FS_DIR, "/dev/dri", DFL_READ))){
		logerr("failed to open /dev/dri dir");
	}
	setports(DRI){
		.deviceLookupTable.data = args.deviceLookupTable,
		.registeredDevices.data = args.registeredDevices,
		.ready = true
	};
	run(DRI);

return OK;
}
Logic(DRI){



}


