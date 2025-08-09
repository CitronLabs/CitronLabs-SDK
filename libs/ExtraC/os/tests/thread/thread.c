#pragma once
#include "./thread.h"
#include "./control.c"



int iter = 0;

int joinfunc(inst(Thread) thread, void* args){

	loop(i, 10000)
		iter++;
		
return 0;
}

int threadfunc(inst(Thread) thread, void* args){
	NEW_SUBTEST("Passing arguements"){
		if(args == testarray)
			PASS_TEST 
		else
			FAIL_TEST
	}
return 1234;
}


bool RUN_STDTHREAD_TESTS(){
	println("\n"BLUE"--Testing Standard Thread--"NC);
	INIT_TEST


NEW_TEST("Basic Thread Control"){
	inst(Thread) test_thread = NULL;
	int res;

	NEW_SUBTEST("Getting the current thread"){
		Error.Hide();
		ERR(ERR_INITFAIL, "Testing...");
		Error.Show();
		inst(Error) data = Thread.GetErr(Thread.GetCurrent());
		if(data->errorcode  == ERR_INITFAIL)
			PASS_TEST 
		else 
			FAIL_TEST
	}
	
	NEW_SUBTEST("Creating a new thread"){
		test_thread = new(Thread, threadfunc);
		if(test_thread != NULL)
			PASS_TEST
		else 
			FAIL_TEST
	}
	NEW_SUBTEST("Running thread"){
		if(Thread.Start(test_thread, testarray) != ERR_NONE )
			FAIL_TEST
		else{
			PASS_TEST
			Error.Hide();
			while(Thread.GetExitCode(test_thread, &res) == THREADERR_RUNNING );
			Error.Show();
		}
	}
	NEW_SUBTEST("Getting the exitcode"){
		if(res == 1234)
			PASS_TEST
		else 
			FAIL_TEST
	}
	NEW_SUBTEST("Destroying threads"){
		Thread.Free(test_thread);
		Error.Hide();
		if(Thread.Start(test_thread, NULL) == THREADERR_DESTROY )

			PASS_TEST
		else 
			FAIL_TEST
		Error.Show();
	}
	NEW_SUBTEST("Joining threads"){
		test_thread = new(Thread, joinfunc);
		quiet(
		    if(Thread.Join(test_thread) != THREADERR_RUNNING )
			FAIL_TEST
		)

		Thread.Start(test_thread, NULL);
		Thread.Join(test_thread);

		if(iter == 10000)
			PASS_TEST
		else
			FAIL_TEST
	}
		Thread.Free(test_thread);
}
	Error.Clear();

	RUN_THREADCONTROL_TESTS();
	Error.Clear();


return TEST_RESULT; 
}
