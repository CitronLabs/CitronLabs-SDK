#pragma once
#include "./extern.h"
#include "types.h"

typedef struct{float x, y, z, max, min;}* posData;
Interface(Position,
	posData imethod(get);	
	errvt imethod(update,, posData pos);	
)

typedef struct{u32 code; bool cont;} keyCode;
Interface(Key,
	keyCode imethod(get);
)

Class(Mouse,
__INIT(),
__FIELD(inputHandle handle),
      	#define MOUSEBUTTON_LEFT  0
      	#define MOUSEBUTTON_RIGHT 1
	interface(Position);
	bool method(Mouse, buttonPressed,, u32 buttonID);
)

Class(Keyboard,
__INIT(),
__FIELD(inputHandle handle),
      	interface(Key);
)




