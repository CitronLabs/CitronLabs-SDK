#pragma once
/*
#if __STDC_VERSION__ < 201112L
#error "Your compiler does not support c11 features that Extra-C requires" 
#endif
*/

#include "std-libc.h"
#ifndef __USER_CONFIG__
#include "xc-user-config.h"
#endif
#include "std-utils.h"
#include "std-types.h"
#include "std-thread.h"
#include "std-error.h"
#include "std-data.h"
#include "stdext-string.h"
#include "std-network.h"
#include "stdext-io.h"
#include "stdext-malloc.h"
#include "stdext-time.h"

#define __EXTRAC_RUNTIME__

typedef enum{ 
	V_SEMANTIC,
	V_RELEASEDATE,
	V_ALPHABETA,
	V_SEMANTICWBUILD
}version_schema;

#define ABV_RELEASE 0
#define ABV_RELEASE_CANDIATE 1
#define ABV_BETA 2
#define ABV_ALPHA 3

Type(Version,
	version_schema schema;
	u32* version;
);


static data(Version) __EXTRAC_VERSION = {
	.schema = V_ALPHABETA,
	.version = (u32[]){
		0, ABV_RELEASE,		// MAJOR_VERSION
		1, ABV_ALPHA,		// MINOR_VERSION
		0, 			// PATCH_VERSION
	} 
};

static data(Version) __LIBC_VERSION = {
	.schema = V_RELEASEDATE,
	.version = (u32[]){
		#if __STDC_VERSION__ == 201112L
			2011
		#elif __STDC_VERSION__ == 201710L
			2017
		#elif __STDC_VERSION__ == 202311L
			2023
		#endif
	} 
};

typedef bool(*__init_func)();
static const __init_func __USER_INIT__ = 
	#ifdef __USER_INIT_FUNC__
		__USER_INIT_FUNC__
	#else 
		NULL
	#endif
;

#if SET_DOAUTOINIT
	int extra_main(int argc, char** argv);
	#define main extra_main
	#define __start int extra_main(int arc, char** argv)
#else
	errvt init_ExtraC();
#endif

#if SET_HEADERONLY

#include "../src/error/errorcodes.c"

#include "../src/data/datastructs.c"
#include "../src/data/list.c"
#include "../src/data/hashmap.c"
#include "../src/data/queue.c"
#include "../src/data/stack.c"
#include "../src/data/numbers.c"

#include "../src/thread/thread.c"

#include "../src/network/network.c"

#include "../src/types/types.c"
#include "../src/types/scan.c"
#include "../src/types/format.c"

#include "../src/ext/io/io.c"
#include "../src/ext/malloc/mem.c"

#include "../src/ext/time/time.c"
#include "../src/ext/time/watch.c"
#include "../src/ext/time/print-scan.c"

#include "../src/ext/string/print-scan.c"
#include "../src/ext/string/regex.c"
#include "../src/ext/string/string.c"
#include "../src/ext/string/strbuilder.c"

#include "../src/init.c"

#endif
