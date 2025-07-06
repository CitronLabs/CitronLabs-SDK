#pragma once
#include "../../../include/std-all.h"
#include <stdio.h>

#ifdef calloc
#undef calloc
#endif
#ifdef malloc
#undef malloc
#endif
#ifdef realloc
#undef realloc
#endif
#ifdef free
#undef free
#endif

typedef struct c_malloc_metadata{
	size_t bytes_alloced;
}c_malloc_metadata;

private(CMalloc,
	u64 bytes_alloced;
)

void* imethodimpl(CMalloc, New,, u64 bytes_to_alloc, ...){
	c_malloc_metadata* res = NULL;

	va_list args;
	va_start(args, bytes_to_alloc);

	self_as(CMalloc);

	if(0 == bytes_to_alloc) { 
	    ERR(MEMERR_INVALIDSIZE, "invalid alloc size");
	      	return NULL;
	}

	u32 size_mem = va_arg(args, u32);
	if(size_mem == 0){	
		if(priv->bytes_alloced + bytes_to_alloc > self->max_alloc){
			if(!self->overflow_handler || !self->overflow_handler(self, bytes_to_alloc)) 
				return NULL;
		}

		res = malloc(sizeof(c_malloc_metadata) + bytes_to_alloc);
		
		if(NULL == res) { 
		 	ERR(MEMERR_INITFAIL, "failed to allocate memory");
	     	 	return NULL;
		}
		
		res->bytes_alloced = bytes_to_alloc;
	}else{
		if(priv->bytes_alloced + (bytes_to_alloc * size_mem) > self->max_alloc)
			if(!self->overflow_handler(self, bytes_to_alloc * size_mem)) 
				return NULL;
		res = calloc(1, (bytes_to_alloc * size_mem) + sizeof(c_malloc_metadata));
		
		if(NULL == res) { 
		 	ERR(MEMERR_INITFAIL, "failed to allocate memory");
	     	 	return NULL;
		}
		

		res->bytes_alloced = bytes_to_alloc * size_mem;
	}

	priv->bytes_alloced += res->bytes_alloced;

return &res[1];
}


void* imethodimpl(CMalloc, Resize,, void* data, size_t size, ...){

	nonull(data, return NULL);

	self_as(CMalloc);

	c_malloc_metadata* res = &((c_malloc_metadata*)data)[-1];

	if(0 == size) { 
	    ERR(MEMERR_INVALIDSIZE, "invalid realloc size");
	      	return NULL;
	}
	else{
		priv->bytes_alloced -= res->bytes_alloced;
		res = realloc(res, size);
		res->bytes_alloced = size;
		priv->bytes_alloced += res->bytes_alloced;
	}
return &res[1];
}

errvt imethodimpl(CMalloc, Delete,, void* data, ...){
	nonull(data, return nullerr;)
	
	self_as(CMalloc);

	c_malloc_metadata* data_ptr = &((c_malloc_metadata*)data)[-1];

	priv->bytes_alloced -= data_ptr->bytes_alloced;

	 free(data_ptr);
return OK;
}

u64 methodimpl(CMalloc, getBytesAlloced){
	return priv->bytes_alloced;
}


inst(CMalloc) c_malloc = &(CMalloc_Instance){
	.__init = true,
	.max_alloc = UINT64_MAX,
	.overflow_handler = NULL,
	.__methods = &CMalloc,
	.__private = &(CMalloc_Private){
		.bytes_alloced = 0
	}
};

construct(CMalloc,
	.Allocator = {
		.New = CMalloc_New,
		.Resize = CMalloc_Resize,
		.Delete = CMalloc_Delete,
	},
	.getBytesAlloced = CMalloc_getBytesAlloced
){

	self->max_alloc = args.max_alloc;

set_init();
return self;
}
