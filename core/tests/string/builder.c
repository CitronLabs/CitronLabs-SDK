#pragma once
#include "../test-utils.h"

bool RUN_BUILDER_TESTS(){

NEW_TEST("String Builder Tests"){
	inst(StringBuilder) builder;

	NEW_SUBTEST("Initialization"){
		if((builder = push(StringBuilder, s("Hello, World!"), sizeof("Hello, World!"))) == NULL){
			FAIL_TEST
			goto skip;
		}
		str_t temp = StringBuilder.GetStr(builder);
		if(!String.Compare(&temp, s("Hello, World!"))){
			FAIL_TEST
			goto skip;
		}
			PASS_TEST
	}NEW_SUBTEST("Setting Max"){
		if(StringBuilder.Max(builder, 5) != ERR_NONE){
			FAIL_TEST
			goto skip;
		}
		str_t temp = StringBuilder.GetStr(builder);
		if(!String.Compare(&temp, s("Hello"))){
			FAIL_TEST
			goto skip;
		}
			PASS_TEST
	}
	NEW_SUBTEST("Appending"){
		StringBuilder.Max(builder, UINT64_MAX);
		if(StringBuilder.Append(builder, s(", how are you")) != s(", how are you")->len){
			FAIL_TEST
			println("failed to append");
			goto skip;
		}
		if(StringBuilder.Append(builder, NULL,
			 $('?'), endstr) != 1
		){
			FAIL_TEST
			println("failed to format append");
			goto skip;
		}
		str_t temp = StringBuilder.GetStr(builder); 
		if(!String.Compare(&temp, s("Hello, how are you?"))){
			FAIL_TEST
			println("strings not equal");
			goto skip;
		}
			PASS_TEST
	}
	NEW_SUBTEST("Freeing"){
		pop(builder);
		if(errnm != ERR_NONE ){
			FAIL_TEST
			println("error occured when freeing");
			goto skip;
		}
			PASS_TEST
	}
}
skip:
return TEST_RESULT;
}
