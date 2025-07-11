#pragma once
#include "./data.h"
#include "./list.c"
#include "./stack.c"
#include "./queue.c"
#include "./map.c"
#include "./datastructs.c"

bool RUN_STDDATA_TESTS(){
	println("\n"BLUE"--Testing Standard Data--"NC);
	
	INIT_TEST


	RUN_LIST_TESTS();
	Error.Clear();
	RUN_STACK_TESTS();
	Error.Clear();
	RUN_QUEUE_TESTS();
	Error.Clear();
	RUN_MAP_TESTS();
	Error.Clear();
	RUN_DATASTRUCTS_TESTS();
	Error.Clear();
		


return TEST_RESULT; 
}
