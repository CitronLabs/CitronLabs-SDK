#include "../Stack.h"

TEST(STACK_FEATURES){

	Stack(char) stack = NULL;

	NEW_SUBTEST("Initialization"){
		stack = pushStack(c8, 10);
		if(!isinit(stack)){
			FAIL_TEST
			goto skip;
		} 
			PASS_TEST
	}
	NEW_SUBTEST("Pushing"){
		if(Stack.Push(stack, "Hello, World!", sizeof("Hello, World!") - 1)){
			FAIL_TEST
			goto skip;
	    	}
		if(Stack.Count(stack) == 0){
			FAIL_TEST
			goto skip;
		}
			PASS_TEST
	}
	NEW_SUBTEST("Popping"){
		char stack_data[sizeof("Hello, World!")] = {0};
		
		if(Stack.Pop(stack, stack_data, sizeof("Hello, World!") - 1)){
			FAIL_TEST
			goto skip;
		}
		if(Stack.Count(stack) > 0){
			FAIL_TEST
			loginfo("count on fail: ", $(Stack.Count(stack)));
			goto skip;
		}
		if(strncmp(stack_data, "!dlroW ,olleH", sizeof("Hello, World!")) != 0){
			FAIL_TEST
			goto skip;
		}
			PASS_TEST
	}
	NEW_SUBTEST("Freeing"){
		pop(stack);
		if(errnm != ERR_NONE ){
			FAIL_TEST
			goto skip;
		}
			PASS_TEST
	}
	NEW_SUBTEST("Initialize Literal"){
		char stack_data[sizeof("Hello, World!")] = {0};
		
		stack = l_s('H','e','l','l','o',',',' ','W','o','r','l','d','!');

		if(stack == NULL){
			FAIL_TEST
			goto skip;
		}
		if(Stack.Count(stack) == 0){
			FAIL_TEST
			goto skip;
		}
		if(Stack.Pop(stack, stack_data, sizeof("Hello, World!") - 1)){
			FAIL_TEST
			goto skip;
		}
		if(Stack.Count(stack) > 0){
			FAIL_TEST
			goto skip;
		}
		if(strncmp(stack_data, "!dlroW ,olleH", sizeof("Hello, World!")) != 0){
			FAIL_TEST
			loginfo("stack_data:\n", stack_data, "\n!dlroW ,olleH");
			goto skip;
		}
		pop(stack);
		if(errnm != ERR_NONE ){
			FAIL_TEST
			goto skip;
		}
			PASS_TEST
	}

skip:

return TEST_RESULT;
}
