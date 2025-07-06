#include "./data.h"

bool RUN_QUEUE_TESTS(){


NEW_TEST("Queue Data Structure"){

	Queue(char) queue = NULL;

	NEW_SUBTEST("Initialization"){
		queue = pushQueue(c8);
		if(!isinit(queue)){
			FAIL_TEST
			goto skip;
		}else
			PASS_TEST
	}
	NEW_SUBTEST("Enqueuing"){
		if(Queue.Enqueue(queue, "Hello, World!", sizeof("Hello, World!")) != ERR_NONE ){
			FAIL_TEST
			goto skip;
	    	}
		if(!(Queue.Check(queue))){
			FAIL_TEST
			goto skip;
		}
			PASS_TEST
	}
	NEW_SUBTEST("Dequeuing"){
		char queue_data[sizeof("Hello, World!")] = {0};
		
		if(Queue.Dequeue(queue, queue_data, sizeof("Hello, World!")) != ERR_NONE ){
			FAIL_TEST
			goto skip;
		}
		if(Queue.Check(queue)){
			FAIL_TEST
			goto skip;
		}
		if(strncmp(queue_data, "Hello, World!", sizeof("Hello, World!")) != 0){
			println(queue_data);
			FAIL_TEST
			goto skip;
		}
			PASS_TEST
	}
	NEW_SUBTEST("Freeing"){
		pop(queue);
		if(errnm != ERR_NONE ){
			FAIL_TEST
			goto skip;
		}
			PASS_TEST
	}
	NEW_SUBTEST("Initialize Literal"){
		char queue_data[sizeof("Hello, World!")] = {0};
		

		queue = pushQueue(c8, 'H','e','l','l','o',',',' ','W','o','r','l','d');

		if(queue == NULL){
			FAIL_TEST
			goto skip;
		}
		if(!(Queue.Check(queue))){
			FAIL_TEST
			goto skip;
		}
		if(Queue.Dequeue(queue, queue_data, sizeof("Hello, World!")) != ERR_NONE ){
			FAIL_TEST
			goto skip;
		}
		if(Queue.Check(queue)){
			FAIL_TEST
			goto skip;
		}
		if(strncmp(queue_data, "Hello, World!", sizeof("Hello, World!")) != 0){
			FAIL_TEST
			goto skip;
		}
		pop(queue);
		if(errnm != ERR_NONE ){
			FAIL_TEST
			goto skip;
		}
			PASS_TEST
	}
}
skip:



return TEST_RESULT;


}
