#include "maths.h"
#if defined (__x86_64__) 
	#include "SIMD/x86_64/math.c"
	#include "SIMD/x86_64/bits.c"
	#include "SIMD/x86_64/cmp.c"
	#include "SIMD/x86_64/move.c"
#endif

private(SIMD,)

void methodimpl(SIMD, Add,,   inst(SIMD) b, inst(SIMD) result){}	
void methodimpl(SIMD, Sub,,   inst(SIMD) b, inst(SIMD) result){}	
void methodimpl(SIMD, Mul,,   inst(SIMD) b, inst(SIMD) result){}	
void methodimpl(SIMD, Div,,   inst(SIMD) b, inst(SIMD) result){}	
void methodimpl(SIMD, And,,   inst(SIMD) b, inst(SIMD) result){}	
void methodimpl(SIMD, Or,,    inst(SIMD) b, inst(SIMD) result){}	
void methodimpl(SIMD, Xor,,   inst(SIMD) b, inst(SIMD) result){}	
void methodimpl(SIMD, Not,,   inst(SIMD) result){}	
void methodimpl(SIMD, Cmp,,   inst(SIMD) b, inst(SIMD) result, numEquality cmpFlags){}	
void methodimpl(SIMD, Move,,  inst(SIMD) output){}	
void methodimpl(SIMD, Store,, void* output){}	
void methodimpl(SIMD, Set,,   void* output){}

construct(SIMD,
	.Add   = SIMD_Add,    
	.Sub   = SIMD_Sub,    
	.Mul   = SIMD_Mul,    
	.Div   = SIMD_Div,    
	.And   = SIMD_And,    
	.Or    = SIMD_Or,      
	.Xor   = SIMD_Xor,    
	.Not   = SIMD_Not,    
	.Cmp   = SIMD_Cmp,    
	.Move  = SIMD_Move,  
	.Store = SIMD_Store,
	.Set   = SIMD_Set    
){
	if(args.bitwidth == 0) { 
		ERR(ERR_INVALID, "SIMD bitwidth cannot be 0");
		return NULL; 
	}

	switch(args.bitwidth){
	case 1 ... 8:{
		
	break;}
	}

return self;
}
