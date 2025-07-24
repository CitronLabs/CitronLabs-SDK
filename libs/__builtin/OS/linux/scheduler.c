#include "OS.h"

int main(int argc, cstr argv[]);
Type(LinuxThread,
	pthread_t thread;
);

void vmethodimpl(LinuxScheduler, sleep, u64 millisec){
	usleep(millisec);
}

threadHandle vmethodimpl(LinuxScheduler, newThread, void fn(startfn,void*), void* args){
	nonull(startfn, return NULL);

	LinuxThread* result = new(LinuxThread);

	if(-1 == pthread_create(&result->thread, NULL, (void*(*)(void*))startfn, args)){
		switch (errno) {
		
		}
	}

return result;
}


const ImplAs(scheduler, LinuxScheduler){
	.sleep = LinuxScheduler_sleep,
	.newThread = LinuxScheduler_newThread	
};
