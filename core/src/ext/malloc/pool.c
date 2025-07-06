#include "../../../include/std-all.h"

typedef u64 pool_metadata[2]; // [0] = alloced size ; [1] = used size

private(Pool,
	size_t max_size, current_size;
	void* lastfree_member;
	pool_metadata* data;
	u16 member_size;
);

static pool_metadata* alloc_new_pool(inst(Pool) self, size_t size){

	pool_metadata* res = 
	    malloc(
		(size * priv->member_size) + 
	 	sizeof(pool_metadata) + 
	 	sizeof(void*)
	    );
	
	(*res)[0] = size;
	(*res)[1] = 0;

	void* data_start = &res[1];
	(*(pool_metadata**)(data_start + size)) = NULL;

return res;
}

#define alloc_size (*curr_strip)[0]
#define curr_size (*curr_strip)[1]
void* imethodimpl(Pool, New,, size_t size, ...){

	self_as(Pool)

	void* res = NULL;
	if(priv->lastfree_member != NULL){
		res = priv->lastfree_member;
		priv->lastfree_member = *(void**)priv->lastfree_member;
	}	
	if(priv->lastfree_member == NULL){
		//Maximum size is reached
	    if(priv->current_size >= priv->max_size){
		assert(priv->current_size <= priv->max_size);
		ERR(MEMERR_OVERFLOW, "maximum size has been reached");
	    }
	    else{
	        pool_metadata* curr_strip = priv->data;
	        loop(i, priv->current_size){
	    	    pool_metadata** next_strip = NULL;
	    	    if(alloc_size < curr_size){
		        break;
		    }else
		        assert(curr_size == alloc_size);
		        void* data_start = &curr_strip[1];
			next_strip = (pool_metadata**)(data_start + alloc_size); 
		    	    
		        if(*next_strip == NULL){
			    *next_strip = alloc_new_pool(self, 
				(priv->current_size + (alloc_size + (alloc_size / 2)) > priv->max_size) ?
				priv->max_size - priv->current_size : alloc_size + (alloc_size / 2));
			}
			curr_strip = *next_strip;
	    	    }
	    	res = ((void*)&curr_strip[1]) + 
	    	   (curr_size * priv->member_size) + 
		    priv->member_size;
		curr_size++;
	   }
	}
return res;
}
errvt imethodimpl(Pool, Delete,, void* instance, ...){
	
	self_as(Pool)

	*((void**)instance) = priv->lastfree_member;
	priv->lastfree_member = instance;
return OK;
}

construct(Pool,
	.Allocator = {
		.New = Pool_New,
		.Delete = Pool_Delete,
	}
){

	if(0 == args.member_size){
		ERR(MEMERR_INVALIDSIZE, "required member size cannot be 0");
	  	return self;
	}
	
	if(0 == args.init_size){ 
	      	ERR(MEMERR_INVALIDSIZE, "required init size cannot be 0");
	  	return self;
	}

	args.limit = args.limit == 0 ? UINT64_MAX : args.limit;
	
	if(args.init_size > args.limit) {
	  	ERR(MEMERR_INVALIDSIZE, "init size cannot be larger than the limit");
	  	return self;
	}
	
	set_methods(Pool);
	set_priv(Pool){
	  	.max_size = args.limit,
		.current_size = args.init_size,
		.member_size = args.member_size,
		.data = alloc_new_pool(self, args.init_size)
	};

set_init();
return self;


}
