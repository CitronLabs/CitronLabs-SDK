#pragma once
#include "../test-utils.h"

#include "./c_malloc.c"
#include "./arena.c"
#include "./pool.c"

    
bool RUN_STDEXTMALLOC_TESTS(){

	loginfo("\n"BLUE"--Testing Standard Extra Malloc--"NC"\n");

	INIT_TEST

	RUN_CMALLOC_TESTS();

return TEST_RESULT; 
}
