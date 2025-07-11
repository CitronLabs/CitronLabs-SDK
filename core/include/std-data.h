#pragma once
#include "std-libc.h"
#include "std-utils.h"
#include "std-error.h"
#include "std-types.h"
#include "stdext-io.h"
#include "stdext-string.h"

#ifndef __USER_CONFIG__
#include "xc-user-config.h"
#endif

typedef enum DSN_field_type{
	DSN_NULL,
	DSN_NUMBER,
	DSN_STRING,
	DSN_LIST,
	DSN_QUEUE,
	DSN_STACK,
	DSN_MAP,
	DSN_STRUCT
}DSN_field_type;

#define getDSN_Type(var) _Generic((var),		\
inst(Number)	: DSN_NUMBER,				\
inst(String)	: DSN_STRING,				\
inst(List)	: DSN_LIST,				\
inst(Queue)	: DSN_QUEUE,				\
inst(Stack)	: DSN_STACK,				\
inst(Map)	: DSN_MAP,				\
inst(Struct)	: DSN_STRUCT,				\
default		: DSN_NULL)


typedef struct DSN_data{
	DSN_field_type type;
	void* data;
}DSN_data;
asClass(DSN_data){ passover }

/**
 * Extra-C List Data Structure
 *-----*/

#define l(first, ...) pushList(typeof(first), first, __VA_ARGS__)
#define L(first, ...) newList(typeof(first), first, __VA_ARGS__)

#define ListForEach(list, type, var) 				\
	u64 __##var##_size = List.Size(list); 			\
	type* __##var##_data = List.GetPointer(list, 0);	\
	type var = __##var##_data[0];				\
	for(size_t var##_iterator = 0; 				\
     	    var##_iterator < __##var##_size; 			\
	    var = __##var##_data[++var##_iterator]		\
	)

#define LISTINDEX_WRITE true
#define LISTINDEX_READ false

#define List(type) inst(List) 
#define newList(type, ...) new(List, 				\
		sizeof((type[]){__VA_ARGS__}) 		\
		/ sizeof(type),				\
		sizeof(type),	 			\
		getDSN_Type((type){0}),			\
		(type[]){__VA_ARGS__})
#define pushList(type, ...) push(List, 				\
		sizeof((type[]){__VA_ARGS__}) 		\
		/ sizeof(type),				\
		sizeof(type),	 			\
		getDSN_Type((type){0}),			\
		(type[]){__VA_ARGS__})

#define ListCast(list, type) \
List.Cast(list, getDSN_Type((type){0}), sizeof(type))


Class(List,
__INIT(u64 init_size; u64 type_size; DSN_field_type dsn_type; void* literal;),
__FIELD(),

	interface(Formatter);

	errvt 		method(List,Limit,, u64 limit_size);
	errvt 		method(List,Append,, void* in, u64 len);
	errvt 		method(List,Insert,, u64 len, u64 index, void* in);
	void 		method(List,Pop);
	void 		method(List,Flush);
	errvt 		method(List,Index,, bool write, u64 index, u64 len, void* data);
	errvt		method(List,SetFree,, u64 index);
	u64		method(List,FillSlot,, void* in);
	u64 		method(List,Size);
	void* 		method(List,GetPointer,, u64 offset);
	void* 		method(List,FreeToPointer);
	inst(List)	method(List,SubList,, u64 index, u64 len);
	errvt 		method(List,Merge,, inst(List) merged_list,u64 index);
	errvt 		method(List,Grow,, u64 add_amount);
	errvt   	method(List,Cast,, DSN_field_type dsn_type, u64 new_type_size);
)

/**
 * Extra-C Stack Data Structure
 *-----*/

#define Stack(type) inst(Stack)
#define newStack(type, ...) new(Stack,				\
		sizeof((type[]){__VA_ARGS__}) 		\
		/ sizeof(type),				\
		sizeof(type),	 			\
		getDSN_Type((type){0}),			\
		(type[]){__VA_ARGS__})

#define pushStack(type, ...) push(Stack,			\
		sizeof((type[]){__VA_ARGS__}) 		\
		/ sizeof(type),				\
		sizeof(type),	 			\
		getDSN_Type((type){0}),			\
		(type[]){__VA_ARGS__})




Class(Stack,
__INIT(u64 init_size; u64 type_size; DSN_field_type dsn_type; void* literal;),
__FIELD(),
	
	interface(Formatter);

	errvt method(Stack,Index,, bool write, u64 index, void* data);
	void* method(Stack,ToPointer);
	errvt method(Stack,Limit,, u64 limit);
	errvt method(Stack,Grow,, u64 add_amount);
	errvt method(Stack,Push,, void* item, u64 num);
	errvt method(Stack,Pop,, void* out, u64 num);
	u64 method(Stack,Count);
	bool method(Stack,Check);
)

/**
 * Extra-C Queue Data Structure
 *-----*/

#define Queue(type) inst(Queue)
#define newQueue(type, ...) new(Queue,				\
		sizeof((type[]){__VA_ARGS__}) 		\
		/ sizeof(type),				\
		sizeof(type),	 			\
		getDSN_Type((type){0}),			\
		(type[]){__VA_ARGS__})
#define pushQueue(type, ...) push(Queue,			\
		sizeof((type[]){__VA_ARGS__}) 		\
		/ sizeof(type),				\
		sizeof(type),	 			\
		getDSN_Type((type){0}),			\
		(type[]){__VA_ARGS__})
Class(Queue,
__INIT(u64 init_size; u64 type_size;DSN_field_type dsn_type; void* literal;),
__FIELD(),

	interface(Formatter);
	errvt method(Queue,Index,, bool write, u64 index, void* data);
	void* method(Queue,ToPointer);
	errvt method(Queue,Limit,, u64 limit);
	errvt method(Queue,Grow,, u64 add_amount);
	errvt method(Queue,Enqueue,, void* item, u64 num);
	errvt method(Queue,Dequeue,, void* out, u64 num);
	u64 method(Queue,Count);
	bool method(Queue,Check);
);

Class(BaseType, 
__INIT(__Base_Type_ID__ ID; void* data),
__FIELD(__Base_Type_ID__ ID; void* data),
	interface(Formatter);
)

/**
 * Extra-C Map Data Structure
 *-----*/

#define Map(key,value) inst(Map)
#define newMap(keytype, datatype, ...) new(Map,	 				\
			sizeof((data_entry[]){__VA_ARGS__}) / sizeof(data_entry),\
			sizeof(data(keytype)),	 				\
			getDSN_Type((inst(keytype)){0}),			\
			sizeof(data(datatype)),					\
			getDSN_Type((inst(datatype)){0}),			\
			(getMethods(keytype)).Object.__HASH,			\
			(data_entry[]){__VA_ARGS__})
#define pushMap(keytype, datatype, ...) push(Map,	 			\
			sizeof((data_entry[]){__VA_ARGS__}) / sizeof(data_entry),\
			sizeof(data(keytype)),	 				\
			getDSN_Type((inst(keytype)){0}),			\
			sizeof(data(datatype)),					\
			getDSN_Type((inst(datatype)){0}),			\
			(getMethods(keytype)).Object.__HASH,			\
			(data_entry[]){__VA_ARGS__})

#define entry(key, data) data_entry
typedef struct data_entry{
	void* key;
	void* data;
	u32 hash;
}data_entry;
asClass(data_entry){ passover }

#define INVALID_MAPINDEX UINT32_MAX

Class(Map,
__INIT(
      	u64 init_size; 
	u64 key_type_size;
	DSN_field_type key_dsn_type;
	u64 data_type_size; 
	DSN_field_type data_dsn_type;
	u32(*key_hash_func)(inst(Object) object);
	data_entry* literal;
),
__FIELD(),

	interface(Formatter);
	u64 		method(Map, Count);
	errvt 		method(Map,Limit,, u64 limit);
	errvt 		method(Map,SetDefault,, void* data);
	List(data_entry)method(Map,GetEntries);
	errvt 		method(Map,Insert,, void* key, void* value);
	void* 		method(Map,Search,, void* key);
	u32 		method(Map,SearchIndex,, void* key);
	void* 		method(Map,Index,, u32 index);
	errvt 		method(Map,Remove,, void* key);
	u32 (*Hash)(void* key, u64 len);
)



#define N_NULL	   0
#define N_SIGNED   1
#define N_UNSIGNED 2
#define N_FLOATING 3
#define N(number) new(Number, number)
#define n(number) push(Number, number)

Class(Number,
__INIT(double number;),
__FIELD(
	u8 type : 2;
	u8 len : 2;
	union{
		u64 as_u64 : 64;
		u64 as_u32 : 32;
		u64 as_u16 : 16;
		u64 as_u8  : 8;
		
		i64 as_i64 : 64;
		i64 as_i32 : 32;
		i64 as_i16 : 16;
		i64 as_i8  : 8;

		float as_float;		
		double as_double;		
	};
),
	interface(Formatter);
);


#define struct(allocmethod, ...) 		\
	allocmethod(Struct, 		\
	     (data_entry[]){__VA_ARGS__}, 	\
	     sizeof((data_entry[]){__VA_ARGS__}) \
	     / sizeof(data_entry)		\
	)

#define D(name, data) (data_entry){s(name), new(DSN_data, getDSN_Type(data), asObject(data))}

Class(Struct,
__INIT(data_entry* fields; u64 num_of_fields),
__FIELD(Map(String, DSN_data) fields),
	interface(Formatter);
	errvt 		method(Struct, Define,, ...);
	errvt 		method(Struct, AddField,, cstr name, DSN_data* data);
	errvt 		method(Struct, Merge,, inst(Struct) datastruct);
	DSN_data*	method(Struct, SearchField,, inst(String) name);
)


Class(DSN, 
__INIT(cstr name; inst(String) source; List(entry(String,DSN)) imports), 
__FIELD(inst(String) name; inst(Struct) body),
	
 	interface(Formatter);

      	errvt 		method(DSN, addImport,,   cstr name, inst(DSN) import_data);
	DSN_data*	method(DSN, searchField,, inst(String) name);
	u64		method(DSN, parseField,,  DSN_data* ds, inst(String) in);
	u64		method(DSN, formatField,, DSN_data* ds, inst(StringBuilder) out);
	
	// if buff is null then it return the expected size of the buff
	u64		method(DSN, formatDSB,, void* buff);
	u64		method(DSN, parseDSB,, void* buff, u64 size);
	
	u64 	method(DSN, parseList,,    inst(List)* data,	inst(String) in);
	u64 	method(DSN, parseQueue,,   inst(Queue)* data,	inst(String) in);
	u64 	method(DSN, parseStack,,   inst(Stack)* data,	inst(String) in);
	u64 	method(DSN, parseMap,,     inst(Map)* data,	inst(String) in);
	u64 	method(DSN, parseStruct,,  inst(Struct)* data,	inst(String) in);
	u64 	method(DSN, parseString,,  inst(String)* data,	inst(String) in);
	u64 	method(DSN, parseNumber,,  inst(Number)* data,	inst(String) in);
	
	u64 	method(DSN, formatList,,   inst(List) data,	inst(StringBuilder) out);
	u64 	method(DSN, formatQueue,,  inst(Queue) data,	inst(StringBuilder) out);
	u64 	method(DSN, formatStack,,  inst(Stack) data,	inst(StringBuilder) out);
	u64 	method(DSN, formatMap,,    inst(Map) data,	inst(StringBuilder) out);
	u64 	method(DSN, formatStruct,, inst(Struct) data,	inst(StringBuilder) out);
	u64 	method(DSN, formatString,, inst(String) data,	inst(StringBuilder) out);
	u64 	method(DSN, formatNumber,, inst(Number) data,	inst(StringBuilder) out);
)



