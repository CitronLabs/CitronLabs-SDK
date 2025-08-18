#include "../../include/alloc.h"
#include "../../include/data.h"

private(Pool,
	size_t max_size, alloc_size, current_size;
	Stack(void*) free_slots;
	List(Buffer) pool_buffers;
	u16 member_size;
	bool isStatic;
);

void* methodimpl(Pool, Alloc,, u64 num){

	inst(Buffer) alloc_buff = NULL;

	if(priv->current_size + num > priv->alloc_size){

	}else{
	    foreach(priv->pool_buffers, inst(Buffer), buff){
		if(!Buffer.isMaxed(buff) && 
		   Buffer.getTotalSize(buff) > Buffer.getItemNum(buff) + num)
		{
			alloc_buff = buff;
			break;
		}
    	    }
	}
	priv->current_size += num;

return Buffer.Allocator.New(generic alloc_buff, num, NULL);
}

void* imethodimpl(Pool, New,, size_t size, void* ex_args){
	self(Pool);
return Pool.Alloc(self, size);
}

errvt methodimpl(Pool, Return,, void* instance){
	Stack.Push(priv->free_slots, &instance, 1);
return OK;
}


errvt imethodimpl(Pool, Delete,, void* instance, void* ex_args){	
	self(Pool);
	Stack.Push(priv->free_slots, &instance, 1);
return OK;
}

errvt methodimpl(Pool, Grow,, u64 num){

	if(priv->isStatic){
		return ERR(MEMERR_OVERFLOW, "cannot grow a static pool");
	}
	if(priv->current_size + num > priv->max_size){
		return ERR(MEMERR_OVERFLOW, "size goes beyond the specified maximum");
	}
	u64 new_alloc_size = 
		((priv->alloc_size / 2) + num) > priv->max_size ?
		priv->max_size - priv->alloc_size : ((priv->alloc_size / 2) + num);

	inst(Buffer) new_buff = new(Buffer, new_alloc_size, priv->member_size);
	List.Append(priv->pool_buffers, &new_buff, 1);

	priv->alloc_size += new_alloc_size;

return OK;
}

errvt methodimpl(Pool, Reserve,, u64 num){
	if(priv->alloc_size - priv->current_size > num) return OK;

	Pool.Grow(self, num);
return OK;}

construct(Pool,
	.Allocator = {
		.New = Pool_New,
		.Delete = Pool_Delete,
	},
	.Return = Pool_Return,
	.Grow = Pool_Grow,
	.Alloc = Pool_Alloc,
	.Reserve = Pool_Reserve
){

	if(0 == args.member_size){
		ERR(MEMERR_INVALIDSIZE, "required member size cannot be 0");
	  	return NULL;
	}
	
	if(0 == args.init_size){ 
	      	ERR(MEMERR_INVALIDSIZE, "required init size cannot be 0");
	  	return NULL;
	}

	args.limit = args.limit == 0 ? UINT64_MAX : args.limit;
	
	if(args.init_size > args.limit) {
	  	ERR(MEMERR_INVALIDSIZE, "init size cannot be larger than the limit");
	  	return NULL;
	}
	
	setpriv(Pool){
	  	.max_size = args.limit,
		.current_size = args.init_size,
		.member_size = args.member_size,
	};

return self;
}
