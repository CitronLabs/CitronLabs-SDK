
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
