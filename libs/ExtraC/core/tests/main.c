#include "../../APIs/XC/core.h"
#include "./error/error.c"
#include "./data/data.c"
#include "./string/string.c"
#include "./time/time.c"
#include "./malloc/malloc.c"

int main(){

	loginfo(YELLOW"--Extra C Tests--"NC);
	RUN_STDERROR_TESTS();
	RUN_STDEXTMALLOC_TESTS();
	RUN_STDDATA_TESTS();
	RUN_STDEXTSTRING_TESTS();
	RUN_STDEXTTIME_TESTS();

return 0;
}

