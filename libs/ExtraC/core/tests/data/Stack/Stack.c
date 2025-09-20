#include "Stack.h"
#include "tests/features.c"
#include "tests/errors.c"
#include "tests/cases.c"


bool RUN_STACK_TESTS(){

	NEW_TEST("Stack Data Structure");

	RUN_TEST(STACK_FEATURES){
		return TEST_RESULT;
	}
	
	RUN_TEST(STACK_ERRORS){
		return TEST_RESULT;
	}
	
	RUN_TEST(STACK_EDGE_CASES){
		return TEST_RESULT;
	}

}
