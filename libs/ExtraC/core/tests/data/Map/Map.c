#include "../data.h"
#include "tests/features.c"
#include "tests/errors.c"
#include "tests/cases.c"

#define printmap \
loop(i, List.Size(entries)) \
	loginfo(		\
	"hash: ", 	$(((data_entry*)List.GetPointer(entries, i))->hash), "\n", \
	"key: ",	$(((inst(String))((data_entry*)List.GetPointer(entries, i))->key)->txt), "\n", \
	"data: ",	$(*(u32*)((data_entry*)List.GetPointer(entries, i))->data), "\n" \
	);


bool RUN_MAP_TESTS(){

NEW_TEST("Map Data Structure"){

	Map(u32, String) map = NULL;
	List(data_entry) entries = NULL;
	
	u32 data[3] = {31243552, 4509302, 391204802};
	inst(String) keys[3] = {s("hi"), s("Lorem Ispbum"), s("Hello World!")};
	u32 indexes[3] = {INVALID_MAPINDEX, INVALID_MAPINDEX, INVALID_MAPINDEX};
	
	NEW_SUBTEST("Initialization"){
		map = pushMap(String, u32);

		if(isinit(map))
			PASS_TEST
		else{
			FAIL_TEST
			goto skip;
		}
	}
	NEW_SUBTEST("Getting Entries List"){
		if((entries = Map.GetEntries(map)) == NULL){
			FAIL_TEST
			goto skip;
		}
			PASS_TEST
	}
	NEW_SUBTEST("Insertion"){

		indexes[0] = Map.Insert(map, keys[0], &data[0]);
		indexes[1] = Map.Insert(map, keys[1], &data[1]);
		indexes[2] = Map.Insert(map, keys[2], &data[2]);

		if(List.Size(entries) < 3){
			FAIL_TEST
			goto skip;	
		}
			PASS_TEST
	}
	NEW_SUBTEST("Searching"){
		u32 key_index = INVALID_MAPINDEX;
		
		loop(i, 3){
		    if((key_index = Map.SearchIndex(map, keys[i])) == INVALID_MAPINDEX){

			FAIL_TEST
			goto skip;	
		    }
		    if(key_index != indexes[i]){
			FAIL_TEST
			goto skip;	
		    }
		}
			PASS_TEST
	}
	NEW_SUBTEST("Indexing"){
		u32* index_result = {0};

		loop(i, 3){
			if((index_result = Map.Index(map, indexes[i])) == NULL){
				FAIL_TEST
				goto skip;
			}
			if(*index_result != data[i]){
				FAIL_TEST
				goto skip;
			}
		}
			PASS_TEST
	}
	NEW_SUBTEST("Removing"){
		loop(i, 3){
		    if(Map.Remove(map, keys[i]) != ERR_NONE){
			FAIL_TEST
			goto skip;
		    }
		    if(((data_entry*)List.GetPointer(entries, i))->data != NULL){
			FAIL_TEST
			goto skip;
		    }
		}
			PASS_TEST
	}
	NEW_SUBTEST("Freeing"){
		pop(map);
		if(errnm != ERR_NONE ){
			FAIL_TEST
			goto skip;
		}
			PASS_TEST
	}
	NEW_SUBTEST("Initialize Literal"){
		u32* index_result = {0};
		
		map = pushMap(String, u32,
			{keys[0], &data[0]},
			{keys[1], &data[1]},
			{keys[2], &data[2]}
		);
		if(map == NULL){
			FAIL_TEST
			goto skip;
		}
		
		if((entries = Map.GetEntries(map)) == NULL){
			FAIL_TEST
			goto skip;
		}
		
		indexes[0] = Map.Insert(map, keys[0], &data[0]);
		indexes[1] = Map.Insert(map, keys[1], &data[1]);
		indexes[2] = Map.Insert(map, keys[2], &data[2]);
		
		if(List.Size(entries) < 3){
			FAIL_TEST
			goto skip;	
		}
		loop(i, 3){
			if((index_result = Map.Index(map, indexes[i])) == NULL){
				FAIL_TEST
				goto skip;
			}
			if(*index_result != data[i]){
				FAIL_TEST
				goto skip;
			}
		}
		pop(map);
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
