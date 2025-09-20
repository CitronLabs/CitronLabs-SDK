#include "DSN.h"

#include "tests/features.c"
#include "tests/errors.c"
#include "tests/cases.c"

TEST(DSN){

	NEW_TEST("DSN Serialization");

	RUN_TEST(DSN_FEATURES){
		return TEST_RESULT;
	}
	
	RUN_TEST(DSN_ERRORS){
		return TEST_RESULT;
	}
	
	RUN_TEST(DSN_EDGE_CASES){
		return TEST_RESULT;
	}

return TEST_RESULT
}
