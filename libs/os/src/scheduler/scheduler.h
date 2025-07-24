#pragma once
#include "../../include/all.h"


static List(inst(Thread)) active_threads = NULL;
static Stack(inst(Thread)) freed_threads = NULL;

private(Thread,
	pthread_t thread;
	u64 thread_index;
	int(*start_func)(inst(Thread) thread, void* args);
	inst(Error) errdata;
	int exit_code;
	bool is_active;
);

private(Mutex,
	pthread_mutex_t mutex;
);

private(Semaphore,
	sem_t semaphore;	
);

int main(int argc, cstr* argv);

static inst(Thread) init_thread = 
    &(Thread_Instance){
	.__private = &(Thread_Private){
		.errdata = &(Error_Instance){
			.errorcode = 0,
			.message = "No Error"
		},
		.is_active = true,
		.start_func = (int(*)(inst(Thread),void*))main,
		.exit_code = 0
	},
	.__methods = &Thread,
	.__init = true
};

#ifndef __THREAD_SOURCE_DEF__
#include "./threads.c"
#include "./mutex.c"
#include "./semaphore.c"
#endif

