#include "../libs/APIs/ebee/core.h"
#include "../libs/__builtin/ebee-modules/Langs/langs/Lang-C.h"
#include "config/build.c"

errvt BUILD_EBEE(inst(EB_Project) ebee){
	EB.source.depRequire(
		l("extrac")
	);

	INFO("Building Ebee...")
	
	inst(CBuild) build = new(CBuild,
		.cc = CC,
		.libs = l("extrac-core"),
		.srcfiles = l(
			cat(PROJECT_PATH, "/libs/build/src/ebee.c")->txt
		)
	);

	CBuild.compile(build, NULL, CCFL_DO_COMPILE_ONLY);

	check(){return ERR(err->errorcode, err->message);}

	INFO("Built Ebee!")

return OK;
}

errvt build(){
	
	inst(EB_Project) ExtraC = new(EB_Project,
		.name = "extrac",
		.project_dir = PROJECT_PATH,
		.build_dir = "/build",
		.tasks = l(
			task(S("build"), BUILD_EBEE)
		)
	);
	
	inst(EB_Project) Ebee = new(EB_Project,
		.name = "ebee",
		.project_dir = PROJECT_PATH,
		.build_dir = "/build",
		.tasks = l(
			task(s("build"), BUILD_EBEE)
		)
	);
	
return OK;
}
