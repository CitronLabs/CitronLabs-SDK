#pragma once
#include "error.h"
#include "types.h"
#include "stringutils.h"

#define N(number) new(Number,  #number)
#define n(number) push(Number, #number)


Enum(numEquality,
     	NUM_NULL    = 0,
	NUM_EQUALS  = 1,
	NUM_GREATER = 2,
	NUM_LESSER  = 4,
	NUM_NOT     = 8
)

Class(Number,
__INIT(cstr initVal),
__FIELD(),
	interface(Formatter);
    	
	//Number Float Casts
      	errvt  method(Number, castToBigFloat);
      	double method(Number, castToLongFloat);
      	float  method(Number, castToFloat);

	//Number Int Casts
      	errvt  method(Number, castToBigInt);
      	u64    method(Number, castToLongInt);
      	u32    method(Number, castToInt);

	//Number Utils
	errvt  method(Number, setPrecision,,   u64 precision);
	bool   method(Number, isFloat);
	errvt  method(Number, setZero);
	
      	//Number Operations
 	errvt method(Number, AddInto,,      inst(Number) a, inst(Number) b);
	errvt method(Number, SubtractInto,, inst(Number) a, inst(Number) b);
	errvt method(Number, MultiplyInto,, inst(Number) a, inst(Number) b);
    	errvt method(Number, DivideInto,,   inst(Number) a, inst(Number) b, inst(Number) remainder);
 	
      	inst(Number) method(Number, Add,,      inst(Number) other);
	inst(Number) method(Number, Subtract,, inst(Number) other);
	inst(Number) method(Number, Multiply,, inst(Number) other);
    	inst(Number) method(Number, Divide,,   inst(Number) other, inst(Number) remainder);
    	
      	numEquality  method(Number, Compare,,  inst(Number) other);
);

#define VECDATA_REG  0
#define VECDATA_LONG 1
#define VECDATA_BIG  2
#define VECDATA_VEC  3

Type(VecData,
     	u8 stack_allocated : 1;
	u8 floating : 1; 
	u8 datatype : 2; 
	size_t datasize, len; void* data;
)

#define vec(first, ...) push(Vector, (VecData){true, 		\
	_Generic((first),					\
	inst(Vector): Vector.isFloat((inst(Vector))		\
		((i64*)(&(typeof(first)){first}))),		\
	inst(Number): Number.isFloat((inst(Number))		\
		((i64*)(&(typeof(first)){first}))),		\
	float: true,						\
	double: true,						\
	default: false						\
	),							\
	_Generic((first),					\
	inst(Vector): VECDATA_VEC,				\
	inst(Number): VECDATA_BIG,				\
	double: VECDATA_LONG,					\
	i64: 	VECDATA_LONG,					\
	float:  VECDATA_REG,					\
	i8:     VECDATA_REG,					\
	i16: 	VECDATA_REG,					\
	i32:  	VECDATA_REG					\
	),							\
	_Generic((first),					\
	inst(Vector): Vector.DataSize((inst(Vector))		\
		((i64*)(&(typeof(first)){first}))),		\
	default: sizeof(typeof(first))				\
	),							\
	sizeof((typeof(first)[]){first, __VA_ARGS__})		\
		/sizeof(typeof(first)),				\
	(typeof(first)[]){first, __VA_ARGS__}			\
})
#define Vector(type, dim) inst(Vector)

Class(Vector,
__INIT(VecData initData),
__FIELD(),
	interface(Formatter);

	bool 		method(Vector, isFloat);
	u64 		method(Vector, DataSize);
	inst(Vector) 	method(Vector, DotProduct,, 	 inst(Vector) other);
	errvt 		method(Vector, DotProductInto,,  inst(Vector) a, inst(Vector) b);
)

/*----------------------|
 * 	  SIMD		|
----------------------*/

#if __Simd_Use

    #define usingSIMD (true)
    
    	#if isSet(__Simd_DefFunctions, SIMD_MATH)
    		#include "SIMD/SIMD_Arithmetic.h"
    	#endif
    	#if isSet(__Simd_DefFunctions, SIMD_MATH)
    		#include "SIMD/SIMD_Bitwise.h"
    	#endif
    	#if isSet(__Simd_DefFunctions, SIMD_MATH)
    		#include "SIMD/SIMD_Comparision.h"
    	#endif
    	#if isSet(__Simd_DefFunctions, SIMD_MATH)
    		#include "SIMD/SIMD_Move.h"
    	#endif


Data(SIMDVec,
__INIT(u16 bitwidth; u16 typesize; void* data),
	u16 bitwidth, typesize; void* data;
);

#define pushSIMD(type, len)  				\
	initialize(SIMDVec,				\
		alloca(sizeof(SIMDVec) +		\
	 		(sizeof(type) * len)),		\
		(sizeof(type) * len), sizeof(type)	\
	)


#define newSIMD(type, len)  				\
	initialize(SIMDVec,				\
		malloc(sizeof(SIMDVec) + 		\
	 		(sizeof(type) * len)),		\
		(sizeof(type) * len), sizeof(type)	\
	)

#define MD(first, ...)  					\
	initialize(SIMDVec,					\
		malloc(sizeof(SIMDVec) + 			\
	 	  (sizeof(typeof(first)) 			\
	 	  * (sizeof((typeof(first)[])			\
		{first, __VA_ARGS__})/sizeof(typeof(first))))),	\
		(sizeof(typeof(first)) 				\
	 	  * (sizeof((typeof(first)[])			\
		{first, __VA_ARGS__})/sizeof(typeof(first)))),	\
	     		sizeof(typeof(first)), 			\
		(typeof(first)[]){first, __VA_ARGS__}		\
	)

#define md(first, ...)  					\
	initialize(SIMDVec,					\
		alloca(sizeof(SIMDVec) + 			\
	 	  (sizeof(typeof(first)) 			\
	 	  * (sizeof((typeof(first)[])			\
		{first, __VA_ARGS__})/sizeof(typeof(first))))),	\
		(sizeof(typeof(first)) 				\
	 	  * (sizeof((typeof(first)[])			\
		{first, __VA_ARGS__})/sizeof(typeof(first)))),	\
	     		sizeof(typeof(first)), 			\
		(typeof(first)[]){first, __VA_ARGS__}		\
	)

Interface(SIMD,
	u32 maxBitWidth;
       	void vmethod(Add,   SIMDVec* a, SIMDVec* b, SIMDVec* result);	
       	void vmethod(Sub,   SIMDVec* a, SIMDVec* b, SIMDVec* result);	
       	void vmethod(Mul,   SIMDVec* a, SIMDVec* b, SIMDVec* result);	
       	void vmethod(Div,   SIMDVec* a, SIMDVec* b, SIMDVec* result);	
       	void vmethod(And,   SIMDVec* a, SIMDVec* b, SIMDVec* result);	
       	void vmethod(Or,    SIMDVec* a, SIMDVec* b, SIMDVec* result);	
       	void vmethod(Xor,   SIMDVec* a, SIMDVec* b, SIMDVec* result);	
       	void vmethod(Cmp,   numEquality cmpFlags, SIMDVec* a, SIMDVec* b, SIMDVec* result);	
       	void vmethod(Move,  SIMDVec* vec, SIMDVec* output);	
       	void vmethod(Store, SIMDVec* vec, void* output);	
       	void vmethod(Set,   SIMDVec* vec, void* output);
)

struct SIMD_Interface;
extern const SIMD_Interface SIMD;
#else
	#define usingSIMD (false)
#endif
