#include "List.h"
#include "tests/features.c"
#include "tests/errors.c"
#include "tests/cases.c"


TEST(LIST){
	NEW_TEST("List Data Structure");

	RUN_TEST(LIST_FEATURES){
		return TEST_RESULT;
	}
	
	RUN_TEST(LIST_ERRORS){
		return TEST_RESULT;
	}
	
	RUN_TEST(LIST_EDGE_CASES){
		return TEST_RESULT;
	}

return TEST_RESULT;
}
