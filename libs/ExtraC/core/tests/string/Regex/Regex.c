#include "Regex.h"
#include "tests/features.c"
#include "tests/errors.c"
#include "tests/cases.c"

bool RUN_REGEX_TESTS() {

	NEW_TEST("Regex Matching");

	RUN_TEST(REGEX_FEATURES){
		return TEST_RESULT;
	}
	
	RUN_TEST(REGEX_ERRORS){
		return TEST_RESULT;
	}
	
	RUN_TEST(REGEX_EDGE_CASES){
		return TEST_RESULT;
	}

return TEST_RESULT;
}

