#pragma once
#include "stringutils.h"
#include "StringBuilder/StringBuilder.c"
#include "String/String.c"
#include "Regex/Regex.c"

TEST(STRING_UTILS){

	loginfo("\n"BLUE"--Testing Standard Extra String--"NC);

	INIT_TEST
		

	RUN_TEST(STRING){
		return TEST_RESULT;
	}
	RUN_TEST(STRINGBUILDER){
		return TEST_RESULT;
	}
	RUN_TEST(REGEX){
		return TEST_RESULT;
	}

return TEST_RESULT; 
}
