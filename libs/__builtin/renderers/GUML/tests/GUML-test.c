#include "../include/GUML.h"


inst(GumlPage) StartPage();

bool RUN_GUML_TEST(){

	inst(Display) window = new(Display,
		.name = "GUML Test",
		.x = 0, .y = 0,
		.w = 500, .h = 500,
		.parent = root_display
	);
	inst(guml) gml = new(guml, window);

	Display.run(window);

	while(Display.isRunning(window)){
		guml.setPage(gml, StartPage());	
		guml.Render.renderFrame(generic gml);
		guml.Render.swapBuffers(generic gml);
	}

return true;
}
