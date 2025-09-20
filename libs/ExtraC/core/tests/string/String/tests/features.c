#include "../String.h"

TEST(STRING_FEATURES){
	inst(String) s1 = NULL;
	inst(String) s2 = NULL;
	inst(String) s3 = NULL;

	NEW_SUBTEST("Initialization"){
		s1 = s("Hello, World!");
		s2 = s("Hello, World!");
		s3 = s("Goodbye, World!");
		if(!isinit(s1) || !isinit(s2) || !isinit(s3))
			FAIL_TEST
		else
			PASS_TEST
	}

	NEW_SUBTEST("Comparison"){
		if(String.Compare(s1, s2) != 0 || String.Compare(s1, s3) == 0)
			FAIL_TEST
		else
			PASS_TEST
	}

	NEW_SUBTEST("Copy"){
		inst(String) s4 = String.Copy(s1);
		if(!isinit(s4) || String.Compare(s1, s4) != 0)
			FAIL_TEST
		else
			PASS_TEST
		del(s4);
	}
	
	NEW_SUBTEST("Cut"){
		inst(String) cut_string = String.Cut(s1, 7, 5);
		if(String.Compare(cut_string, s("World")) != 0)
			FAIL_TEST
		else
			PASS_TEST
		del(cut_string);
	}

	NEW_SUBTEST("Concatenate"){
		inst(String) s5 = s("Hello, ");
		inst(String) s6 = s("World!");
		inst(String) cat_string = String.Cat(s5, s6);
		if(String.Compare(cat_string, s("Hello, World!")) != 0)
			FAIL_TEST
		else
			PASS_TEST
		pop(s5);
		pop(s6);
		del(cat_string);
	}

	NEW_SUBTEST("Free"){
		pop(s1);
		pop(s2);
		pop(s3);
		if(errnm != ERR_NONE)
			FAIL_TEST
		else
			PASS_TEST
	}

	NEW_SUBTEST("UTF-8 Initialization and Length") {
		inst(String) utf8_string = s("Hëllo, Wörld! 👋");
		if (utf8_string == NULL || utf8_string->len != 17) {
			FAIL_TEST
			goto skip;
		}
		PASS_TEST
		pop(utf8_string);
	}
	
	NEW_SUBTEST("UTF-8 Comparison") {
		inst(String) utf8_string1 = s("你好世界!");
		inst(String) utf8_string2 = s("你好世界!");
		inst(String) utf8_string3 = s("你好世界");
		
		if (String.Compare(utf8_string1, utf8_string2) && !String.Compare(utf8_string1, utf8_string3)) {
			PASS_TEST
		} else {
			FAIL_TEST
			goto skip;
		}
		pop(utf8_string1);
		pop(utf8_string2);
		pop(utf8_string3);
	}
	
	NEW_SUBTEST("UTF-8 to UTF-16 Conversion") {
		inst(String) utf8_string = s("Hello👋");
		inst(String) utf16_string = String.Convert(utf8_string, CHAR_UTF16);
		if (utf16_string == NULL || utf16_string->txt.type != CHAR_UTF16 || utf16_string->len != 6) {
			FAIL_TEST
			goto skip;
		}
		PASS_TEST
		pop(utf16_string);
	}
	
	NEW_SUBTEST("UTF-16 back to UTF-8") {
		inst(String) original_utf8 = s("Hello👋");
		inst(String) intermediate_utf16  = String.Convert(original_utf8, CHAR_UTF16);
		inst(String) converted_back_utf8 = String.Convert(intermediate_utf16, CHAR_UTF8);
		
		if (String.Compare(original_utf8, converted_back_utf8)) {
			PASS_TEST
		} else {
			FAIL_TEST
			goto skip;
		}
		pop(original_utf8);
		pop(intermediate_utf16);
		pop(converted_back_utf8);
	}

	NEW_SUBTEST("Cutting UTF-8 String") {
		inst(String) utf8_string = s("Hëllo, Wörld! 👋");
		String.Cut(utf8_string, 0, 7);
		
		if (utf8_string == NULL || utf8_string->len != 7 || !String.Compare(utf8_string, s("Hëllo, "))) {
			FAIL_TEST
			goto skip;
		}
		PASS_TEST
		pop(utf8_string);
	}
	
	NEW_SUBTEST("Cat UTF-8 String") {
		inst(String) str1 = s("Hello");
		inst(String) str2 = s("👋");
		inst(String) cat_str = String.Cat(str1, str2);
		if (String.Compare(cat_str, s("Hello👋"))) {
			PASS_TEST
		} else {
			FAIL_TEST
			goto skip;
		}
		pop(str1);
		pop(str2);
		del(cat_str);
	}

	
skip:

return TEST_RESULT;
}
