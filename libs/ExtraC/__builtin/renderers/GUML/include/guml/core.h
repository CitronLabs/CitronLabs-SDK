#pragma once
#include "../extern.h"

Class(GumlPage,
__INIT(),
__FIELD(Color background),
#define Layout					\
for( 						\
	errvt error = 				\
	GumlPage.layoutStart()			\
	;					\
	!error					\
	;					\
	error = GumlPage.layoutEnd()		\
)

#define Page(name) Page name = new(GumlPage);	\
for( 						\
	errvt error = 				\
	GumlPage.start(name)			\
	;					\
	!error					\
	;					\
	error = GumlPage.end()			\
)

      	errvt method(GumlPage, start);
      	errvt vmethod(end);
      	errvt vmethod(layoutStart);
      	errvt vmethod(layoutEnd);
)
typedef inst(GumlPage) Page;
