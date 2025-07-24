#define __GUML
#define USE_DEFAULTS
#define BUILTINS
#include "../include/GUML.h"

void Button(){
Layout{
	box(0){

	}
}
}

Page StartPage(){
    Page(StartScreen){
	Layout{
	    box(
		.bgcolor = RGBA(255, 255, 255, 255),	
		.round 	 = pct(0)	
	    ){
		Button();
		Button();
		Button();
	    }
	}
    }
return StartScreen;
}

