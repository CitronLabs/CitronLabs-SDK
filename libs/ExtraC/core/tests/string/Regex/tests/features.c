#include "../Regex.h"


TEST(REGEX_FEATURES){
	//		    Test Name			Input Text     Regex	Expected Found
	CHECK_REGEX_RESULT("Exact Match", 		"abc", 	       "abc",      	1);
	CHECK_REGEX_RESULT("No Match", 			"abc", 	       "xyz",      	0);
	CHECK_REGEX_RESULT("Wildcard Match", 		"a.c", 	       "a.c",      	1);
	CHECK_REGEX_RESULT("List Match (any character)","cat", 	       "[cabr]at", 	1);
	CHECK_REGEX_RESULT("List No Match", 		"dog", 	       "[cabr]at", 	0);
	CHECK_REGEX_RESULT("Range Match (lowercase)", 	"d",   	       "[a-z]",    	1);
	CHECK_REGEX_RESULT("Range Match (uppercase)", 	"F",   	       "[A-Z]",    	1);
	CHECK_REGEX_RESULT("Range No Match", 		"1",           "[a-z]",    	0);
	CHECK_REGEX_RESULT("Escaped Dot", 		"file.txt",    "file\\.txt", 	1);
	CHECK_REGEX_RESULT("Escaped Bracket", 		"file[1].txt", "file\\[1].txt", 1);
	CHECK_REGEX_RESULT("Escaped Backslash", 	"\\", "\\\\", 			1);
	CHECK_REGEX_RESULT("Multiple Wildcard Matches", "a.c a.c",     "a.c", 		2);



skip:

return TEST_RESULT;
}


