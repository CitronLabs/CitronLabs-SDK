#pragma once

/*\<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>\
                                          .         .				 |
     ,o888888o.    8 8888      88        ,8.       ,8.          8 8888           |
    8888     `88.  8 8888      88       ,888.     ,888.         8 8888           |
 ,8 8888       `8. 8 8888      88      .`8888.   .`8888.        8 8888           |
 88 8888           8 8888      88     ,8.`8888. ,8.`8888.       8 8888           |
 88 8888           8 8888      88    ,8'8.`8888,8^8.`8888.      8 8888           |
 88 8888           8 8888      88   ,8' `8.`8888' `8.`8888.     8 8888           |
 88 8888   8888888 8 8888      88  ,8'   `8.`88'   `8.`8888.    8 8888           |
 `8 8888       .8' ` 8888     ,8P ,8'     `8.`'     `8.`8888.   8 8888           |
    8888     ,88'    8888   ,d8P ,8'       `8        `8.`8888.  8 8888           |
     `8888888P'       `Y88888P' ,8'         `         `8.`8888. 8 888888888888   |
										 |
<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>*/

#include "../../core.h"
#include "../../os.h"


Decl(GumlPage)

Class(guml,
__INIT(inst(Display) display),
__FIELD(),
      	interface(Render);
	errvt method(guml, setPage,, inst(GumlPage) page);
)

/*\------------------|
    INIT FUNCTIONS   |
/------------------*/

errvt GXsys_GUML_rendererloader(va_list user_args);

/*\------------------|
         GUML        |
/------------------*/
#ifdef __GUML

#define	_CUSTOM_ 0x00
#define	_SIMPLE_ 0x01
#define	_INVOVLED_ 0x02


#define	_OPENGL_ 0x01
#ifdef USE_DEFAULTS
	#define __PROFILE _SIMPLE_
	#define __GFXAPI _OPENGL_
#endif

#if defined(__PROFILE) && defined(__GFXAPI)
#if __PROFILE == _SIMPLE_
	#include "guml/componants.h"
	#include "guml/render.h"

#elif __PROFILE == _INVOLVED_
	#include "guml/elements.h"
	#include "guml/componants.h"
	#include "guml/render.h"
#elif __PROFILE == _CUSTOM_
#endif

#ifdef BUILTINS
#include "guml/builtins.h"
#endif

#endif
#endif









