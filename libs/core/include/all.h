#pragma once

#if __STDC_VERSION__ < 201112L
#error "Your compiler does not support c11 features that Extra-C requires" 
#endif

#define __EXTRAC_RUNTIME__

#include "./libc.h"
#if !defined (__FORMAT_CODES__) && !defined (__ERROR_CODES__)
	#include "config.h"
#endif

#include "./utils.h"
#include "./types.h"
#include "./error.h"
#include "./data.h"
#include "./stringutils.h"
#include "./alloc.h"
#include "./timing.h"


Enum(VersionSchema, V_SEMANTIC,	V_RELEASEDATE, V_ALPHABETA);

Type(Version,
	#define ABV_RELEASE 		0
	#define ABV_RELEASE_CANDIATE 	1
	#define ABV_BETA 		2
	#define ABV_ALPHA 		3

     	#define Version(project, _schema, ...) 				\
     		static data(Version) __##project##_Version = 		\
		{.schema = _schema, .version = (u32[]){__VA_ARGS__}	\
	}

	VersionSchema schema;
	u32* version;
);


Version(ExtraC, V_SEMANTIC, 
		0, ABV_RELEASE,		// MAJOR_VERSION
		1, ABV_ALPHA,		// MINOR_VERSION
		0, 			// PATCH_VERSION
);

Version(LibC, V_RELEASEDATE,
	#if __STDC_VERSION__ == 201112L
		2011
	#elif __STDC_VERSION__ == 201710L
		2017
	#elif __STDC_VERSION__ == 202311L
		2023
	#endif
);

#if __AutoInit 
	int extra_main(int argc, char** argv);
	#define main extra_main
	#define __start int extra_main(int arc, char** argv)
#else
	errvt init_ExtraC();
#endif

#if __HeaderOnly
#include "../src/error/errorcodes.c"

#include "../src/data/datastructs.c"
#include "../src/data/list.c"
#include "../src/data/hashmap.c"
#include "../src/data/queue.c"
#include "../src/data/stack.c"
#include "../src/data/numbers.c"

#include "../src/types/types.c"
#include "../src/types/scan.c"
#include "../src/types/format.c"

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
