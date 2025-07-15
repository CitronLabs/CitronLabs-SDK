#include "../include/ebee-data.h"
#include "./cli/commands.c"
#include "./core/buildenv.c"
#include "./source/source.c"
#include "./cache/cache.c"
#include "./utils/utils.c"


void default_title_screen(){
		
	PRINTLOGO

	println("--VERSIONS--");
	println("EBEE :\t", $(__eb_version));
	println("EXTRAC :\t", $(__EXTRAC_VERSION));
	println("LIBC :\t", $(__LIBC_VERSION));
}


errvt EB_setTitleScreen(void(*title_screen_func)()){
	nonull(title_screen_func, return nullerr);

	__eb_data->__private->title_screen = title_screen_func;

return OK;
}

Impl(EB){
	.rerun = EB_rerun,
	.cli = {
		.addCommand = EB_addCommand,
		.addProject = EB_addProject,
	  	.setTitleScreen = EB_setTitleScreen
	},
	.source = {
		.add
	},
	.store = {
		.cacheLoad = EB_cacheLoad,
		.cacheRemove = EB_cacheRemove,
	  	.cacheSearch = EB_cacheSearch,
	}
};



int main(int argc, char** argv){
	
	if((__eb_data = new(EB)) != ERR_NONE){
		ERR(BUILDERR_TARGETS, "could not initialize targets");
	      	return -1;
	}

	getopts(argc, argv,{
	case 'v':{
		__eb_data->__private->verbose = true;	
	break;} 
	});
	
	__eb_data->__private->argv = argv;
	
	INFO("--Running build setup function");

	if(build() != ERR_NONE){
		ERR(BUILDERR_TARGETS, "could not initialize targets");
	      	return -1;
	}

	INFO("--Reading command-line arguements");

	readCMDArgs(argc, argv);

	del(__eb_data);
return 0;
}
