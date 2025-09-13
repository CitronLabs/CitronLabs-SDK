#include "maths.h"
#if defined (__x86_64__) 
	#include "SIMD/x86_64/math.c"
	#include "SIMD/x86_64/bits.c"
	#include "SIMD/x86_64/cmp.c"
	#include "SIMD/x86_64/move.c"
#endif

static inline void vmethodimpl(SIMD, Add,   SIMDVec* a, SIMDVec* b, SIMDVec* result){}	
static inline void vmethodimpl(SIMD, Sub,   SIMDVec* a, SIMDVec* b, SIMDVec* result){}	
static inline void vmethodimpl(SIMD, Mul,   SIMDVec* a, SIMDVec* b, SIMDVec* result){}	
static inline void vmethodimpl(SIMD, Div,   SIMDVec* a, SIMDVec* b, SIMDVec* result){}	
static inline void vmethodimpl(SIMD, And,   SIMDVec* a, SIMDVec* b, SIMDVec* result){}	
static inline void vmethodimpl(SIMD, Or,    SIMDVec* a, SIMDVec* b, SIMDVec* result){}	
static inline void vmethodimpl(SIMD, Xor,   SIMDVec* a, SIMDVec* b, SIMDVec* result){}	
static inline void vmethodimpl(SIMD, Cmp,   numEquality cmpFlags, SIMDVec* a, SIMDVec* b, SIMDVec* result){}	
static inline void vmethodimpl(SIMD, Move,  SIMDVec* vec, SIMDVec* output){}	
static inline void vmethodimpl(SIMD, Store, SIMDVec* vec, void* output){}	
static inline void vmethodimpl(SIMD, Set,   SIMDVec* vec, void* output){}


const Impl(SIMD){
	.Add   = SIMD_Add,    
	.Sub   = SIMD_Sub,    
	.Mul   = SIMD_Mul,    
	.Div   = SIMD_Div,    
	.And   = SIMD_And,    
	.Or    = SIMD_Or,      
	.Xor   = SIMD_Xor,    
	.Cmp   = SIMD_Cmp,    
	.Move  = SIMD_Move,  
	.Store = SIMD_Store,
	.Set   = SIMD_Set,    
};
