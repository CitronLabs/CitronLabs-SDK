#pragma once
#include "data.h"
#include "List/List.c"
#include "Stack/Stack.c"
#include "Queue/Queue.c"
#include "Map/Map.c"
#include "Struct/Struct.c"
#include "DSN/DSN.c"

TEST(DATA){
	loginfo("\n"BLUE"--Testing Standard Data--"NC);
	
	INIT_TEST

	RUN_TEST(LIST){
		return TEST_RESULT;
	};
	RUN_TEST(STACK){
		return TEST_RESULT;
	};
	RUN_TEST(QUEUE){
		return TEST_RESULT;
	};
	RUN_TEST(MAP){
		return TEST_RESULT;
	};
	RUN_TEST(STRUCT){
		return TEST_RESULT;
	};
	RUN_TEST(DSN){
		return TEST_RESULT;
	};


return TEST_RESULT; 
}
