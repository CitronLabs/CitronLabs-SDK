#pragma once
#include "../../test-utils.h"
#include "./builder.c"

bool RUN_STRINGTYPES_TESTS();		


bool RUN_STRING_TESTS(){

NEW_TEST("String Tests"){
	inst(String) string = {0};
	inst(String) stringcpy = {0};

	NEW_SUBTEST("Initialization"){
		if((string = push(String, "Hello, World!", sizeof("Hello, World!")))->txt == NULL){
			FAIL_TEST
			goto skip;
		}
		if(strncmp(string->txt, "Hello, World!", sizeof("Hello, World!")) != 0){
			FAIL_TEST
			goto skip;
		}
			PASS_TEST
	}
	NEW_SUBTEST("Copying"){
		if((stringcpy = String.Copy(string))->txt == NULL){
			FAIL_TEST
			goto skip;
		}
		if(strncmp(stringcpy->txt, "Hello, World!", sizeof("Hello, World!")) != 0){
			FAIL_TEST
			goto skip;
		}
			PASS_TEST
	}
	NEW_SUBTEST("Comparing"){
		if(!String.Compare(stringcpy, string)){
			FAIL_TEST
			goto skip;
		}
			PASS_TEST
	}
	NEW_SUBTEST("Freeing"){
		pop(stringcpy);
		if(errnm != ERR_NONE){
			FAIL_TEST
			goto skip;
		}
			PASS_TEST
	}
	NEW_SUBTEST("Scanning"){
		char c = '\0';
		if(String.Scan(string, $(c), endscan) != 1){
			FAIL_TEST
			goto skip;
		}
		if(c != 'H'){
			FAIL_TEST
			goto skip;
		}
			PASS_TEST
	}
	NEW_SUBTEST("Regexing"){
		str_regex_result result[3] = {0};
		i32 num_found = 0;
		if((num_found = String.Regex(s("Hello, World"), s("W[a-z].[ol]d"), result, 3)) == -1){
			FAIL_TEST
			goto skip;
		}
		if(num_found > 1){
			FAIL_TEST
			println($(num_found));
			goto skip;
		}
		if(result[0].str_offset != 7 && result[0].len != s("World")->len){
			FAIL_TEST
			println($(result[0].str_offset), "  ", $(result[0].len), "  ", $((s("World")->len)));
			goto skip;
		}
			PASS_TEST
	}
}
skip:
return TEST_RESULT;
}

bool RUN_STDEXTSTRING_TESTS(){

	println("\n"BLUE"--Testing Standard Extra String--"NC);

	INIT_TEST
		

	RUN_BUILDER_TESTS();		
	Error.Clear();
	RUN_STRING_TESTS();		
	Error.Clear();


return TEST_RESULT; 
}
