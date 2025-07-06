#include "./xc_additions.h"
#include "../include/std-all.h"
#include "./error/error.c"
#include "./data/data.c"
#include "./thread/thread.c"
#include "./network/network.c"
#include "./ext/io/io.c"
#include "./ext/string/string.c"
#include "./ext/time/time.c"
#include "./ext/malloc/malloc.c"


__start{

	println(YELLOW"--Extra C Tests--"NC);
	RUN_STDERROR_TESTS();
	RUN_STDEXTMALLOC_TESTS();
	RUN_STDDATA_TESTS();
	RUN_STDTHREAD_TESTS();
	RUN_STDEXTIO_TESTS();
	RUN_STDEXTSTRING_TESTS();
	RUN_STDEXTTIME_TESTS();

return 0;
}

