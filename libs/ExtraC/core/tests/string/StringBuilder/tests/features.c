#include "../StringBuilder.h"

TEST(STRINGBUILDER_FEATURES){

	inst(StringBuilder) builder = NULL;

	NEW_SUBTEST("Initialization"){
		builder = push(StringBuilder, .init_str = s("Hello"));
		if(!isinit(builder))
			FAIL_TEST
		else 
			PASS_TEST
	}
	
	NEW_SUBTEST("Append"){
		StringBuilder.Append(builder, s(", World!"));
		if(String.Compare(StringBuilder.CreateStr(builder), s("Hello, World!")) != 0)
			FAIL_TEST
		else
			PASS_TEST
	}
	
	NEW_SUBTEST("Prepend"){
		StringBuilder.Prepend(builder, s("This is a test: "));
		if(String.Compare(StringBuilder.CreateStr(builder), s("This is a test: Hello, World!")) != 0)
			FAIL_TEST
		else
			PASS_TEST
	}

	NEW_SUBTEST("Insert"){
		StringBuilder.Insert(builder, 16, s("great "));
		if(String.Compare(StringBuilder.CreateStr(builder), s("This is a great test: Hello, World!")) != 0)
			FAIL_TEST
		else
			PASS_TEST
	}
	
	NEW_SUBTEST("Replace"){
		StringBuilder.Replace(builder, s("Hello"), s("Goodbye"));
		if(String.Compare(StringBuilder.CreateStr(builder), s("This is a great test: Goodbye, World!")) != 0)
			FAIL_TEST
		else
			PASS_TEST
	}
	
	NEW_SUBTEST("Setting Max"){
		StringBuilder.Max(builder, sizeof("This is a great test") - 1);

		str_t temp = StringBuilder.GetStr(builder);
		if(!String.Compare(&temp, s("This is a great test"))){
			FAIL_TEST
			goto skip;
		}
		quiet(){
			StringBuilder.Append(builder, s(": Goodbye, World!"));

			if(errnm == OK){
				FAIL_TEST
				goto skip;
			}
		}
			PASS_TEST
	}
	
	NEW_SUBTEST("Clear"){
		StringBuilder.Clear(builder);
		if(StringBuilder.GetStr(builder).len > 0)
			FAIL_TEST
		else
			PASS_TEST
	}

	NEW_SUBTEST("UTF-8 String Creation"){
		inst(String) test_utf8 = s("你好, World!");
		if (isinit(test_utf8) && test_utf8->len == 11) {
			PASS_TEST
		} else {
			FAIL_TEST
		}
	}	
		// Test StringBuilder Append with UTF-8
	NEW_SUBTEST("StringBuilder Append with UTF-8"){

		StringBuilder.Append(builder, s("Hello "));
		StringBuilder.Append(builder, s("世界")); // "世界" is UTF-8
		
		data(String) final_utf8 = StringBuilder.GetStr(builder);
		if (String.Compare(&final_utf8, s("Hello 世界")) && final_utf8.len == 7) {
			PASS_TEST
		} else {
			FAIL_TEST
		}

		StringBuilder.Clear(builder);
	}
	// Test a basic multi-byte UTF-32 string (requires more complex setup)
	NEW_SUBTEST("UTF-32 String Handling"){
		c32 utf32_arr[] = { 'H', 'e', 'l', 'l', 'o', ' ', 0x1F600, ' ', 0x1F601, '\0' }; // 😀, 😁

		StringBuilder.Append(builder, &((String_Instance){ .txt.data.utf32 = utf32_arr, .len = 9 }));
		data(String) final_utf32 = StringBuilder.GetStr(builder);
		if (final_utf32.len == 9 && final_utf32.txt.type == CHAR_UTF32) {
			PASS_TEST
		} else {
			FAIL_TEST
		}
	}
	// Test String Comparison with mixed UTF-8 and ASCII
	NEW_SUBTEST("String Comparison with Unicode"){
		inst(String) str1_utf8 = s("café");
		inst(String) str2_utf8 = s("café");
		inst(String) str3_utf8 = s("cafe");
		if (String.Compare(str1_utf8, str2_utf8) && !String.Compare(str1_utf8, str3_utf8)) {
			PASS_TEST
		} else {
			FAIL_TEST
		}
	}
	// Test String concatenation with multi-byte characters
	NEW_SUBTEST("StringBuilder Cat with UTF-8"){
		inst(String) part1 = s("Hello, ");
		inst(String) part2 = s("こんにちは");
		inst(String) result = String.Cat(part1, part2);
		if (String.Compare(result, s("Hello, こんにちは"))) {
			PASS_TEST
		} else {
			FAIL_TEST
		}
	}
	// Test multi-byte character length validation
	NEW_SUBTEST("Multi-byte Length Validation"){
		inst(String) emoji_str = s("Hello 😀 World!");
		if (emoji_str->len == 14) {
			PASS_TEST
		} else {
			FAIL_TEST
		}
	}
	NEW_SUBTEST("Free"){
		pop(builder);
		if(errnm != ERR_NONE)
			FAIL_TEST
		else
			PASS_TEST
	}
	
skip:

return TEST_RESULT
}
