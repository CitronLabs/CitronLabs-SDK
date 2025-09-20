#include "../data.h"
#include "tests/features.c"
#include "tests/errors.c"
#include "tests/cases.c"

bool RUN_QUEUE_TESTS(){

	NEW_TEST("Queue Data Structure");

	RUN_TEST(QUEUE_FEATURES){
		return TEST_RESULT;
	}
	
	RUN_TEST(QUEUE_ERRORS){
		return TEST_RESULT;
	}
	
	RUN_TEST(QUEUE_EDGE_CASES){
		return TEST_RESULT;
	}


}
