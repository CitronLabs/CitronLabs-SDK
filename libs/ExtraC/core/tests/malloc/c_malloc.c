#pragma once
#include "../test-utils.h"

bool RUN_CMALLOC_TESTS(){

NEW_TEST("Allocator Tests"){

	int* ptr = NULL;

	u32 bytesalloc_before = CMalloc.Allocator.getBytesAlloced(generic c_malloc);
	NEW_SUBTEST("C-malloc_malloc"){
		ptr = malloc(sizeof(int));
		
		if(ptr == NULL){
			FAIL_TEST;
			loginfo("\t allocation failed");
			goto skip_cmalloc;
		}
		if(bytesalloc_before == CMalloc.Allocator.getBytesAlloced(generic c_malloc)){
			FAIL_TEST;
			loginfo("\t c_malloc_metadata not properly updated");
			goto skip_cmalloc;
		}else
			PASS_TEST
	}
	NEW_SUBTEST("C-malloc_free"){
		free(ptr);
		if(bytesalloc_before != CMalloc.Allocator.getBytesAlloced(generic c_malloc)){
			FAIL_TEST;
			loginfo("\t c_malloc_metadata not properly updated");
			goto skip_cmalloc;
		}
			PASS_TEST
	}
	NEW_SUBTEST("C-malloc_calloc"){
		ptr = calloc(4, sizeof(int));
		
		if(ptr == NULL){
			FAIL_TEST;
			loginfo("\t allocation failed");
			goto skip_cmalloc;
		}else
		if(CMalloc.Allocator.getBytesAlloced(generic c_malloc) == bytesalloc_before){
			FAIL_TEST;
			loginfo("\t c_malloc_metadata not properly updated");
			goto skip_cmalloc;
		}else
			PASS_TEST;

		free(ptr);
	}
}
skip_cmalloc:

return TEST_RESULT; 
}
