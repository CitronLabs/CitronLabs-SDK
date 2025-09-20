#pragma once
#include "../../include/config.h"
#include "../../include/data.h"
#include "../../include/stringutils.h"
#include "../../include/alloc.h"

#define DSN_Object_Print(dsntype, ptr) NULL, 							\
	dsntype == DSN_STRUCT 	? &((inst(Struct))ptr)	->__methods->Formatter :	\
	dsntype == DSN_NUMBER 	? &((inst(Number))ptr)		->__methods->Formatter :	\
	dsntype == DSN_STRING 	? &((inst(String))ptr)		->__methods->Formatter :	\
	dsntype == DSN_LIST 	? &((inst(List))ptr)		->__methods->Formatter :	\
	dsntype == DSN_MAP 	? &((inst(Map))ptr)		->__methods->Formatter :	\
	dsntype == DSN_QUEUE 	? &((inst(Queue))ptr)		->__methods->Formatter :	\
	dsntype == DSN_STACK 	? &((inst(Stack))ptr)		->__methods->Formatter :	\
	NULL, ptr

private(List,
	void* data;
	u64 items_alloced, items, item_size, limit, 
	    * free_slots_buff, free_slots_buff_alloced, free_slots_buff_size
	;
	DSN_fieldType dsn_type;
	mutex busy;
)

private(Map,
	u64 allocednum;
	u16 item_size, key_size;
	u32* bucket_indexes;
	u32 default_index;
	List(data_entry) buckets;
	DSN_fieldType key_dsn, data_dsn;
	u32(*key_hash_func)(inst(Object));
	mutex busy;
)

typedef u8 slot_status;
private(Queue,	
    	slot_status* writehead,* readhead,* start,* end, * jmp_point;
	void* to_pointer_buf;
	u64 items, limit;
	DSN_fieldType dsn_type;
    	u16 itemsize;
	mutex busy;
)

private(Stack,
	void* start;
	u64 allocednum, top, limit;
	u16 itemsize;
	DSN_fieldType dsn_type;
	mutex busy;
)

private(DSN,
	Map(String, u32) import_resolve;
	List(DSN) imports;
	inst(Struct) header;
	mutex busy;
);
private(Struct,
	mutex busy;
);

