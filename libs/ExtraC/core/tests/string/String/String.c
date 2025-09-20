#include "String.h"
#include "tests/features.c"
#include "tests/errors.c"
#include "tests/cases.c"



TEST(STRING){

	NEW_TEST("String Building");


	RUN_TEST(STRING_FEATURES){
		return TEST_RESULT;
	}
	
	RUN_TEST(STRING_ERRORS){
		return TEST_RESULT;
	}
	
	RUN_TEST(STRING_EDGE_CASES){
		return TEST_RESULT;
	}


return TEST_RESULT;
}
