#pragma once
#include "./extern.h"
#include "types.h"

Decl(Display);
extern inst(Display) root_display;

Interface(Render,
	errvt imethod(setDisplay,, inst(Display) display);
	errvt imethod(renderFrame);
)


Class(Surface,
__INIT(inst(Display) display),
__FIELD(), 

);


Class(Display, 
__INIT(inst(Display) parent; char* name; u64 w,h,x,y),
__FIELD(inst(Display) parent; char* name; u64 w,h,x,y),
      	errvt 		method(Display, addChild,, inst(Display) display);
      	errvt 		method(Display, update);
      	errvt 		method(Display, setBuffers,, inst(Surface) back, inst(Surface) front);
      	errvt 		method(Display, swapBuffers);
      	inst(Surface) 	method(Display, createSurface);
	bool 		method(Display, isRunning);
	
)
Class(Vulkin,
__INIT(),
__FIELD(),
	interface(Render);
)
void test(){

	inst(Display) window = new(Display,
		.parent = root_display,
		.name = "Test Window :)"
	);

	if(!isinit(window)){
		ERR(ERR_INITFAIL, "window is not initialize");
		return;
	}

	check(
	Display.setBuffers(window,
		push(Surface, window),
		push(Surface, window)
	)){
		ERR(ERR_INITFAIL, "failed to set window buffers");
	}

	inst(Vulkin) vk = new(Vulkin);
	
	Vulkin.Render.setDisplay(generic vk, window);
	
	while(Display.isRunning(window)){
		
		Vulkin.Render.renderFrame(generic vk);
	}
}
