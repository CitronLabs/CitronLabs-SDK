/*
ExtraC CORE Configuration File
*/

#if defined (			__ERROR_CODES__				)
/*---------------------------------------------------------------------------*/
	ERR_NONE, ERR_INVALID, ERR_NULLPTR, ERR_INITFAIL, 
	ERR_NOTIMPLEM, ERR_FAIL,

	ERR_SEGFAULT, ERR_ABORT,

	DATAERR_MEMALLOC, DATAERR_SIZETOOLARGE, 	
	DATAERR_OUTOFRANGE,DATAERR_LIMIT, 		
	DATAERR_EMPTY, DATAERR_DSN,		

	MEMERR_OVERFLOW, MEMERR_INITFAIL, MEMERR_LEAK, MEMERR_INVALIDSIZE,	

	STRINGERR_REGEX,STRINGERR_FORMAT,

	#include "./xc-os.c"
	#include "./xc-resource.c"

#elif defined( 			__FORMAT_CODES__			)
/*---------------------------------------------------------------------------*/
#ifndef FORMAT
#define FORMAT(domain, default, ...)
#endif	
	       	FORMAT(NUM, NUM_REG,
	     		NUM_REG, NUM_HEX, NUM_FLOAT, NUM_BIN)

		FORMAT(STRING, STRING_REG,
			STRING_REG, STRING_WORD, STRING_NUM)
		
		FORMAT(DATA, DATA_DSN,
			DATA_DSN, DATA_DEBUG)
	
	#include "./xc-os.c"
	#include "./xc-resource.c"

#undef FORMAT
#elif defined( 			__GLOBAL_METHODS__			)
/*---------------------------------------------------------------------------*/
#include "./xc-resource.c"

#define CORE_METHODS(Class)							\	
	u32 imethod(__HASH);							\
	u32 imethod(__DESTROY);							\
	RESOURCE_METHODS(Class)							\
	
#else
/*---------------------------------------------------------------------------*/
#ifndef XC_CORE_CONFIG
#define XC_CORE_CONFIG
#include "__config_start.h"

define(XC_DataStructs){
	value maxSize;
}; 
global bool(*__Init_Func)()		= NULL; 
global setting __AutoInit 		= true;
global setting __HeaderOnly		= false;

global setting __Debug 			= true;

global setting __HijackMalloc 		= true;

global setting __DataAutoGrow		= true;

global config(XC_DataStructs) 
__List = { 
	.maxSize 			= INT64_MAX
},
__Queue = { 
	.maxSize 			= INT64_MAX
},
__Stack = { 
	.maxSize 			= INT64_MAX
},
__Map = { 
	.maxSize 			= INT64_MAX
};

#include "__config_end.h"
#endif
#endif

