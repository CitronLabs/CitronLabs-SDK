#pragma once
#include "ebee.h"
#include "build_config.h"
#include "ebee-modules/compileC.h"
#include "ebee-modules/autoRebuild.h"


void compileMemtree(){
compileC_result	memtree_lib = {0};
	
	compileC_blueprint memtree_blueprint = {
		.cc = s(CC),
		.srcfiles = listLiteral(std_str,
			s(STD_DIR "/memtree/src/data.c"),
			s(STD_DIR "/memtree/src/leaf.c"),
			s(STD_DIR "/memtree/src/nodes.c"),
			s(STD_DIR "/memtree/src/tokens.c"),
		),
		.includes = listLiteral(std_str,
			s(STD_DIR "/memtree/include"),
			s(STD_DIR "/extra-c/include")
		)
	};
	
	memtree_lib = C_blueprint_compile(&memtree_blueprint,
				(std_str){0},
				CCFL_DO_COMPILE_ONLY); 
	
	
    	C_result_linkLib(s("ar rcs"),
		memtree_lib.output,
		s("libmemtree.a")	    	
     	);
	
}

void compileMemtreeTests(){
compileC_result memtree_tests = {0};
	
	compileC_blueprint memtree_blueprint = {
		.cc = s(CC),
		.includes = listLiteral(std_str,
			s(STD_DIR "/extra-c/include"),
			s(STD_DIR "/memtree/include"),
		),
		.srcfiles = listLiteral(std_str,
			s(STD_DIR "/memtree/tests/main.c")
		),
		.libs = listLiteral(std_str,
			s("memtree")
		      )
	};

	memtree_tests = C_blueprint_compile(&memtree_blueprint,
				s("memtree_tests"), 
				CCFL_DO_EVERYTHING);
}

errvt build_memtree(){
	errvt error = ERR_NONE;
	
	checkautoRebuild(__FILE__);

	EBEE_TARGET memtree = {
		.target_name = s("memtree"),
		.steps = listLiteral(EBEE_STEP,
		       compileMemtree,
		       compileMemtreeTests
		)
	};

	checkreturnerr((error = eb_register_target(memtree)) != ERR_NONE,
		error, "Failed to register memtree target");

return error;
}
