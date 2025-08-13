#pragma once
#include "./interface.h"


typedef struct Color Color;
Interface(ColorEncoding,
	Color imethod(toRGBA);
	errvt imethod(fromRGBA,, Color color);
)

Type(Color,
      	#define RGBA(r,g,b,a) (data(Color)){((float)r/255.0),((float)g/255.0),((float)b/255.0),((float)a/255.0)}
 	float r,g,b,a;
);

Decl(Display);
extern inst(Display) defaultDisplay;

Interface(Render,
	errvt imethod(setDisplay,, inst(Display) display);
	errvt imethod(renderFrame);
      	errvt imethod(swapBuffers);
)


#define DISPLAY_SIZE 0x01
#define DISPLAY_POS  0x02
Class(Display, 
__INIT(inst(Display) parent; char* name; u64 w,h,x,y;),
__FIELD(inst(Display) parent; char* name; u64 w,h,x,y),
      	errvt 		method(Display, addChild,, inst(Display) display);
      	errvt 		method(Display, update);
      	errvt 		method(Display, run);
      	errvt 		method(Display, stop);
      	errvt 		method(Display, lock,,  u8 attrb_to_lock);
	bool 		method(Display, isRunning);
	graphicsHandle  method(Display, getHandle);
	
)
