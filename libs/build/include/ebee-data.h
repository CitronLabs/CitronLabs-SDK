#pragma once
#include "../../APIs/ebee/core.h"

#define PRINTLOGO 				\
	println(				\
YELLOW"-----------------------------\\\n" 	\
"   	        ,-.	      \\\n"		\
"    	        \\_/            \\\n"		\
"	     _ {|||)<		\\\n"		\
"     | |	/ \\		 \\\n"		\
"  ___| |_    __ `-'__             \\\n"     	\
" / _ \\ '_ \\ / _ \\/ _ \\   	   \\\n"	\
"|  __/ |_) |  __/  __/		    \\\n"	\
" \\___|_.__/ \\___|\\___|    	     \\\n"	\
LIGHTGRAY"	'Easy' Build System" YELLOW"           \\\n"     \
"---------------------------------------\\"   \
NC	);




enum BUILD_DIRS_IDS{ BINARY_OUT, BUILD_FILES };

enum BUILD_FILES_IDS{ BUILD_DATA, DEPENDENCY_DATA };

static cstr* argv;
static void fn(title_screen);
static struct{ u8 verbose : 1; } flags;

Data(EB_Env,
__INIT(inst(String) path),
	Map(String, intf(Project)) targets;		

	Map(String, Struct) caches[COMPILE_CACHE + 1];
);



void default_title_screen();

void readCMDArgs(int argc, char** argv);

