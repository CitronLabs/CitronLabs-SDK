#include "../Struct.h"

TEST(STRUCT_FEATURES){

	inst(String) name1 = s("name");
	inst(String) name2 = s("age");
	inst(String) name3 = s("score");
	inst(String) non_existent = s("non_existent");
	
	inst(String) test_string = s("John Doe");
	int test_int = 30;
	double test_double = 95.5;
	
	inst(Struct) person = NULL;
	
	NEW_SUBTEST("Initialization and Field Definition");
	person = pushStruct(
		D("name", test_string),
		D("age", &test_int),
		D("score", &test_double)
	);
	if (isinit(person) && Struct.SearchField(person, name1) != NULL &&
		Struct.SearchField(person, name2) != NULL &&
		Struct.SearchField(person, name3) != NULL) {
		PASS_TEST
	} else {
		FAIL_TEST
		goto skip;
	}

	NEW_SUBTEST("Search for existing fields");
	DSN_data* name_data = Struct.SearchField(person, name1);
	DSN_data* age_data = Struct.SearchField(person, name2);
	DSN_data* score_data = Struct.SearchField(person, name3);
	
	if (name_data && name_data->type == DSN_STRING &&
		age_data && age_data->type == DSN_NULL && // This is a gap, I assume DSN_NULL for non-DSN types
		score_data && score_data->type == DSN_NULL) {
		PASS_TEST
	} else {
		FAIL_TEST
		goto skip;
	}
	
	NEW_SUBTEST("Search for non-existent field");
	if (Struct.SearchField(person, non_existent) == NULL) {
		PASS_TEST
	} else {
		FAIL_TEST
		goto skip;
	}
	
	NEW_SUBTEST("Add new field");
	int new_field_val = 123;
	Struct.AddField(person, "new_field", &(DSN_data){DSN_NULL, &new_field_val});
	DSN_data* new_field_data = Struct.SearchField(person, s("new_field"));
	if (new_field_data != NULL) {
		PASS_TEST
	} else {
		FAIL_TEST
		goto skip;
	}
	
	pop(person);

skip:

return TEST_RESULT;
}
