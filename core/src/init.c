#define EXPOSE_INIT
#define NO_AUTO_INIT

#ifndef NO_HEADERS
#include "../include/std-all.h"
#endif

#undef main
int extra_main(int argc, cstr* argv);

errvt init_ExtraC(){
	errvt res = ERR_NONE;
	if(__USER_INIT__ != NULL) res  = __USER_INIT__();
return res;
}

int main(int argc, cstr* argv){
	if(init_ExtraC()) return -1;

return extra_main(argc, argv);	
}
#define main extra_main





