#include "../datastructs.h"

u64 methodimpl(DSN, formatQueue,, inst(Queue) data, inst(StringBuilder) out){

	u64 formated_len = StringBuilder.Append(out, s("<<[ "));
	
	loop(i, data->__private->items){
	    void* item = &((u8*)data->__private->start)[i * data->__private->itemsize];
	    if(i + 1 == data->__private->items){
		formated_len += DSN.formatField(self, &(DSN_data){data->__private->dsn_type, item}, out);
	    }else{
		formated_len += DSN.formatField(self, &(DSN_data){data->__private->dsn_type, item}, out);
		formated_len += StringBuilder.Append(out, s(", "));
	    }
	}

	formated_len += StringBuilder.Append(out, s(" ]"));
	
return formated_len;
}
u64 methodimpl(DSN, formatStack,, inst(Stack) data, inst(StringBuilder) out){
	u64 formated_len = StringBuilder.Append(out, s(">>[ "));
	
	loop(i, data->__private->top){
	    void* item = &((u8*)data->__private->start)[i * data->__private->itemsize];
	    if(i + 1 == data->__private->top){
		formated_len += DSN.formatField(self, &(DSN_data){data->__private->dsn_type, item}, out);
	    }else{
		formated_len += DSN.formatField(self, &(DSN_data){data->__private->dsn_type, item}, out);
		formated_len += StringBuilder.Append(out, s(", "));
	    }
	}
	formated_len += StringBuilder.Append(out,s(" ]"));

return formated_len;
}

u64 methodimpl(DSN, formatList,, inst(List) data, inst(StringBuilder) out){
	
	u64 formated_len = StringBuilder.Append(out, s("[ "));

	loop(i, data->__private->items){
	    void* item = &((u8*)data->__private->data)[i * data->__private->item_size];
	    if(i + 1 == data->__private->items){
		formated_len += DSN.formatField(self, &(DSN_data){data->__private->dsn_type, item}, out);
	    }else{
		formated_len += DSN.formatField(self, &(DSN_data){data->__private->dsn_type, item}, out);
		formated_len += StringBuilder.Append(out, s(", "));
		}
	}
	formated_len += StringBuilder.Append(out, s(" ]"));

return formated_len;	
}

u64 methodimpl(DSN, formatMap,, inst(Map) data, inst(StringBuilder) out){
	
	u64 formated_len = 0;
		
	formated_len += StringBuilder.Append(out, s("@{ "));
		
	ListForEach(data->__private->buckets, data_entry, bucket){
		formated_len += DSN.formatField(self, &(DSN_data){data->__private->key_dsn, bucket.key}, out);
		formated_len += StringBuilder.Append(out, s("->"));
		formated_len += DSN.formatField(self, &(DSN_data){data->__private->data_dsn, bucket.data}, out);
		formated_len += StringBuilder.Append(out, s(", "));
  	}
	formated_len += StringBuilder.Append(out, s(" }"));

return formated_len;
}

u64 methodimpl(DSN, formatStruct,, inst(Struct) data, inst(StringBuilder) out){
	u64 formated_len = 0;

	formated_len += StringBuilder.Append(out, s("{ "));
	
	List(data_entry) entries = Map.GetEntries(data->fields);

	ListForEach(entries, data_entry, entry){
	    DSN_data* field = entry.data;
		formated_len += DSN.formatField(self, field, out);
		formated_len += StringBuilder.Append(out, s(", "));
	}

	formated_len += StringBuilder.Append(out, s(" }"));

return formated_len;
}


#define format(formatstr, type) \
	formatted_len = snprintf(buff, 50, formatstr, data->as_##type)
u64 methodimpl(DSN, formatNumber,, inst(Number) data, inst(StringBuilder) out){
	
	u64 formatted_len = 0;
	char buff [50] = {0};
	char* format = NULL;

	switch(data->type){
	case N_SIGNED: {
		switch(data->len){
		case 1:{format(format != NULL ? format : "%hi", i32); break;}
		case 2:{format(format != NULL ? format : "%i", i32); break;}
		case 3:{format(format != NULL ? format : "%li" ,i64); break;}
		}
	break;}
	case N_UNSIGNED: {	
		switch(data->len){
		case 1:{format(format != NULL ? format : "%hu", u64); break;}
		case 2:{format(format != NULL ? format : "%u", u32); break;}
		case 3:{format(format != NULL ? format : "%lu", u32); break;}
		}
	break;}
	case N_FLOATING:{format(format != NULL ? format : "%lf", double); break;}
	default:{ return 0; }
	}

	StringBuilder.Append(out, s(buff));

return formatted_len;
}
u64 methodimpl(DSN, formatString,, inst(String) data, inst(StringBuilder) out){


	StringBuilder.Append(out, s("\""));
	StringBuilder.Append(out, data);
	StringBuilder.Append(out, s("\""));

return data->len + 2;
}


