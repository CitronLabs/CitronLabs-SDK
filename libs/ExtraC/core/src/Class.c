#include "../include/types.h"
#include "../include/error.h"

private(Object,)
construct(Object){
	self->__methods = args.methods;
	self->__private = args.private;
return self;
}
