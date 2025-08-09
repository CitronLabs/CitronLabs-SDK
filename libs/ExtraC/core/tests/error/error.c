#pragma once
#include "error.h"
#include "../test-utils.h"
#include "./logger.c"

bool RUN_STDERROR_TESTS(){
	loginfo("\n"BLUE"--Testing Standard Error--"NC"\n");

	INIT_TEST

NEW_TEST("Core Functionality"){
	
	NEW_SUBTEST("Setting errnum"){
		quiet(
			ERR(ERR_FAIL, "Testing...");
		)
		if(errnm == ERR_FAIL && strncmp(errstr,"Testing...", sizeof("Testing...")) == 0)
			PASS_TEST
		else 
			FAIL_TEST
	}
	NEW_SUBTEST("Clearing errors"){
		Error.Clear();
		if(errnm == ERR_FAIL || strncmp(errstr,"Testing...", sizeof("Testing...")) == 0){
			FAIL_TEST
		}else{
			PASS_TEST
		}
	}
	
}

return TEST_RESULT; 
}
