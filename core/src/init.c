#define EXPOSE_INIT
#define NO_AUTO_INIT

#ifndef NO_HEADERS
#include "../include/std-all.h"
#endif

#undef main
int extra_main(int argc, cstr* argv);

u64 Print_VArgs(inst(StringBuilder) builder, va_list args);
u64 Scan_VArgs(inst(String) str, va_list args);

Impl(FormatUtils){
	.FormatVArgs = Print_VArgs,
	.ScanVArgs = Scan_VArgs
};

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





