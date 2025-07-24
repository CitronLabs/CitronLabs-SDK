#include "extern.h"

#define CACHY_ERRORCODES \
CACHYERR_GET,		\	
CACHYERR_ADD,		\
CACHYERR_SEARCH		\

typedef u32 cache_id;

#define AUTOCLEANUP_FALSE false
#define AUTOCLEANUP_TRUE true

Class(Cache,
__INIT(
	size_t max_size_in_bytes;
      	bool auto_cleanup;
      	u16 cleanup_counter;
),
__FIELD(),
	cache_id method(Cache, Add,, size_t size_in_bytes, inst(String) label, void* data);
	void* method(Cache, Get,, cache_id id);
	void* method(Cache, Search,, inst(String) label);
      	errvt method(Cache, Clean);
)


