#pragma once
#include "std-libc.h"
#include "std-error.h"
#include "std-utils.h"

#ifndef __USER_CONFIG__
#include "xc-user-config.h"
#endif

#if STDMALLOC_HIJACKMALLOC
#define malloc(size) CMalloc.Allocator.New(c_malloc, size, NULL)
#define calloc(nmemb, size) CMalloc.Allocator.New(c_malloc, nmemb, size, NULL) 
#define realloc(data, size) CMalloc.Allocator.Resize(c_malloc, data, size, NULL) 
#define free(ptr) CMalloc.Allocator.Delete(c_malloc, ptr, NULL)
#endif


#ifdef EXPOSE_INIT 
	errvt init_stdExtMalloc();
#endif

Interface(Allocator, 
	void* imethod(New,, u64 size, ...);
      	void* imethod(Resize,, void* instance, u64 size, ...);
      	errvt imethod(Delete,, void* instance, ...);
);

Class(CMalloc,
__INIT(u64 max_alloc),
__FIELD(
	size_t max_alloc;
	bool(*overflow_handler)(inst(CMalloc), u64 overflowed_datasize);
),
	interface(Allocator);
      	u64 method(CMalloc, getBytesAlloced);
)

Class(Pool,
__INIT(u64 member_size, init_size, limit),
__FIELD(),
	#define Pool(type) inst(Pool)

	interface(Allocator);
)

Class(Arena,
__INIT(u64 init_size),
__FIELD(),
	interface(Allocator);
)

extern inst(CMalloc) c_malloc;
