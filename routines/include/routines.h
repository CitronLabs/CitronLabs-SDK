#pragma once

#define RoutineErrorCodes	\
ROUTINEERR_RUN,			\
ROUTINEERR_INIT,		\
ROUTINEERR_ALRDYACTIVE		\

#ifndef __USER_ERRORCODES__
	#define __USER_ERRORCODES__ RoutineErrorCodes
#endif

#include "../../core/include/std-all.h"



Class(FancyFunction,
__INIT(),
__FIELD(),
	
	#define FANCYFUNCTION(...) static inst(FancyFunction) __FANCY__; __FANCY__ = new(FancyFunction, __VA_ARGS__);

	#define defer defer: for(int i = 0; (i = FancyFunction.Defer(__FANCY__)); FancyFunction.End(__FANCY__))
	#define setDel(var, del) FancyFunction.SetVarDel(__FANCY__, var, del);

	#define freturn FancyFunction.End(__FANCY__); return
      	
      	errvt method(FancyFunction, SetVarDel,, void* var, void* del_func);
	bool method(FancyFunction, Defer);
      	bool method(FancyFunction, End);
)

Class(Fiber, 
__INIT(void*(*start_func)(void* args)),
__FIELD(void*(*start_func)(void* args)),

	void(*Yield)();
	void(*Exit)();
	inst(Fiber)(*This)();
	void (*Join)(inst(Fiber) fiber);
	void method(Fiber, Start,, void* args);
)

#define Callback(name, ...) intf(Routine) routine_interface, void* name
#define callback(routine) &((typeof(routine)){routine}->__methods->Routine), routine
	
Interface(Routine,
	#define Routine_decl(name, ...) \
	  	struct name##_args{__VA_ARGS__;};

	#define Routine(name, ...) struct name##_args{__VA_ARGS__;}; intf(Routine) name
	#define call(routine, ...) routine.Call(routine, &(struct routine##_args){__VA_ARGS__})

	errvt imethod(Call,, void* args);
	errvt imethod(End);
	errvt imethod(CheckStatus);
)


#define IO_READ false
#define IO_WRITE true 
enum IO_type{ IO_NETWORK, IO_FILE, IO_DIR, IO_DEVICE };
Class(IORoutine,
__INIT(const char* path; size_t size; void* data; u8 type : 2; u8 write : 1;),
__FIELD(inst(Fiber) fiber),
	interface(Routine);
)

Class(SubRoutine,
__INIT(),
__FIELD(),

	#define SubRoutine_decl(name, ...) \
      		struct name##_args{__VA_ARGS__;};

	#define SubRoutine(name, ...) \
      		struct name##_args{__VA_ARGS__;}; inst(SubRoutine) name

	#define subroutine(name, ...) \
		struct name##_args {__VA_ARGS__;}; inst(SubRoutine) name; __VA_ARGS__; 	\
		for(int run = 0; 							\
		(run = SubRoutine.InitHere(						\
			name, 								\
			sizeof(struct name##_args),					\
			&name + sizeof(void*)))						\
		!= 0;									\
	     	SubRoutine.Routine.End(name))
	

	interface(Routine);
	errvt method(SubRoutine, InitHere,, size_t sizeof_args, void* args_start);
)



