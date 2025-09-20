#include "../List.h"

TEST(LIST_ERRORS){
	List(int) test_list = pushList(int, 10);
	
	NEW_SUBTEST("Append with NULL data"){
		errnm = ERR_NONE;
		List.Append(test_list, NULL, 5);
		if (errnm == ERR_NULLPTR) {
		    PASS_TEST
		} else {
		    FAIL_TEST
		}
	}
		
	NEW_SUBTEST("Insert with out of bounds index"){
		errnm = ERR_NONE;
		List.Insert(test_list, 100, 1, (int[]){1});
		if (errnm == DATAERR_OUTOFRANGE) {
		    PASS_TEST
		} else {
		    FAIL_TEST
		}
	}
	
	NEW_SUBTEST("Get Pointer on empty list"){
		pop(test_list);
		test_list = pushList(int, 10);
		if (List.GetPointer(test_list, 0) == NULL) {
		    PASS_TEST
		} else {
		    FAIL_TEST
		}
	}
	
	NEW_SUBTEST("Pop on empty list"){
		errnm = ERR_NONE;
		List.Pop(test_list, 1);
		if (errnm == DATAERR_EMPTY) {
		    PASS_TEST
		} else {
		    FAIL_TEST
		}
	}
		
	NEW_SUBTEST("SetFree with invalid index"){
		errnm = ERR_NONE;
		List.SetFree(test_list, 100);
		if (errnm == DATAERR_OUTOFRANGE) {
		    PASS_TEST
		} else {
		    FAIL_TEST
		}
	}
	
	NEW_SUBTEST("Reserve beyond limit"){
		errnm = ERR_NONE;
		List.Limit(test_list, 5);
		List.Reserve(test_list, RESERVE_EXACT, 10);
		if (errnm == DATAERR_LIMIT) {
		    PASS_TEST
		} else {
		    FAIL_TEST
		}
	}
 
pop(test_list);

return TEST_RESULT;
}
