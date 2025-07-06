#include "datastructs.h"

#define EMPTY 0
#define FULL 1
#define JUMP 2

#define shifthead(head, numofbytes) head = ((u8*)head) + numofbytes 
#define slot_size(queue) (queue->itemsize + sizeof(slot_status))

errvt methodimpl(Queue, Grow,, u64 add_amount){

	if(priv->nextqueue != NULL){
		self = priv->nextqueue;

		u64 previtems = priv->items;
		u64 total_items = priv->nextqueue != NULL ? 
		priv->items 
		: 
		priv->items + priv->nextqueue->__private->items;

		if(total_items + priv->items <= priv->limit)
			priv->items += priv->items;
		else 
			priv->items += priv->limit - total_items;

		priv->start = realloc(priv->start,priv->items * slot_size(priv));
		priv->end = priv->start + (priv->items * slot_size(priv));
		priv->writehead = priv->start + (previtems * slot_size(priv));

	}
	else {
	    if(priv->limit - priv->items > 0){
		priv->nextqueue = new(Queue, priv->items, priv->dsn_type, priv->itemsize);
		*priv->writehead = JUMP;
		priv->limit = priv->limit - priv->items;
	    }else{
		return ERR(DATAERR_LIMIT, "limit has been reached for this queue");
	    }
	}
return OK;
}

#define currpriv currqueue->__private
errvt methodimpl(Queue, Enqueue,, void* item, u64 num){
	
	inst(Queue) currqueue = self;
	
	nonull(self, return nullerr)
	nonull(item, return nullerr)

	if(priv->nextqueue != NULL) currqueue = priv->nextqueue;

	loop(i, num){

		if(priv->writehead == priv->end){
	//		DO_LATER("finish implementing this function");
		}
		if(*(priv->writehead + slot_size(priv)) == FULL){
	//		DO_LATER("finish implementing this function");
		}
		*currpriv->writehead = FULL;
		shifthead(currpriv->writehead, sizeof(slot_status));
		memcpy(currpriv->writehead, &((u8*)item)[i], currpriv->itemsize);
		shifthead(currpriv->writehead,currpriv->itemsize);
		currpriv->items++;
	}
return OK;
}
errvt methodimpl(Queue, Dequeue,, void* out, u64 num){

	nonull(self, return nullerr)
	nonull(out, return nullerr)

	if(EMPTY == *priv->readhead) return ERR(
		DATAERR_EMPTY, "queue is empty");

	loop(i, num){

		if(*priv->readhead == JUMP){
			free(priv->start);
			;
			priv = priv->nextqueue->__private;
		}

		if(priv->readhead == priv->end) priv->readhead = priv->start;
		*priv->readhead = EMPTY;
		shifthead(priv->readhead, sizeof(slot_status));
		memcpy(&((u8*)out)[i * priv->itemsize], priv->readhead, priv->itemsize);
		shifthead(priv->readhead,priv->itemsize);
		priv->items--;
	}


return OK;
}
bool methodimpl(Queue,Check){

	nonull(self, return -1)

	switch(*priv->readhead){
	case EMPTY: return false;
	case FULL: return true;
	case JUMP: return Queue.Check(priv->nextqueue);
	}
return false;	
}

u64 methodimpl(Queue, Count){
	nonull(self, return -1)

	return priv->items;
}

errvt methodimpl(Queue, Index,, bool write, u64 index, void* data){


	if(priv->items <= index){
		if(priv->nextqueue == NULL) 
			return ERR(DATAERR_OUTOFRANGE, "index out of range");
		index -= priv->items;
		self = priv->nextqueue;

		if(priv->items <= index)
			return ERR(DATAERR_OUTOFRANGE, "index out of range");
	}

	void* slot_data = priv->readhead + (slot_size(priv) * index);
	if(*(slot_status*)slot_data == JUMP){
		self = priv->nextqueue;
	}

	if(slot_data == priv->end) 
		slot_data = priv->start;

	slot_data += sizeof(slot_status);

	memcpy(data, priv->readhead, priv->itemsize);

return OK;
}

errvt methodimpl(Queue, Limit,, u64 limit){

	u64 total_items = priv->nextqueue != NULL ? 
		priv->items 
		: 
		priv->items + priv->nextqueue->__private->items;
	
	if(total_items > limit){
		if(priv->nextqueue != NULL){
			total_items -= priv->items;
			self = priv->nextqueue;
		}
		void* new_data_buffer = calloc(limit, priv->itemsize);
		if(priv->writehead < priv->readhead){
			u64 num_first_cpy = (priv->end - priv->readhead) / slot_size(priv);
			if((limit - num_first_cpy) > 0){

				memcpy(new_data_buffer, priv->readhead, num_first_cpy);
			}else{
				memcpy(new_data_buffer, priv->readhead, limit);
			}
			if(((limit - num_first_cpy) - (priv->items - num_first_cpy)) > 0){

				memcpy(new_data_buffer + (num_first_cpy * slot_size(priv)),
	  				priv->start, priv->items - num_first_cpy);
			}else{
				memcpy(new_data_buffer + (num_first_cpy * slot_size(priv)),
	  				priv->start, limit - num_first_cpy);
			}
	 	}else{
			memcpy(new_data_buffer, priv->readhead, limit);
		}
		free(priv->start);
		priv->start = realloc(priv->start,priv->items * slot_size(priv));
		priv->end = priv->start + (priv->items * slot_size(priv));
		priv->writehead = priv->end;
		priv->readhead = priv->start;
		priv->items = limit;
	}

	priv->limit = limit;

return OK;
}
void* methodimpl(Queue, ToPointer){
	
	nonull(self, return NULL);

	if(priv->items == 0) return NULL;


	u64 total_items = priv->nextqueue != NULL ? 
		priv->items 
		: 
		priv->items + priv->nextqueue->__private->items;

	void* out = calloc(total_items, priv->itemsize);
	u32 cursor = 0;

	loop(i, total_items){

		void* curr_data = priv->readhead + (slot_size(priv) * cursor);

		if(*priv->readhead == JUMP){
			self = priv->nextqueue;
			cursor = 0;
		}

		if(curr_data == priv->end) 
			curr_data = priv->start;

		curr_data += sizeof(slot_status);

		memcpy(&((u8*)out)[i * priv->itemsize], curr_data, priv->itemsize);
	}

return out;
}

errvt imethodimpl(Queue,Free){
	self_as(Queue)

	nonull(self, return nullerr;)

	if(priv->nextqueue != NULL){del(priv->nextqueue);}
	free(priv->start);
	;

return OK;
}

u64 imethodimpl(Queue, Scan,, FORMAT_ID* formats, inst(String) in){


}

u64 imethodimpl(Queue, Print,, FORMAT_ID* formats, inst(StringBuilder) out){

	inst(Queue) self = object;
	u64 formated_len = 0;

	switch(formats[FORMAT_DATA]){
	case DATA_DSN:
		formated_len += DSN.formatQueue(NULL, self, out);
	break;
	case DATA_DEBUG:
	
		formated_len += StringBuilder.Append(out, s("(Queue){"));
		
		formated_len += StringBuilder.Append(out, NULL, ".data = ", $(priv->start), ", ", endstr);
		formated_len += StringBuilder.Append(out, NULL, ".items = ", $(priv->items), ", ", endstr);
		formated_len += StringBuilder.Append(out, NULL, ".item_size = ", $(priv->itemsize), ", ", endstr);
		
		formated_len += StringBuilder.Append(out, s(" }"));
	break;	
	default: 
		return 0;
	}
return formated_len;
}

construct(Queue,
	.Enqueue = Queue_Enqueue,
	.Dequeue = Queue_Dequeue,
	.Check = Queue_Check,
	.Count = Queue_Count,
	.Index = Queue_Index,
	.Limit = Queue_Limit,
	.ToPointer = Queue_ToPointer,
	.Grow = Queue_Grow,
	.Object.__DESTROY = Queue_Free,
	.Formatter = {
	  	.Print = Queue_Print,
	  	.Scan = Queue_Scan
	}
){

	u64 start_size = args.init_size  == 0 ? 1 : args.init_size;
	set_priv(Queue){
		.start = calloc(start_size, args.type_size + sizeof(slot_status)),
		.end = priv->start + (start_size * (args.type_size + sizeof(slot_status))),
		.readhead = priv->start,
		.writehead = priv->start,
		.itemsize = args.type_size,
		.dsn_type = args.dsn_type,
		.items = 0,
		.limit = UINT64_MAX,
	};

	set_methods(Queue);
	
	if(args.literal != NULL){
		loop(i, start_size){
			*priv->writehead = FULL;
			shifthead(priv->writehead, sizeof(slot_status));
			memcpy(priv->writehead, args.literal, priv->itemsize);
			args.literal += args.type_size;
			shifthead(priv->writehead,priv->itemsize);
			priv->items++;
		}
	}


return self;
}
