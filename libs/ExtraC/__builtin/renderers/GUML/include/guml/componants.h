#pragma once
#include "core.h"
#include "elements.h"


Class(GumlComponant,
__INIT(inst(GumlElement) element),
__FIELD(),

#define COMPONANT_MACRO_LAYOUT(element_name,...) \
for( 						\
	errvt error = GumlComponant.pushNode( 	\
	    push(GumlComponant, 		\
	    (GumlElement*)	 		\
	    &NEW_ELEMENT(element_name,		\
		__VA_ARGS__))) 			\
	;					\
	!error					\
	;					\
	error = GumlComponant.popNode()		\
)

	errvt method(GumlComponant, pushNode);
	errvt vmethod(popNode);
)
