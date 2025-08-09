#pragma once
#pragma once
#include "./file.c"
#include "./dir.c"


bool RUN_STDEXTIO_TESTS(){
	println("\n"BLUE"--Testing Standard Extra IO--"NC);

	INIT_TEST
	RUN_FILE_TESTS();		
	Error.Clear();
	RUN_DIR_TESTS();		
	Error.Clear();


return TEST_RESULT; 
}
