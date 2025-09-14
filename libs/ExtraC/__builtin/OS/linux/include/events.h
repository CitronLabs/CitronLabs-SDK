#pragma once
#include "extern.h"

Enum(Events_Type,
	Events_Dev	,
	Events_Video	,
     	Events_Input	,
     	Events_Filesys	,
     	Events_Network 	,
     	#define Events_Top Events_Network
)

Blueprint(Events, 
__IO(in_any handle; out_u64 numEvents),
	  List(Queue(OSEvent)) eventQueues;
)

Module(DevEvents, 	Events,,,)
Module(VideoEvents, 	Events,,,)
Module(DisplayEvents, 	Events,,,)
Module(SoundEvents, 	Events,,,)
Module(InputEvents, 	Events,,,)
Module(FilesysEvents, 	Events,,,)
Module(NetworkEvents, 	Events,,,)
Module(SchedulerEvents, Events,,,)
Module(MemoryEvents, 	Events,,,)
Module(UserEvents, 	Events,,,)
