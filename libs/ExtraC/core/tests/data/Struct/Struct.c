#include "Struct.h"
#include "tests/features.c"
#include "tests/errors.c"
#include "tests/cases.c"


TEST(STRUCT){

	NEW_TEST("Generic Data Structure");

	RUN_TEST(STRUCT_FEATURES){
		return TEST_RESULT;
	}
	
	RUN_TEST(STRUCT_ERRORS){
		return TEST_RESULT;
	}
	
	RUN_TEST(STRUCT_EDGE_CASES){
		return TEST_RESULT;
	}

}
