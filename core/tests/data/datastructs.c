#include "./data.h"

bool verifyTestMap(Map(inst(String), inst(Number)) test_map, inst(String) test_str, inst(Number) test_num){

	inst(Number)* res = Map.Search(test_map, test_str);

	if(!res) return false;

return (*res)->as_double == test_num->as_double;
}

bool RUN_DATASTRUCTS_TESTS(){

NEW_TEST("Generic Data Structure"){

	inst(String) test_str = s("Hello, World!");
	inst(Number) test_num = n(123.321);
	
	Map(String, Number) test_map = pushMap(String, Number,
		{test_str, test_num}
	);
	
	inst(Struct) test_struct = NULL;
	inst(StringBuilder) struct_format = NULL;

	NEW_SUBTEST("Initialization"){
		
		test_struct = struct(push, 
				D("string", test_str), 
				D("number", test_num), 
				D("map",    test_map)
		);
		
		if(test_struct == NULL){
			FAIL_TEST
			goto skip;
		}else
			PASS_TEST
	}
	NEW_SUBTEST("Init Verification"){

		DSN_data* data = Struct.SearchField(test_struct, s("string"));
		if(data == NULL){
			FAIL_TEST
			goto skip;
		}
		if(data->type != DSN_STRING && 
		  ((inst(String))data->data)->txt != test_str->txt)
		{
			FAIL_TEST
			goto skip;
		}
		data = Struct.SearchField(test_struct, s("number"));
		if(data == NULL){
			FAIL_TEST
			goto skip;
		}
		if(data->type != DSN_NUMBER && 
			*((inst(Number)*)data->data) != test_num)
		{
			FAIL_TEST
			goto skip;
		}
		data = Struct.SearchField(test_struct, s("map"));
		if(data == NULL){
			FAIL_TEST
			goto skip;
		}
		if(data->type != DSN_MAP &&
	   		verifyTestMap(data->data, 
		    		test_str, 
		    		test_num)
		){
			FAIL_TEST
			goto skip;
		} 
			PASS_TEST
	}
}

skip:

return TEST_RESULT;
}
