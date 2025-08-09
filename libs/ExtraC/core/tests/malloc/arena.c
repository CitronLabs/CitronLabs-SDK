#pragma once
#include "../test-utils.h"

bool RUN_ARENA_TESTS(){

NEW_TEST("Arena Allocator Tests"){
	
	inst(Arena) arena = NULL;
	u32* num_buf = NULL;

	NEW_SUBTEST("Initialization"){
		if((arena = new(Arena, .init_size = sizeof(u32) * 4)) == NULL){
			FAIL_TEST
			goto skip;
		}else
			PASS_TEST
	}
	NEW_SUBTEST("Allocation"){
		if((num_buf = Arena.Allocator.New(generic arena, sizeof(u32) * 4, NULL)) == NULL){
			FAIL_TEST
			goto skip;
		}else
			PASS_TEST
	}
	NEW_SUBTEST("Setting Max"){
		if(Arena.Allocator.Resize(generic arena, NULL, sizeof(u32) * 4, NULL) != ERR_NONE){
			FAIL_TEST
			goto skip;
		}else
			PASS_TEST
	}



}	
skip:

return TEST_RESULT; 
}
