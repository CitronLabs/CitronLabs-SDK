#include "../XC/core.h"

#define INFO(...)if(EB.getFlag(EBFL_VERBOSE)){ \
	println(WHITE,	__VA_ARGS__, NC);}


Interface(EBctl_Cli,
	errvt 	(*runCommand)(const cstr command);
	errvt 	(*addCommand)(const cstr name, void(*command));
	errvt 	(*setTitleScreen)(void(*)());
);

