/*
ExtraC RESOURCE Configuration File
*/

#if defined (			__ERROR_CODES__				)
/*---------------------------------------------------------------------------*/
	RESOURCERR_INVALID, RESOURCERR_FAIL, 		
	RESOURCERR_NOTLOADED, RESOURCERR_TOKENINDEX, 		
	RESOURCERR_TOKENCREATE, RESOURCERR_TOKENMODIFY, 	
	RESOURCERR_TOKENACCESS

#elif defined( 			__FORMAT_CODES__			)
/*---------------------------------------------------------------------------*/
#ifndef FORMAT
#define FORMAT(domain, default, ...)
#endif	

#undef FORMAT
#elif defined( 			__GLOBAL_METHODS__			)
/*---------------------------------------------------------------------------*/
typedef struct Collection_Instance Collection_Instance;

#define RESOURCE_METHODS(Class)							\
	inst(Class)(*__COLLECT)							\
		(inst(Collection) collection, Class##_ConstructArgs args);	
#else
/*---------------------------------------------------------------------------*/
#ifndef XC_RESOURCE_CONFIG
#define XC_RESOURCE_CONFIG
#include "__config_start.h"


#include "__config_end.h"
#endif
#endif

