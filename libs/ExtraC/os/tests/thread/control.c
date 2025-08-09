#pragma once
#include "./thread.h"


int shared_variable = 0;
inst(Mutex) mutex = NULL;
inst(Semaphore) sem1 = NULL, *sem2 = NULL;

static int sem_func(inst(Thread) thread, void* args){
	
	Semaphore.Wait(sem1);

	shared_variable += (u64)args;

	Semaphore.Wait(sem2);
	Semaphore.Post(sem2);

return 0;
}
static int mutex_func(inst(Thread) thread, void* args){
	Mutex.Lock(mutex);

	Thread.Sleep(10);
	shared_variable = 1;

	Mutex.Unlock(mutex);

return 0;
}


bool RUN_THREADCONTROL_TESTS(){

	inst(Thread) test_thread = NULL;
	inst(Thread) test_thread2 = NULL;

NEW_TEST("Mutex Tests"){

	NEW_SUBTEST("Initialization"){
		mutex = new(Mutex);
		if(mutex != NULL)
			PASS_TEST
		else 
			FAIL_TEST
	}
	NEW_SUBTEST("Locking and unlocking"){
		test_thread = new(Thread, mutex_func);
		int passed_cycles = 0;

		quiet(
		loop(i, 100){
			Thread.Start(test_thread, NULL);
			while(Mutex.TryLock(mutex) == THREADERR_MUTEX_LOCKED );
			if(shared_variable == 1)
				passed_cycles++;
			shared_variable = 0;
			Mutex.Unlock(mutex);

		Thread.Join(test_thread);
		}
		)
	if(passed_cycles == 99)
		PASS_TEST
	else{
		FAIL_TEST
		println("FAIL RESULT: ", $(passed_cycles));
	}
	}
	Thread.Free(test_thread);
}

NEW_TEST("Semaphore Test"){
	NEW_SUBTEST("Initialization"){
		sem1 = new(Semaphore, 2);
		sem2 = new(Semaphore, 1);
		if(sem1 != NULL && sem2 != NULL)
			PASS_TEST
		else 
			FAIL_TEST
	}
	NEW_SUBTEST("Joining and Leaving"){
		
		test_thread = new(Thread, sem_func);		 
		test_thread2 = new(Thread, sem_func);
		
		shared_variable = 0;

		Semaphore.Wait(sem2);

		Thread.Start(test_thread, (void*)1);
		Thread.Start(test_thread2, (void*)2);
		
		while(Semaphore.TryWait(sem1) != THREADERR_SEM_FULL )
			{ Semaphore.Post(sem1); Thread.Sleep(1);}

		Semaphore.Post(sem2);

		if(shared_variable == 3)
			PASS_TEST
		else{
			FAIL_TEST
		println("FAIL RESULT: ", $(shared_variable));
		}

		Thread.Join(test_thread);
		Thread.Join(test_thread2);
		
	}
		Thread.Free(test_thread);
		Thread.Free(test_thread2);
		del(sem1);
		del(sem2);
}

return TEST_RESULT;
}
