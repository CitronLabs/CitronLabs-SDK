/*
ExtraC CORE Configuration File
*/

#if defined (			__ERROR_CODES__				)
/*---------------------------------------------------------------------------*/
	ERR_NONE, ERR_INVALIDERR, ERR_NULLPTR, 	ERR_INITFAIL, 
	ERR_NOTIMPLEM,

	ERR_SEGFAULT, ERR_ABORT,

	DATAERR_MEMALLOC, DATAERR_SIZETOOLARGE, 	
	DATAERR_OUTOFRANGE,DATAERR_LIMIT, 		
	DATAERR_EMPTY, DATAERR_DSN,		

	MEMERR_OVERFLOW, MEMERR_INITFAIL, MEMERR_LEAK, MEMERR_INVALIDSIZE,	

	STRINGERR_REGEX,STRINGERR_FORMAT,

	#include "./xc-os.c"

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

#undef FORMAT
#else
/*---------------------------------------------------------------------------*/
#ifndef XC_CORE_CONFIG
#define XC_CORE_CONFIG
#include "__common.h"

define(XC_DataStructs){
	setting autoGrow;
	value maxSize;
}; 

global setting __AutoInit 		= true;
global setting __HeaderOnly		= false;

global setting __Debug 			= true;

global setting __HijackMalloc 		= true;

global config(XC_DataStructs) 
__List = { 
	.autoGrow 			= true,
	.maxSize 			= UINT64_MAX
},
__Queue = { 
	.autoGrow 			= true,
	.maxSize 			= UINT64_MAX
},
__Stack = { 
	.autoGrow 			= true,
	.maxSize 			= UINT64_MAX
},
__Map = { 
	.autoGrow 			= true,
	.maxSize 			= UINT64_MAX
};


#endif
#endif

