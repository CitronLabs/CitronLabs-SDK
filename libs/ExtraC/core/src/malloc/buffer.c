#include "../../include/alloc.h"
#include "../../include/data.h"

private(Buffer,
	u64 type_size, size, alloced_size;
	pntr data; bool isStatic;
);

u64  methodimpl(Buffer, getItemNum){ return priv->size; }
u64  methodimpl(Buffer, getTypeSize){ return priv->type_size; }
u64  methodimpl(Buffer, getTotalSize){ return priv->type_size * priv->size; }
pntr methodimpl(Buffer, getPointer){ return priv->data; }
u64 imethodimpl(Buffer, getBytesAlloced){ self(Buffer); return priv->type_size * priv->size; }
bool imethodimpl(Buffer, isStatic){ self(Buffer); return priv->isStatic; }
bool methodimpl(Buffer, isMaxed){ return priv->alloced_size == priv->alloced_size; }

errvt imethodimpl(Buffer, setMax,, u64 max){ 
	self(Buffer); 
	return Buffer.resize(self, max); 
}

pntr imethodimpl(Buffer, New,, u64 size, void* ex_args){
	self(Buffer);
	if(priv->alloced_size + size > priv->size){
		if(priv->isStatic){
			ERR(MEMERR_OVERFLOW, "size exceeds buffer and cannot grow static buffer");
			return NULL;
		}else{
		  check(
		    Buffer.resize(self, (priv->size / 2) + size);
		  ){ 
			ERR(err->errorcode, err->message);
			return NULL;	
		  }
		}
	}

	pntr result = pntr_shiftcpy(priv->data, priv->alloced_size);
	priv->alloced_size += size;

return result;
}

void* imethodimpl(Buffer, Realloc,, pntr instance, u64 new_size, void* ex_args){
	self(Buffer);
	check(Buffer.resize(self, new_size);){
		ERR(err->errorcode, err->message);
		return NULL;
	}
return priv->data;
}

errvt imethodimpl(Buffer, Destroy){
	self(Buffer);
	free(priv->data);
return OK;
}

errvt imethodimpl(Buffer, Hash){
	self(Buffer);
	return Map.Hash(priv->data, priv->size);
}

errvt methodimpl(Buffer, Cast,, u64 type_size){
	if(type_size == 0) return ERR(MEMERR_INVALIDSIZE, "cannot cast buffer to type size 0");
	
	priv->size = (priv->size * priv->type_size) / type_size;
	priv->alloced_size = (priv->alloced_size * priv->type_size) / type_size;
	priv->type_size = type_size;

return OK;
}
errvt methodimpl(Buffer, Resize,, u64 new_size){
	if(priv->isStatic) 
		return ERR(MEMERR_INITFAIL, "unable to resize a static buffer");
	priv->data = realloc(priv->data, new_size);
	priv->size = new_size;
	if(priv->alloced_size > priv->size) priv->alloced_size = priv->size;

return OK;
}
#undef cast
construct(Buffer,
	.getItemNum = Buffer_getItemNum,
	.getTypeSize = Buffer_getTypeSize,
	.getTotalSize = Buffer_getTotalSize,
	.getPointer = Buffer_getPointer,
	.isMaxed = Buffer_isMaxed,
	.cast = Buffer_Cast,
	.resize = Buffer_Resize,
	.Allocator = {
	    .getBytesAlloced = Buffer_getBytesAlloced,
	    .isStatic = Buffer_isStatic,
	    .setMax = Buffer_setMax,
	    .New = Buffer_New,
    	    .Resize = Buffer_Realloc
	},
	.__DESTROY = Buffer_Destroy, .__HASH = Buffer_Hash
){
	if(args.size == 0){
	  	ERR(MEMERR_INVALIDSIZE, "buffer size cannot be 0"); 
	  	return NULL;
	}
	args.type_size = args.type_size == 0 ? 1 : args.type_size;

	if(args.isStatic){
		priv->data = pntr_shiftcpy(self, sizeof(Buffer_Instance) + sizeof(Buffer_Private));
	}else{
	  check(priv->data = calloc(args.size, args.type_size)){
		ERR(err->errorcode, err->message); return NULL;
	  }
	}
	
	setpriv(Buffer){
		.size = args.size,
	  	.type_size = args.size,
		.isStatic = args.isStatic,
		.alloced_size = 0
	};

return self;
}
