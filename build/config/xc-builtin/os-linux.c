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


#define LinuxEnv_Display_X11 0x11
#define LinuxEnv_Display_WayLand 0x3A7

#define	__LinuxEnv_DisplayBackend LinuxEnv_Display_X11

#define LinuxEnv_Audio_PipeWire 9193

#define	__LinuxEnv_AudioBackend LinuxEnv_Audio_PipeWire

#include "../__config_end.h"
#endif
#endif

