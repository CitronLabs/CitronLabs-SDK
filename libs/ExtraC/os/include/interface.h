#pragma once
#include "extern.h"
#include "./os-interface/filesys.h"
#include "./os-interface/input.h"
#include "./os-interface/graphics.h"
#include "./os-interface/audio.h"
#include "./os-interface/scheduler.h"
#include "./os-interface/memory.h"
#include "./os-interface/network.h"

/*--------------------------------------|
	      OS BACKEND		|
--------------------------------------*/

typedef u32 OSEventType;

#define SYS_GRAPHICS 0
  #define SYS_GRAPHICS_DISPLAY 0
  #define SYS_GRAPHICS_VIDEO 1

#define SYS_AUDIO 1 

#define SYS_INPUT 2 
  #define SYS_INPUT_POS 0 
  #define SYS_INPUT_KEY 1 

#define SYS_NETWORK 3

Type(OSEvent,
	u8 osSystem : 3;
     	u8 osResource : 5;
	union{
		inputEvent input;
		socketEvent socket;
		displayEvent display;
		videoEvent video;
		audioEvent audio;
     	}data;
)

typedef void* osHandle;

Interface(OS,
	interface(filesys);		
	interface(input);		
	interface(graphics);	
	interface(audio);		
	interface(scheduler);	
	interface(memory);		
	interface(network);		

	cstr OSName;
	errvt vmethod(initOS);
	errvt vmethod(exitOS);
	u64   vmethod(pollEvents);
);

#define defaultOS(interface) intf(OS) userOS = &interface;
extern intf(OS) userOS;

