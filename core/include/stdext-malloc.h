#pragma once
#include "std-libc.h"
#include "std-error.h"
#include "std-types.h"
#include "std-utils.h"

#ifndef __USER_CONFIG__
#include "xc-user-config.h"
#endif

#if STDMALLOC_HIJACKMALLOC
#define malloc(size) CMalloc.Allocator.New(generic c_malloc, size, NULL)
#define calloc(nmemb, size) CMalloc.Allocator.New(generic c_malloc, nmemb, &(u64){size}) 
#define realloc(data, size) CMalloc.Allocator.Resize(generic c_malloc, data, size, NULL) 
#define free(ptr) CMalloc.Allocator.Delete(generic c_malloc, ptr, NULL)
#endif


#ifdef EXPOSE_INIT 
	errvt init_stdExtMalloc();
#endif

Interface(Allocator,
	void* imethod(New,, u64 size, void* ex_args);
      	void* imethod(Resize,, void* instance, u64 size, void* ex_args);
      	errvt imethod(Delete,, void* instance, void* ex_args);
      	errvt imethod(setMax,, u64 size);
      	bool  imethod(isStatic);
      	u64  imethod(getBytesAlloced);
);

Class(Buffer,
__INIT(u64 size; u16 type_size),
__FIELD(void* pointer),
	#define Buffer(type) inst(Buffer)
	#define buffer(type, size) \
      		init(Buffer, sizeof(Buffer) + sizeof_Buffer_Private + (sizeof(type) * size), size, sizeof(type))

	interface(Allocator);

	bool method(Buffer, isMaxed);
	u64  method(Buffer, getTotalSize);
	u64  method(Buffer, getTypeSize);
	u64  method(Buffer, getItemNum);
      	u64  method(Buffer, realloc,, u64 num);
      	u64  method(Buffer, cast,, u64 type_size);
)

Class(CMalloc,
__INIT(u64 max_alloc),
__FIELD(
	bool(*overflow_handler)(inst(CMalloc), u64 overflowed_datasize);
),
	interface(Allocator);
)

Class(Pool, 
__INIT(u64 member_size, init_size, limit; bool isStatic),
__FIELD(),
	#define Pool(type) inst(Pool)

	interface(Allocator);
      	void* method(Pool, Alloc,, u64 num);
      	errvt method(Pool, Return,, void* instance);
      	errvt method(Pool, Reserve,, u64 num_members);
      	errvt method(Pool, Grow,, u64 add_num_members);
)

Class(Arena,
__INIT(u64 init_size; bool isStatic),
__FIELD(),
	interface(Allocator);
      	void* method(Arena, Alloc,, u64 num_bytes);
      	errvt method(Arena, Reserve,, u64 num_bytes);
      	errvt method(Arena, Grow,, u64 add_num_bytes);
)

extern inst(CMalloc) c_malloc;
