#include "../include/routines.h"

private(Coroutine,
	void* stack_pointer;
	void* args;
);

Queue(inst(Coroutine)) fiber_queue;

extern void Coroutine_Yield();
void Coroutine_Exit();
void Coroutine_Join(inst(Coroutine) fiber);
inst(Coroutine) Coroutine_This();



void fiberNext(void* stack_pointer);
void fiberSwitch(void* stack_pointer, std_fiber* fiber);



construct(Coroutine,
	.Yield = Coroutine_Yield
){
	set_methods(Coroutine);
	set_priv(Coroutine){0};	
	self->start_func = args.start_func;

}
