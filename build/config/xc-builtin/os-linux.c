/*
ExtraC OS Linux Configuration File
*/

#if defined (			__ERROR_CODES__				)
/*---------------------------------------------------------------------------*/
#elif defined( 			__FORMAT_CODES__			)
/*---------------------------------------------------------------------------*/
#elif defined( 			__GLOBAL_METHODS__			)
/*---------------------------------------------------------------------------*/
#else
/*---------------------------------------------------------------------------*/
#ifndef XC_OSLINUX_CONFIG
#define XC_OSLINUX_CONFIG
#include "../__config_start.h"

enum LinuxWindowENV{ WINENV_X11, WINENV_WAYLAND};

global value WindowAPI = WINENV_X11; 

#include "../__config_end.h"
#endif
#endif

