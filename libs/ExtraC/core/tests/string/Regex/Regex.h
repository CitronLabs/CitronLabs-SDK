#include "../stringutils.h"


// Define a helper macro for checking regex results
#define CHECK_REGEX_RESULT(test_name, input_str, regex_pattern, expected_matches) 		\
    NEW_SUBTEST(test_name) { 									\
        inst(String) test_string = s(input_str); 						\
        inst(String) regex = s(regex_pattern); 							\
        str_regex_result result_buffer[10]; 							\
        int matches = String.Regex(test_string, regex, result_buffer, 10); 			\
        if (matches != expected_matches) { 							\
            FAIL_TEST; 										\
            loginfo("FAIL: Expected ", $(expected_matches), " matches, got ", $(matches)); 	\
            goto skip; 										\
        } 											\
        PASS_TEST; 										\
    }
