#include "./datastructs.h"
#include "DSN/format.c"
#include "DSN/parse.c"
#include "DSN/bin.c"

errvt handleQueueOverride(DSN_data* reference, DSN_data* override){
	inst(Queue) ref = reference->data;
	inst(Queue) ovr = override->data;
	
	if(ovr->__private->dsn_type != ref->__private->dsn_type)
		return ERR(DATAERR_DSN, "override types dont match that of the reference");
	
	u64 ref_size = Queue.Count(ref), ovr_size = Queue.Count(ovr);

	if(ref_size > ovr_size){
		void* ref_ovr = Queue.ToPointer(ref);
		Queue.Enqueue(ovr, ref_ovr, ref_size - ovr_size);
	}
return OK;
}
errvt handleStackOverride(DSN_data* reference, DSN_data* override){
	inst(Stack) ref = reference->data;
	inst(Stack) ovr = override->data;
	
	if(ovr->__private->dsn_type != ref->__private->dsn_type)
		return ERR(DATAERR_DSN, "override types dont match that of the reference");

	u64 ref_size = Stack.Count(ref), ovr_size = Stack.Count(ovr);

	if(ref_size > ovr_size){
		void* ref_ovr = Stack.ToPointer(ref);
		Stack.Push(ovr, ref_ovr, ref_size - ovr_size);
	}
return OK;
}
errvt handleListOverride(DSN_data* reference, DSN_data* override){
	inst(List) ref = reference->data; 
	inst(List) ovr = override->data;
	
	if(ovr->__private->dsn_type != ref->__private->dsn_type)
		return ERR(DATAERR_DSN, "override types dont match that of the reference");
	
	u64 ref_size = List.Size(ref), ovr_size = List.Size(ovr);

	if(ref_size > ovr_size){
		void* ref_ovr = List.GetPointer(ref, ovr_size);
		List.Append(ovr, ref_ovr, ref_size - ovr_size);
	}
return OK;
}
errvt handleMapOverride(DSN_data* reference, DSN_data* override){
	inst(Map) ref = reference->data; 
	inst(Map) ovr = override->data;

	if(ovr->__private->data_dsn != ref->__private->data_dsn ||
	   ovr->__private->key_dsn != ref->__private->key_dsn)
		return ERR(DATAERR_DSN, "override types dont match that of the reference");

	List(data_entry) ref_ents = Map.GetEntries(ref);
	
	foreach(ref_ents, data_entry, ent){
		if(Map.SearchIndex(ovr, ent.key) == UINT32_MAX){
			Map.Insert(ovr, ent.key, ent.data);
		}
	}
return OK;
}
errvt handleStructOverride(DSN_data* reference, DSN_data* override){
	inst(Struct) ref = reference->data; 
	inst(Struct) ovr = override->data;

	List(data_entry) entries = Map.GetEntries(ref->fields);

	foreach(entries, data_entry, ent){
		DSN_data* res = Struct.SearchField(ovr, ent.key);
		if(res == NULL){
		    if(Struct.AddField(ovr, ent.key, ent.data) != ERR_NONE){
			return ERR(DATAERR_DSN, "failed to add missing field to override");
		    }
		}
		if(res->type != (*(DSN_data**)ent.data)->type)
			return ERR(DATAERR_DSN, "override does not match reference type");
	}

return OK;
}

u64 resolveReference(inst(DSN) self, DSN_data* ds, inst(String) in){

	if(self == NULL){
		ERR(DATAERR_DSN, "unable to resolve reference due to no DSN instance being provided");
		return 0;
	}
	u64 reference_len = 0;
	for(;;){
		while(isalnum(in->txt[reference_len])) reference_len++;
		if(in->txt[reference_len] != '.') break;
	}

	DSN_data* reference = DSN.searchField(self, String_CutBackCpy(in, in->len - reference_len));

	if(reference == NULL){
		ERR(DATAERR_DSN, "reference not found");
		return 0;
	}
	
	while(isblank(in->txt[reference_len])) reference_len++;

	if(in->txt[reference_len] == ':') {

		while(isblank(in->txt[reference_len])) reference_len++;
		
		DSN_data override = {0};
		u64 override_len = DSN.parseField(self, &override, in);
		errvt err = ERR_NONE;

		if(override_len == 0){
			ERR(DATAERR_DSN, "could not parse reference override");
			return 0;
		}
		if(override.type != reference->type){
			ERR(DATAERR_DSN, "override type is not equal to reference type");
			return 0;
		}
		switch (override.type) {
		case DSN_LIST:{
			err = handleListOverride(reference, &override);
		break;}
		case DSN_QUEUE:{
			err = handleQueueOverride(reference, &override);
		break;}
		case DSN_STACK:{
			err = handleStackOverride(reference, &override);
		break;}
		case DSN_MAP:{
			err = handleMapOverride(reference, &override);
		break;}
		case DSN_STRUCT:{
			err = handleStructOverride(reference, &override);
		break;}
		default: break;
		}

		if(err){
			ERR(DATAERR_DSN, "failed to handle override");
			return 0;
		}

		reference = &override;
		reference_len += override_len;
	}
	else if(in->txt[reference_len] != ','){
		ERR(DATAERR_DSN, "expected a ,");
		return 0;
	}

	*ds = *reference;

return reference_len;
}


u64 methodimpl(DSN, parseField,, DSN_data* ds, inst(String) in){

	while(isblank(in->txt[0])){ String_CutFrnt(in, 1); }
	
	switch (in->txt[0]) {
	case '>':{
		ds->type = DSN_STACK;
		return DSN.parseStack(self, (inst(Stack)*)ds->data, in);
	break;}
	case '<':{
		ds->type = DSN_QUEUE;
		return DSN.parseQueue(self, (inst(Queue)*)ds->data, in);
	break;}
	case '[':{
		ds->type = DSN_LIST;
		return DSN.parseList(self, (inst(List)*)ds->data, in);
	break;}
	case '@':{
		ds->type = DSN_MAP;
		return DSN.parseMap(self, (inst(Map)*)ds->data, in);
	break;}
	case '0' ... '9':{
		ds->type = DSN_NUMBER;
		return DSN.parseNumber(self, (inst(Number)*)ds->data, in);
	break;}
	case '"':{
		ds->type = DSN_STRING;
		return DSN.parseString(self, (inst(String)*)ds->data, in);
	break;}
	case '{':{
		ds->type = DSN_STRUCT;
		return DSN.parseStruct(self, (inst(Struct)*)ds->data, in);
	break;}
	case 'a' ... 'z':
	case 'A' ... 'Z':{
		return resolveReference(self, ds, in);
	break;}
	default:{
		ERR(DATAERR_DSN, "unexpected token");
	break;}
	}

return 0;
}

u64 methodimpl(DSN, formatField,, DSN_data* ds, inst(StringBuilder) out){

	switch (ds->type) {
	case DSN_STACK:{
		return DSN.formatStack(self, *(inst(Stack)*)ds->data, out);
	break;}
	case DSN_QUEUE:{
		return DSN.formatQueue(self, *(inst(Queue)*)ds->data, out);
	break;}
	case DSN_LIST:{
		return DSN.formatList(self, *(inst(List)*)ds->data, out);
	break;}
	case DSN_MAP:{
		return DSN.formatMap(self, *(inst(Map)*)ds->data, out);
	break;}
	case DSN_NUMBER:{
		return DSN.formatNumber(self, *(inst(Number)*)ds->data, out);
	break;}
	case DSN_STRING:{
		return DSN.formatString(self, *(inst(String)*)ds->data, out);
	break;}
	case DSN_STRUCT:{
		return DSN.formatStruct(self, *(inst(Struct)*)ds->data, out);
	break;}
	default:{	
		ERR(DATAERR_DSN, "unexpected dsn data type");
	break;}
	}

return 0;
}


errvt methodimpl(DSN, addImport,, cstr name, inst(DSN) import_data){
	
	if(Map.SearchIndex(priv->import_resolve, String_From(name, 255)) != UINT32_MAX){
		return ERR(DATAERR_DSN, "name already in use by another import");
	}

	inst(String) name_str = new(String, name, 255);

	u32 index = List.Size(priv->imports);
	List.Append(priv->imports, &import_data, 1);
	
	Map.Insert(priv->import_resolve, &name_str, &index);

return OK;	
}

DSN_data* methodimpl(DSN, searchField,, inst(String) name){
	
	u64 cursor = 0;

	inst(String) view = String_View(name, 0, name->len);
	inst(Struct) curr_struct = NULL;
	DSN_data* result = NULL;

	loopat(i, cursor, name->len){
	    if(name->txt[i] == '.' || i + 1 == name->len){
		String_CutFrnt(view, i); 

		if(curr_struct == NULL){

		    u32* index = Map.Search(priv->import_resolve, &view);

		    if(index != NULL){
			inst(DSN) import = List.GetPointer(priv->imports, *index);
			curr_struct = import->body;
		    }else{
			curr_struct = priv->header;
		    }
		}

		result = Struct.SearchField(curr_struct, view);
	 	if(result == NULL){
			ERR(DATAERR_DSN, "unable to resolve reference");
			return NULL;
	    	}
		if(name->txt[i] == '.'){
			if(result->type != DSN_STRUCT){
				ERR(DATAERR_DSN, "only structs ({}) can be subreferenced");
				return NULL;
			}
			curr_struct = result->data;
		}else{
		    	return result;
		}
	
		cursor += i;
	    } 
	}

ERR(DATAERR_DSN, "unexpected end of reference");
return NULL;
};

construct(DSN, 
	.parseField = DSN_parseField,
	.parseNumber = DSN_parseNumber,
	.parseString = DSN_parseString,
	.parseStruct = DSN_parseStruct,
	.parseMap = DSN_parseMap,
	.parseList = DSN_parseList,
	.parseQueue = DSN_parseQueue,
	.parseStack = DSN_parseStack,
	
	.formatField = DSN_formatField,
	.formatNumber = DSN_formatNumber,
	.formatString = DSN_formatString,
	.formatStruct = DSN_formatStruct,
	.formatMap = DSN_formatMap,
	.formatList = DSN_formatList,
	.formatQueue = DSN_formatQueue,
	.formatStack = DSN_formatStack,
	
	.addImport = DSN_addImport,
	.searchField = DSN_searchField,
){ 
	
return self;
}
