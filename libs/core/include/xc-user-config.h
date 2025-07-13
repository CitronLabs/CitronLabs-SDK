#pragma once
#include "std-libc.h"

/*----------------------|
      xc-settings	|
-----------------------*/
#define SET_DOAUTOINIT  		true
#define SET_HEADERONLY 			false

/*----------------------|
	std-error	|
-----------------------*/
#define STDERR_DEBUG_MODE  		false


/*----------------------|
	 std-data	|
-----------------------*/
#define STDDATA_AUTOGROW  		true
#define STDDATA_MAP_OVERIDEHASH  	false

#define STDDATA_LIST_GROWTHFACTOR(items_alloced) (items_alloced + (items_alloced / 2))


/*----------------------|
      stdext-malloc	|
-----------------------*/

#define STDMALLOC_HIJACKMALLOC  	true



/*----------------------|
        stdext-io	|
-----------------------*/
#define STDIO_FILECOPY_BUFFERSIZE 4096
