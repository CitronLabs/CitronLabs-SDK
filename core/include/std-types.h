#pragma once
#include "std-libc.h"
#include "std-utils.h"
#include <uchar.h>

/*------------------------------|
       Class Preprocessors	|
-------------------------------*/

#define method(Class,name, ...) (*name)(Class##_Instance* self __VA_ARGS__)
#define imethod(name, ...) (*name)(inst(Object) object __VA_ARGS__)

#define methodimpl(Class,Routine, ...) 			\
	Class##_##Routine(Class##_Instance* self __VA_ARGS__)

#define imethodimpl(Class,Routine, ...) 		\
	Class##_##Routine(inst(Object) object __VA_ARGS__)

#define __INIT(...) __VA_ARGS__;
#define __FIELD(...) __VA_ARGS__;
#define __METHODS(...) __VA_ARGS__
#define interface(Class) const Class##_Interface Class
#define inhert(Class) Class##_Instance Class

#define construct(name, ...)						\
	const u64 sizeof_##name##_Private = sizeof(name##_Private);	\
	Impl(name){__VA_ARGS__}; 					\
	name##_Instance* name##__Create__(				\
		name##_ConstructArgs args, 				\
		name##_Instance* self);					\
	name##_Instance* name##_Construct(				\
		name##_ConstructArgs args, 				\
		name##_Instance* self){ 				\
	self->__methods = &name;					\
	self->__private = 						\
	(name##_Private*)&(((u8*)self)[sizeof(name##_Instance)]); 	\
		if(name##__Create__(args, self) == NULL){ 		\
		    ERR(ERR_INITFAIL, "failed to initialize " #name);	\
		    return self;}					\
	self->__init = true;						\
return self;}								\
									\
	name##_Instance* name##__Create__(				\
		name##_ConstructArgs args, 				\
		name##_Instance* self)					\


#define priv self->__private
#define private(name, ...) \
typedef struct name##_Private{__VA_ARGS__}name##_Private; \

#define setpriv(Class) *self->__private = (Class##_Private)

#define self(Class) inst(Class) self = class(Class) object;

#define passover *self = args; return self;

#define asClass(type)							\
	static const u64 sizeof_##type##_Private = 0;			\
	typedef type type##_Instance; 					\
	typedef type type##_ConstructArgs;				\
	inline static type##_Instance* type##_Construct(		\
		type##_ConstructArgs args,				\
		type##_Instance* self)					\

#define asClassExt(type, construct_args)				\
	static const u64 sizeof_##type##_Private = 0;			\
	typedef type type##_Instance; 					\
	typedef struct {construct_args;} type##_ConstructArgs;		\
	inline static type##_Instance* type##_Construct(		\
		type##_ConstructArgs args,				\
		type##_Instance* self)					\


#define Interface(name, ...) \
	typedef struct name##_Interface					\
	{__VA_ARGS__} name##_Interface; 				\

#define Type(name, ...) typedef struct{__VA_ARGS__}name; asClass(name){ passover }
#define Data(name, __INIT,...) typedef struct{__VA_ARGS__}name; asClassExt(name, __INIT)
#define Static(name, ...)						\
	Interface(name, __VA_ARGS__)					\
	extern name##_Interface name;					\

#define Impl(name) name##_Interface name = 				\

#define Class(name,__INIT, __FIELD, ...) 				\
	typedef struct name##_Private name##_Private;			\
	extern const u64 sizeof_##name##_Private;			\
	typedef struct name##_Instance name##_Instance; 		\
	typedef struct {__INIT} name##_ConstructArgs;			\
	Interface(name, interface(Object); __VA_ARGS__) 		\
	extern name##_Interface name;					\
	typedef struct name##_Instance{					\
		name##_Private* __private;				\
		const name##_Interface* __methods;			\
		__FIELD							\
		u8 __init : 1;						\
	}name##_Instance;						\
	name##_Instance* name##_Construct(				\
		name##_ConstructArgs args,				\
		name##_Instance* self);					\

#define isinit(object) (object->__init)

#define inst(Class) Class##_Instance*
#define intf(Class) const Class##_Interface*
#define data(DataClass) DataClass##_Instance

#define generic (inst(Object))
#define class(type) (inst(type))
#define cast(type) (type)

#define init(name, ptr, ...) name##_Construct((name##_ConstructArgs){__VA_ARGS__}, ptr)

#define new(name, ...) init(name, malloc(sizeof(name##_Instance) + sizeof_##name##_Private), __VA_ARGS__)
#define push(name, ...) init(name, alloca(sizeof(name##_Instance) + sizeof_##name##_Private), __VA_ARGS__)

#define del(object) if(object->__methods->Object.__DESTROY == NULL) ERR(ERR_NULLPTR,"no destructor specified for this object"); \
		    else if(object->__methods->Object.__DESTROY(generic object) == ERR_NONE) free(object);
#define pop(object) if(object->__methods->Object.__DESTROY == NULL) ERR(ERR_NULLPTR,"no destructor specified for this object"); \
		    else object->__methods->Object.__DESTROY(generic object)

/*----------------------|
       Base Types	|
----------------------*/


typedef uint64_t u64;
asClass(u64){ passover }

typedef uint32_t u32;
asClass(u32){ passover }

typedef uint16_t u16;
asClass(u16){ passover }

typedef uint8_t u8;
asClass(u8){ passover }

typedef int64_t i64;
asClass(i64){ passover }

typedef int32_t i32;
asClass(i32){ passover }

typedef int16_t i16;
asClass(i16){ passover }

typedef int8_t i8;
asClass(i8){ passover }

asClass(float){ passover }
asClass(double){ passover }

asClass(bool){ passover }

typedef struct{ char as_cchar; } c8;
asClassExt(c8, char cchar){ self->as_cchar = args.cchar; return self; };

typedef char16_t c16;
asClass(c16){ passover }

typedef char32_t c32;
asClass(c32){ passover }

typedef wchar_t  cwide;
asClass(cwide){ passover }

typedef char* cstr;
asClass(cstr){ passover }

typedef wchar_t* wstr;
asClass(wstr){ passover }

typedef void* pntr;
#define pntr_shift(ptr, shift_amt) ptr = ((void*)(&(((uint8_t*)ptr)[shift_amt])))
#define pntr_shiftcpy(ptr, shift_amt) ((void*)(&(((uint8_t*)ptr)[shift_amt])))
#define pntr_asVal(addr) (*(uint64_t*)&addr)
asClass(pntr){ passover }

Type(Object);

Interface(Object,
	u32 imethod(__HASH);			
	u32 imethod(__DESTROY);		
#ifdef __USER_CLASS_METHODS__
	__USER_CLASS_METHODS__				
#endif

)

typedef enum {
	BASETYPE_NULL,	BASETYPE_INT,    	
	BASETYPE_LONG,	BASETYPE_UINT,    	
	BASETYPE_ULONG, BASETYPE_FLOAT,   	
        BASETYPE_STRING, BASETYPE_CHAR,    	
        BASETYPE_POINTER, BASETYPE_BOOL,			
        BASETYPE_OBJECT		
}__Base_Type_ID__;

#define __Base_Type__(object) 			\
_Generic((object), 				\
i32:    	BASETYPE_INT,			\
u32:		BASETYPE_UINT, 			\
i64:    	BASETYPE_LONG,   		\
u64:    	BASETYPE_ULONG,   		\
i16:   		BASETYPE_INT,   		\
u16:   		BASETYPE_UINT,			\
u8:   		BASETYPE_UINT,		   	\
i8:   		BASETYPE_INT,		   	\
float:   	BASETYPE_FLOAT,   		\
double:  	BASETYPE_FLOAT,			\
const char*: 	BASETYPE_STRING,		\
char *:  	BASETYPE_STRING,		\
c8:	    	BASETYPE_CHAR,   		\
void *:  	BASETYPE_POINTER,		\
bool:		BASETYPE_BOOL, 			\
default: 	BASETYPE_OBJECT)		


#define asObject(var)					\
_Generic((var), 					\
i32:    	push(BaseType, BASETYPE_INT, &var),	\
u32:		push(BaseType, BASETYPE_UINT, &var), 	\
i64:    	push(BaseType, BASETYPE_LONG, &var),   	\
u64:    	push(BaseType, BASETYPE_ULONG, &var),   \
i16:   		push(BaseType, BASETYPE_INT, &var),   	\
u16:   		push(BaseType, BASETYPE_UINT, &var),	\
u8:   		push(BaseType, BASETYPE_UINT, &var),	\
i8:   		push(BaseType, BASETYPE_INT, &var),	\
float:   	push(BaseType, BASETYPE_FLOAT, &var),   \
double:  	push(BaseType, BASETYPE_FLOAT, &var),	\
const char*: 	push(BaseType, BASETYPE_STRING, &var),	\
cstr:	  	push(BaseType, BASETYPE_STRING, &var),	\
c8:	    	push(BaseType, BASETYPE_CHAR, &var),   	\
void *:  	push(BaseType, BASETYPE_POINTER, &var),	\
bool:		push(BaseType, BASETYPE_BOOL, &var), 	\
default: 	var)		

#define getMethods(type)							  \
_Generic(((data(type)){0}), 							  \
i32:    	*(push(BaseType, BASETYPE_INT, 	  &(data(type)){0})->__methods),\
u32:		*(push(BaseType, BASETYPE_UINT,   &(data(type)){0})->__methods),\
i64:    	*(push(BaseType, BASETYPE_LONG,   &(data(type)){0})->__methods),\
u64:    	*(push(BaseType, BASETYPE_ULONG,  &(data(type)){0})->__methods),\
i16:   		*(push(BaseType, BASETYPE_INT, 	  &(data(type)){0})->__methods),\
u16:   		*(push(BaseType, BASETYPE_UINT,   &(data(type)){0})->__methods),\
u8:   		*(push(BaseType, BASETYPE_UINT,   &(data(type)){0})->__methods),\
i8:   		*(push(BaseType, BASETYPE_INT, 	  &(data(type)){0})->__methods),\
float:   	*(push(BaseType, BASETYPE_FLOAT,  &(data(type)){0})->__methods),\
double:  	*(push(BaseType, BASETYPE_FLOAT,  &(data(type)){0})->__methods),\
const char*: 	*(push(BaseType, BASETYPE_STRING, &(data(type)){0})->__methods),\
cstr:	  	*(push(BaseType, BASETYPE_STRING, &(data(type)){0})->__methods),\
pntr: 	 	*(push(BaseType, BASETYPE_POINTER,&(data(type)){0})->__methods),\
bool:		*(push(BaseType, BASETYPE_BOOL,   &(data(type)){0})->__methods),\
default: 	type)		
