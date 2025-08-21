#pragma once
#include "../../os.h"

Class(Mouse,
__INIT(),
__FIELD(),
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

static inst(Mouse) defaultMouse = NULL;
