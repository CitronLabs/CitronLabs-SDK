
void test(){

	inst(Display) window = new(Display,
		.parent = defaultDisplay,
		.name = "Test Window :)"
	);

	if(!isinit(window)){
		ERR(ERR_INITFAIL, "window is not initialize");
		return;
	}

	inst(Vulkin) vk = new(Vulkin);
	
	Vulkin.Render.setDisplay(generic vk, window);
	
	while(Display.isRunning(window)){
		
		Vulkin.Render.renderFrame(generic vk);
		Vulkin.Render.swapBuffers(generic vk);
	}
}
