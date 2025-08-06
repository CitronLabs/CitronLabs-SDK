#pragma once
#include "./libc.h"
#include "./utils.h"
#include <uchar.h>

/*------------------------------|
       Class Preprocessors	|
-------------------------------*/
#define fn(name, ...) (*name)(__VA_ARGS__)

#define method(Class,name, ...) (*name)(Class##_Instance* self __VA_ARGS__)
#define imethod(name, ...) (*name)(inst(Object) object __VA_ARGS__)
#define vmethod(name, ...) (*name)(__VA_ARGS__);

#define methodimpl(Class,Routine, ...) 			\
	Class##_##Routine(Class##_Instance* self __VA_ARGS__)

#define imethodimpl(Class,Routine, ...) 		\
	Class##_##Routine(inst(Object) object __VA_ARGS__)

#define vmethodimpl(Class,Routine, ...) 		\
	Class##_##Routine(__VA_ARGS__)

#define __INIT(...) __VA_ARGS__;
#define __FIELD(...) __VA_ARGS__;
#define __METHODS(...) __VA_ARGS__

#define interface(Class) const Class##_Interface Class
#define inhert(Class) Class##_Instance Class

#define interfaceAs(Class) const Class##_Interface 
#define inhertAs(Class) Class##_Instance 

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
	static type##_Instance* type##_Construct(			\
		type##_ConstructArgs args,				\
		type##_Instance* self)					\

#define asClassExt(type, construct_args)				\
	static const u64 sizeof_##type##_Private = 0;			\
	typedef type type##_Instance; 					\
	typedef struct {construct_args;} type##_ConstructArgs;		\
	static type##_Instance* type##_Construct(			\
		type##_ConstructArgs args,				\
		type##_Instance* self)					\


#define Interface(name, ...) 						\
	typedef struct name##_Interface					\
	{__VA_ARGS__} name##_Interface; 				\

#define Type(name, ...) 						\
	typedef struct name name; 					\
	typedef struct name{__VA_ARGS__}name; 				\
	asClass(name){ passover }


#define Data(name, __INIT,...) 						\
	typedef struct name name; 					\
	typedef struct name{__VA_ARGS__}name;				\
	asClassExt(name, __INIT)


#define Static(name, ...)						\
	Interface(name, __VA_ARGS__)					\
	extern name##_Interface name;					\

#define Enum(name, ...) 						\
	typedef enum {__VA_ARGS__} name; 				\
	asClass(name){ passover }

#define State(name, __INIT, ...) 					\
	typedef enum {__VA_ARGS__} 					\
	name; asClassExt(name, __INIT)

#define Impl(name) 	    name##_Interface name = 				
#define ImplAs(Class, name) Class##_Interface name = 				

#define Decl(name) 							\
	typedef struct name##_Instance name##_Instance; 		\
	typedef struct name##_ConstructArgs name##_ConstructArgs;	\
	typedef struct name##_Interface	name##_Interface;		\
	name##_Instance* name##_Construct(				\
		name##_ConstructArgs args,				\
		name##_Instance* self);					\

#define __GLOBAL_METHODS__
#include "config.h"
#undef __GLOBAL_METHODS__

#define Class(name,__INIT, __FIELD, ...) 				\
	typedef struct name##_Private name##_Private;			\
	extern const u64 sizeof_##name##_Private;			\
	typedef struct name##_Instance name##_Instance; 		\
	typedef struct name##_ConstructArgs				\
	{__INIT} name##_ConstructArgs;					\
	Interface(name, CORE_METHODS(name) __VA_ARGS__) 		\
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

typedef void* inst;
#define inst(Class) Class##_Instance*
#define intf(Class) const Class##_Interface*
#define data(Class) Class##_Instance
#define ifob(Class) struct{intf(Class) intf; inst(Object) obj;}

#define generic (inst(Object))
#define class(type) (inst(type))
#define cast(type) (type)

#define init(name, ptr, ...) name##_Construct((name##_ConstructArgs){__VA_ARGS__}, ptr)

#define new(name, ...) init(name, malloc(sizeof(name##_Instance) + sizeof_##name##_Private), __VA_ARGS__)
#define push(name, ...) init(name, alloca(sizeof(name##_Instance) + sizeof_##name##_Private), __VA_ARGS__)

#define del(object) if((generic object)->__methods->__DESTROY == NULL) ERR(ERR_NULLPTR,"no destructor specified for this object"); \
		    else if((generic object)->__methods->__DESTROY(generic object) == ERR_NONE) free(object);
#define pop(object) if((generic object)->__methods->__DESTROY == NULL) ERR(ERR_NULLPTR,"no destructor specified for this object"); \
		    else (generic object)->__methods->__DESTROY(generic (object))

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

typedef wchar_t  rune;
asClass(rune){ passover }

typedef char* cstr;
asClassExt(cstr, __INIT(cstr txt; u64 len))
{ *self = calloc(args.len, sizeof(char)); strncpy(*self, args.txt, args.len); return self;}

typedef wchar_t* wstr;
asClass(wstr){ passover }

typedef void* pntr;
#define arry(type) type*
#define pntr_shift(ptr, shift_amt) ptr = ((void*)(&(((uint8_t*)ptr)[shift_amt])))
#define pntr_shiftcpy(ptr, shift_amt) ((void*)(&(((uint8_t*)ptr)[shift_amt])))
#define pntr_asVal(addr) (*(uint64_t*)&addr)
asClass(pntr){ passover }

typedef u32 errvt;

Class(Object,,,);


