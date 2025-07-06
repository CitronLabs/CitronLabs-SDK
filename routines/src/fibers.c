#include "../include/routines.h"

private(Fiber,
	void* stack_pointer;
	void* args;
);

Queue(inst(Fiber)) fiber_queue;

extern void Fiber_Yield();
void Fiber_Exit();
void Fiber_Join(inst(Fiber) fiber);
inst(Fiber) Fiber_This();



void fiberNext(void* stack_pointer);
void fiberSwitch(void* stack_pointer, std_fiber* fiber);



construct(Fiber,
	.Yield = Fiber_Yield
){
	set_methods(Fiber);
	set_priv(Fiber){0};	
	self->start_func = args.start_func;

}
