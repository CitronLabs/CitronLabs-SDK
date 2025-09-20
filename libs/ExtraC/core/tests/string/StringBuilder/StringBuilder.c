#include "StringBuilder.h"
#include "tests/features.c"
#include "tests/errors.c"
#include "tests/cases.c"

TEST(STRINGBUILDER){

	NEW_TEST("String Building");


	RUN_TEST(STRINGBUILDER_FEATURES){
		return TEST_RESULT;
	}
	
	RUN_TEST(STRINGBUILDER_ERRORS){
		return TEST_RESULT;
	}
	
	RUN_TEST(STRINGBUILDER_EDGE_CASES){
		return TEST_RESULT;
	}


return TEST_RESULT;
}
