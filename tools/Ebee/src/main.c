#include "extern.h"
#include "types.h"

Type(EbeeFlags,
	u32 verbose : 1;
)

Data(EbeeArgs,
__INIT(cstr* v),
	EbeeFlags flags;
){
	for(int i = 0;;i++){
		if(args.v[i] == NULL) break;
		if(args.v[i][0] == '-'); 
	}
return self;
}

Class(EbeeTool,
__INIT(inst(EbeeArgs) args),
__FIELD(
	inst(MemoryMap) memory;
      	inst(EbeeFlags) flags;
      	
),	
      	interface(Loggable);
      	errvt method(EbeeTool, createEnv,, fsPath path);
)


int main(int argc, char **argv){
	
	inst(EbeeTool) ebee = push(EbeeTool, push(EbeeArgs, argv));


return 0;
}
