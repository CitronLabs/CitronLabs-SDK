#pragma once
#include "extern.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>
#include <unistd.h>
#include <bits/pthreadtypes.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include "semaphore.h"

Static(LinuxEnv,
	interface(OS);
	
)

void populateDisplayDevInfo(inst(String) name, inst(displayDevice) devStruct);

void evntHandler(Queue(OSEvent) evntQueue){
	OSEvent evnt;

    go(HandleEvents){
	   while(Queue.Check(evntQueue)){ Queue.Dequeue(evntQueue, &evnt, 1);
		switch (evnt.osSystem) {
			
		}
	   }

	yield();
    }
}

void testo(){
	Queue(OSEvent) evntQueue = pushQueue(OSEvent);
	LinuxEnv.OS.filesys.handleEvents(NULL, evntQueue);

	evntHandler(evntQueue);
	
	for(;;){

	}
	
	
}
