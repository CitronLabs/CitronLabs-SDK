#pragma once
#include <stdlib.h>
#include <unistd.h>

#include "__devices.h"

/*======================================|
 *	    Helper Functions		|
======================================*/

static inline void* makeUniqueID(EnvDevice_Type Envtype, void* envDeviceData, OSDevice_Type OStype, void* OSDeviceData){
	
	inst uniqueIDBuilder = push(StringBuilder);

	StringBuilder.Set(uniqueIDBuilder, NULL, 
	Envtype == EnvDevice_Video   ?
		      "Video-"      : 
	Envtype == EnvDevice_Sound   ?
		      "Sound-"      :
	Envtype == EnvDevice_Input   ?
		      "Input-"      :
	Envtype == EnvDevice_Network ?
		      "Network-"    :
	Envtype == EnvDevice_Storage ?
		      "Storage-"    : endstr,
	$(((EnvDevice_ID*)envDeviceData)->name), 
	OStype == OSDevice_Graphics  ?
		      "-graphics-"  : 
	OStype == OSDevice_Audio     ?
		      "-audio-"     :
	OStype == OSDevice_Input     ?
		      "-input-"     :
	OStype == OSDevice_Network   ?
		      "-network-"   :
	OStype == OSDevice_Storage   ?
		      "-storage-"   : endstr,
	$(((inputDevice*)OSDeviceData)->name), 
	endstr);


	inst result = StringBuilder.CreateStr(uniqueIDBuilder);
	pop(uniqueIDBuilder);

return result;          
}

/*======================================|
 *	  Method Implementations	|
======================================*/

errvt methodimpl(OSDeviceManager, registerOSDevice,, 
      	EnvDevice_Type envDevType, Device_ID envDevID, 
      	OSDevice_Type osDevType,   void* deviceData, 
	Buffer(OSDeviceResouce) res
){
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
	case OSDevice_Network:{
		os->data.network = *((networkDevice*)deviceData);
		os->data.network.uniqueID = 
			makeUniqueID(
				envDevType, &regDev.data.env.data,
				osDevType, deviceData
			); 
	break;}
	case OSDevice_Storage:{
		os->data.storage = *((storageDevice*)deviceData);
		os->data.storage.uniqueID = 
			makeUniqueID(
				envDevType, &regDev.data.env.data,
				osDevType, deviceData
			); 
	break;}
	}
	
	os->uniqueID = os->data.audio.uniqueID;

	os->resources = newList(OSDeviceResouce, 10);
	
	List.Append(os->resources, Buffer.getPointer(res), Buffer.getItemNum(res));

	Device_ID id = List.FillSlot(priv->registeredDevices, &regOSDev);
	
	Map.Insert(
		priv->deviceLookupTable, 
		os->uniqueID, 
		&id
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
Device_ID methodimpl(OSDeviceManager, findDevice,, inst(String) uniqueID){

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
void* methodimpl(OSDeviceManager, getOSDevice,, Device_ID id){
	
	RegisteredDevice* device = List.GetPointer(priv->registeredDevices, id);
	
	if(!device || !device->isOSDevice || device->isFree){
		ERR(ERR_INVALID, "invalid OSdevice id");
		return NULL;
	}
	
return &device->data.os.data;
}
void* methodimpl(OSDeviceManager, getEnvDevice,, Device_ID id){

	RegisteredDevice* device = List.GetPointer(priv->registeredDevices, id);
	
	if(!device || device->isOSDevice || device->isFree){
		ERR(ERR_INVALID, "invalid EnvDevice id");
		return NULL;
	}
	
return &device->data.env.data;
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
	nonull(self, return err);
	nonull(envDevicesList, return err);

	if(type > EnvDevice_Top)
		return ERR(ERR_INVALID, "invalid env device type");

	foreach(priv->registeredDevices, RegisteredDevice, dev){
		if(!dev.isOSDevice && dev.data.env.type == type)
			List.Append(envDevicesList, &dev.data.env.data, 1);
	}

return OK;
}
errvt methodimpl(OSDeviceManager, getOSDevices,, OSDevice_Type type, inst(List) osDevicesList){
	nonull(self, return err);
	nonull(osDevicesList, return err);

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
	nonull(object, return err);
	self(OSDeviceManager);

	List(data_entry) lookupEntries = Map.GetEntries(priv->deviceLookupTable);
	foreach(lookupEntries, data_entry, entry){
		del((class(String)entry.key));

	del(priv->deviceLookupTable);

	foreach(priv->registeredDevices, RegisteredDevice, device){

	    if(device.isFree) continue;

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
			if(data->video.info.name) 	 { del(data->video.info.name); }
			if(data->video.info.productName) { del(data->video.info.productName); }
			if(data->video.info.vendorName)  { del(data->video.info.vendorName); }
			if(data->video.info.serialCode)  { del(data->video.info.serialCode); }
			del(data->video.info.devPath);
		break;}
		case EnvDevice_Sound:{
			if(data->sound.info.name) 	 { del(data->sound.info.name); }
			if(data->sound.info.productName) { del(data->sound.info.productName); }
			if(data->sound.info.vendorName)  { del(data->sound.info.vendorName); }
			if(data->sound.info.serialCode)  { del(data->sound.info.serialCode); }
		break;}
		case EnvDevice_Input:{
			if(data->input.info.name) 	 { del(data->input.info.name); }
			if(data->input.info.productName) { del(data->input.info.productName); }
			if(data->input.info.vendorName)  { del(data->input.info.vendorName); }
			if(data->input.info.serialCode)  { del(data->input.info.serialCode); }
			foreach(data->input.inputs, inst(String), input) { del(input); }
		break;}
		default:{
			logerr("invalid type device type registered, skipping...");
		}
		}
		del(env->OSDevices);
	    }
	}
	del(priv->registeredDevices);
    ) //check
    {return err->errorcode;}

return OK;
}

/*--------------------------------------|
 *     OSDeviceManager constructor	|
--------------------------------------*/

construct(OSDeviceManager,
	.registerOSDevice 	  = OSDeviceManager_registerOSDevice,
	.getEnvDevices 	  	  = OSDeviceManager_getEnvDevices,
	.getOSDevice		  = OSDeviceManager_getOSDevice,
	.getEnvDevice		  = OSDeviceManager_getEnvDevice,
	.getEnvDeviceFromOSDevice = OSDeviceManager_getEnvDeviceFromOSDevice,
	.findDevice 		  = OSDeviceManager_findDevice,
	.addOSDeviceResources 	  = OSDeviceManager_addOSDeviceResources,
	.isConnected		  = OSDeviceManager_isConnected,
	.freeDevice		  = OSDeviceManager_freeDevice,
	.__DESTROY		  = OSDeviceManager_Destroy,
){
	
	
	priv->registeredDevices = newList(RegisteredDevice, 10);
	priv->deviceLookupTable = newMap(String, Device_ID);

	setup(DevEvents);

	setup(SOUND, 
		.deviceLookupTable = &priv->deviceLookupTable,
		.registeredDevices = &priv->registeredDevices
	);
	setup(INPUT, 
		.deviceLookupTable = &priv->deviceLookupTable,
		.registeredDevices = &priv->registeredDevices
	);
	setup(GRAPHICS, 
		.deviceLookupTable = &priv->deviceLookupTable,
		.registeredDevices = &priv->registeredDevices
	);
	setup(NETWORK, 
		.deviceLookupTable = &priv->deviceLookupTable,
		.registeredDevices = &priv->registeredDevices
	);
	setup(STORAGE, 
		.deviceLookupTable = &priv->deviceLookupTable,
		.registeredDevices = &priv->registeredDevices
	);

return self;
}
