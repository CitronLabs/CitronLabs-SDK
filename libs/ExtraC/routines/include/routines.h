#pragma once
#include "extern.h"

typedef struct {u8 alloc[18];} FancyFunction_Alloc;

Class(FancyFunction,
__INIT(),
__FIELD(bool returned),
	
	#define fancy(...) static FancyFunction_Alloc __FANCY__ = {0}; 				\
     			for(init(FancyFunction, (inst(FancyFunction))&__FANCY__, __VA_ARGS__); 	\
			    !((inst(FancyFunction))&(__FANCY__))->returned; 						\
			    FancyFunction.__DESTROY(generic &__FANCY__))

	#define defer defer: for(int i = 0; (i = FancyFunction.Defer((inst(FancyFunction))&__FANCY__)); FancyFunction.__DESTROY(generic &__FANCY__))
	
	#define subfn(name, first, ...) (*name)(first, ...) = NULL; first; __VA_ARGS__; 
	#define routn(name) 	        (*name)() = NULL;

	#define freturn FancyFunction.__DESTROY(generic &__FANCY__); return
      	
      	errvt method(FancyFunction, SetVarDel,, void* var, void* del_func);
	bool method(FancyFunction, Defer);
)

Class(Coroutine, 
__INIT(),
__FIELD(),

	#define go(name)
	#define yield()
	#define stop()

	void(*Yield)();
	void(*Exit)();
	inst(Coroutine)(*This)();
	void (*Join)(inst(Coroutine) cr);
	void method(Coroutine, Start,, void* args);
)

