#include "../../../include/std-all.h"

private(Arena,
	size_t max_size, current_size;
	void* data,* top;
)

void* imethodimpl(Arena, New,, u64 size, ...){
	
	self_as(Arena);

	if(priv->current_size >= priv->max_size){
		ERR(MEMERR_OVERFLOW, "size goes beyond the specified maximum");
		return NULL;
	}
	
	if(priv->data + priv->current_size >= priv->top + size){
	    priv->current_size += ((priv->current_size / 2 ) + size);

	    priv->current_size = priv->current_size >= priv->max_size ?
			priv->max_size	: priv->current_size;
	
	   u64 top_offset = priv->top - priv->data;
	   priv->data = realloc(priv->data, priv->current_size);
	   priv->top = priv->data + top_offset;
	}
	void* res = priv->top;
	priv->top += size;

return res;
}

void* imethodimpl(Arena, Resize,, void* instance, u64 size, ...){	
	
	self_as(Arena);

	if(size == 0) return NULL;

	if(priv->current_size > size)
		priv->data = realloc(priv->data, size);

	priv->max_size = size;

return priv->data;
}

construct(Arena,
	.Allocator = {
		.New = Arena_New,
		.Resize = Arena_Resize
	}
){
	if(args.init_size == 0) {
	    ERR(MEMERR_INVALIDSIZE, "initial size cannot be 0 for priv");
	    return self;
	}

	set_priv(Arena){
		.max_size = UINT64_MAX,
		.data = malloc(args.init_size),
		.current_size = args.init_size,
	};
}

