#include "../DSN.h"
	
static inst(DSN) dsn_var;

TEST(DSN_FEATURES_PARSING);
TEST(DSN_FEATURES_PRINTING);
TEST(DSN_FEATURES_IMPORTING);

TEST(DSN_FEATURES){

	dsn_var = new(DSN);

	RUN_TEST(DSN_FEATURES_PRINTING){
		return TEST_RESULT;
	}

	RUN_TEST(DSN_FEATURES_PARSING){
		return TEST_RESULT;
	}

	RUN_TEST(DSN_FEATURES_IMPORTING){
		return TEST_RESULT;
	}
	
	del(dsn_var);

return TEST_RESULT;	
}


TEST(DSN_FEATURES_PARSING){
	DSN_data parsed_data = {0};
	u64 parsed_len;

	NEW_SUBTEST("Parse List"){
		inst(String) list_str = s("[1, 2, 3]");
		parsed_len = DSN.parseList(dsn_var, (inst(List)*)&parsed_data.data, list_str);
		if (parsed_len > 0 && parsed_data.type == DSN_LIST && List.Size((inst(List))parsed_data.data) == 3) {
		    PASS_TEST
		} else {
		    FAIL_TEST
		}
		pop((inst(List))parsed_data.data);
	}
	
	NEW_SUBTEST("Parse Map"){
		inst(String) map_str = s("@{\"key1\"->1, \"key2\"->2}");
		parsed_len = DSN.parseMap(dsn_var, (inst(Map)*)&parsed_data.data, map_str);
		if (parsed_len > 0 && parsed_data.type == DSN_MAP && Map.Count((inst(Map))parsed_data.data) == 2) {
		    PASS_TEST
		} else {
		    FAIL_TEST
		}
		pop((inst(Map))parsed_data.data);
	}

	NEW_SUBTEST("Parse Struct"){
		inst(String) struct_str = s("test_struct { .field1 = 1, .field2 = \"string\" }");
		parsed_len = DSN.parseStruct(dsn_var, (inst(Struct)*)&parsed_data.data, struct_str);
		if (parsed_len > 0 && parsed_data.type == DSN_STRUCT && Struct.SearchField((inst(Struct))parsed_data.data, s("field1")) != NULL) {
		    PASS_TEST
		} else {
		    FAIL_TEST
		}
		pop((inst(Struct))parsed_data.data);
	}

	NEW_SUBTEST("Parse with syntax error"){
		inst(String) error_str = s("[1, 2,"); // Missing closing bracket
		parsed_len = DSN.parseList(dsn_var, (inst(List)*)&parsed_data.data, error_str);
		if (parsed_len == 0 && errnm == DATAERR_DSN) {
		    PASS_TEST
		} else {
		    FAIL_TEST
		}
	}
return TEST_RESULT; 


}
TEST(DSN_FEATURES_PRINTING){
	inst(StringBuilder) sb = new(StringBuilder);
    
	NEW_SUBTEST("Format List"){
		List(int) list = pushList(int, 10);
		List.Append(list, (int[]){1,2,3}, 3);
		DSN.formatList(dsn_var, list, sb);
		if (strncmp(StringBuilder.GetStr(sb).txt.data.utf8, "[ 1, 2, 3 ]", 11) == 0) {
		    PASS_TEST
		} else {
		    FAIL_TEST
		}
		StringBuilder.Clear(sb);
		pop(list);
	}
	NEW_SUBTEST("Format Map"){
		Map(String, int) map = pushMap(String, int);
		int val1 = 1, val2 = 2;
		Map.Insert(map, s("key1"), &val1);
		Map.Insert(map, s("key2"), &val2);
		DSN.formatMap(dsn_var, map, sb);
		if (strncmp(StringBuilder.GetStr(sb).txt.data.utf8, "@{ \"key1\"->1, \"key2\"->2, }", 23) == 0) {
		    PASS_TEST
		} else {
		    FAIL_TEST
		}
		StringBuilder.Clear(sb);
		pop(map);
	}
	pop(sb);

}
TEST(DSN_FEATURES_IMPORTING){


}
