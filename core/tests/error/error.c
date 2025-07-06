#pragma once
#include "../xc_additions.h"
#include "../test-utils.h"


bool RUN_STDERROR_TESTS(){
	println("\n"BLUE"--Testing Standard Error--"NC);

	INIT_TEST

NEW_TEST("Core Functionality"){
	
	NEW_SUBTEST("Setting errnum"){
		quiet(
			ERR(ERR_TEST, "Testing...");
		)
		if(errnm == ERR_TEST && strncmp(errstr,"Testing...", sizeof("Testing...")) == 0)
			PASS_TEST
		else 
			FAIL_TEST
	}
	NEW_SUBTEST("Clearing errors"){
		Error.Clear();
		if(errnm == ERR_TEST || strncmp(errstr,"Testing...", sizeof("Testing...")) == 0){
			FAIL_TEST
		}else{
			PASS_TEST
		}
	}
}

return TEST_RESULT; 
}
