/*
ExtraC RESOURCE Configuration File
*/

#if defined (			__ERROR_CODES__				)
/*---------------------------------------------------------------------------*/
	ROUTINEERR_RUN,	ROUTINEERR_INIT, ROUTINEERR_ALRDYACTIVE,	


#elif defined( 			__FORMAT_CODES__			)
/*---------------------------------------------------------------------------*/
#ifndef FORMAT
#define FORMAT(domain, default, ...)
#endif	

#undef FORMAT
#elif defined( 			__GLOBAL_METHODS__			)
/*---------------------------------------------------------------------------*/

#else
/*---------------------------------------------------------------------------*/
#ifndef XC_RESOURCE_CONFIG
#define XC_RESOURCE_CONFIG
#include "__config_start.h"


#include "__config_end.h"
#endif
#endif

