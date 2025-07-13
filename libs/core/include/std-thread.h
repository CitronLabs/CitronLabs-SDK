#pragma once
#include "std-error.h"
#include "std-libc.h"
#include "std-error.h"

typedef struct std_thread std_thread;
typedef struct thread_mutex thread_mutex;
typedef struct thread_semaphore thread_semaphore;

typedef struct Thread_Instance Thread_Instance;

Class(Thread,
__INIT(int(*func)(inst(Thread), void* args);),
__FIELD(),

	errvt method(Thread,Start,, void* args);
	errvt method(Thread,Join);
	errvt method(Thread,Free);
	errvt method(Thread,Exit,,int exitcode);
	errvt method(Thread,GetExitCode,, int* result);
      	inst(Error) method(Thread,GetErr);
	void (*Sleep)(u64 milliseconds);
      	inst(Thread)(*GetCurrent)();
);
Class(Mutex,
__INIT(),
__FIELD(thread_mutex* thread;),
      	errvt method(Mutex,Lock);
      	errvt method(Mutex,Unlock);
      	errvt method(Mutex,TryLock);
);
Class(Semaphore,
__INIT(u64 slots;),
__FIELD(thread_semaphore* thread;),
      	errvt method(Semaphore,Wait);
      	errvt method(Semaphore,Post);
      	errvt method(Semaphore,TryWait);
);
