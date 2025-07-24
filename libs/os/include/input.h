#pragma once
#include "./extern.h"
#include "types.h"

Type(Vector,
	float x,y,z;
)
Static(VectorUtils,

)

typedef struct{data(Vector) pos; float max, min;}* posData;
Interface(PosDevice,
	posData imethod(get);	
	errvt imethod(update,, posData pos);	
)

typedef struct{u32 code; bool cont;} keyCode;
Interface(KeyDevice,
	keyCode imethod(get);
)

Class(Mouse,
__INIT(),
__FIELD(inputHandle handle),
      	#define MOUSEBUTTON_LEFT  0
      	#define MOUSEBUTTON_RIGHT 1
	interface(PosDevice);
	bool method(Mouse, buttonPressed,, u32 buttonID);
)

Class(Keyboard,
__INIT(),
__FIELD(inputHandle handle),
      	interface(KeyDevice);
)




