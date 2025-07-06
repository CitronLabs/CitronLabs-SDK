#pragma once
#include "ebee.h"
#include "build_config.h"
#include "ebee-modules/compileC.h"
#include "ebee-modules/autoRebuild.h"


void compileRoutines(){
compileC_result	routines_lib = {0};
	
	compileC_blueprint routines_blueprint = {
		.cc = s(CC),
		.includes = listLiteral(std_str,
			s(STD_DIR "/routines/include"),
			s(STD_DIR "/extra-c/include")
		),
		.srcfiles = listLiteral(std_str,
			s(STD_DIR "/routines/src/fibers.c"),
			s(STD_DIR "/routines/src/routines.c")
		)
	};
/*FIX LATER	
	C_blueprint_addSrcDirs(&routines_blueprint, true, listLiteral(std_str,
			s(STD_DIR "/extra-c/src/data"),
			s(STD_DIR "/extra-c/src/error"),
			s(STD_DIR "/extra-c/src/ext/string")
	));
*/
	routines_lib = C_blueprint_compile(&routines_blueprint,
				(std_str){0},
				CCFL_DO_COMPILE_ONLY); 
	
	
    	C_result_linkLib(s("ar rcs"),
		routines_lib.output,
		s("libroutines.a")	    	
     	);
	
}

void compileRoutinesTests(){
compileC_result routines_tests = {0};
	
	compileC_blueprint routines_blueprint = {
		.cc = s(CC),
		.includes = listLiteral(std_str,
			s(STD_DIR "/routines/include"),
			s(STD_DIR "/extra-c/include"),
		),
		.srcfiles = listLiteral(std_str,
			s(STD_DIR "/routines/tests/main.c")
		),
		.libs = listLiteral(std_str,
			s("routines")
		      )
	};

	routines_tests = C_blueprint_compile(&routines_blueprint,
				s("routines_tests"), 
				CCFL_DO_EVERYTHING);
}

errvt build_routines(){
	errvt error = ERR_NONE;
	
	checkautoRebuild(__FILE__);

	EBEE_TARGET routines = {
		.target_name = s("routines"),
		.steps = listLiteral(EBEE_STEP,
		       compileRoutines,
		       compileRoutinesTests
		)
	};

	checkreturnerr((error = eb_register_target(routines)) != ERR_NONE,
		error, "Failed to register routines target");

return error;
}
