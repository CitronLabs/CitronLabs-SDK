#pragma once

#include "extern.h"

/*------------------------------\
           Memory Tree	    	|
------------------------------*/

#define MEMFLAG_LOCK 0x01
#define MEMFLAG_DIRECTACCESS 0x02
#define MEMFLAG_READ 0x02
#define MEMFLAG_WRITE 0x02

typedef u64 memid; asClass(memid){ passover }
typedef u32 allocid; asClass(allocid){ passover }

typedef union{
	struct{
	    u8 direct_access : 1;
	    u8 locked : 1;
	}flags;

	u32 protections;
}mmprot_info;

Type(mmnode_info,
	u32 childrennum : 24;
	u32 contentsnum : 32;
	mmprot_info protections;
);

Type(mmleaf_info,
	allocid allocator_index;
	mmprot_info protections;
	u64 size;
);

// Allocator => MemoryMap && Collections => Resources
// 
// Allocators handle the allocation of the memory;
//
// MemoryMaps && Collections handle management of memory;
//
// Resources are a handle to a piece of memory;

typedef struct Resource_Instance Resource_Instance;

Class(MemoryMap,
__INIT(intf(Allocator) default_alloc_intf; void* default_alloc; mmprot_info protections),
__FIELD(),
	
	#define ROOT_TOKEN 0

      	bool method(MemoryMap, validateMemID,, memid id);
	allocid method(MemoryMap, registerAllocator,, intf(Allocator) set_allocator_intf, void* set_allocator);
	memid method(MemoryMap, Nest,, memid parent, inst(MemoryMap) nested_tree);
	
      	errvt 	method(MemoryMap, GetNode,,  memid  token,  mmnode_info* metadata);
	memid   method(MemoryMap, AddNode,,  memid  parent, mmprot_info* protections);
	errvt 	method(MemoryMap, CutNode,,  memid  token);
	errvt 	method(MemoryMap, MoveNode,, memid* token,  memid maptoid);


	errvt 	method(MemoryMap, GetLeaf,,  memid  token,  mmleaf_info* metadata);
	memid   method(MemoryMap, AddLeaf,,  memid  parent, mmleaf_info metadata);
	errvt 	method(MemoryMap, CutLeaf,,  memid  token);
	errvt 	method(MemoryMap, MoveLeaf,, memid* token,  memid maptotoken);
)


Class(Collection,
__INIT(inst(MemoryMap) memMap; memid parent;),
__FIELD(u8 warnRemoval),
	
	#define collect(Collection, Class, ...) Class.__COLLECT(Collection, (Class##_ConstructArgs){__VA_ARGS__})

	u32 method(Collection, numOfResources);

)

Class(Resource,
__INIT(inst(Collection) collection; size_t size),
__FIELD(),
      	void* method(Resource, getData);
      	errvt method(Resource, setDestructor,, errvt(*destructor)(void*));
      	bool method(Resource,  isNearRemoval);
	errvt method(Resource, moveTo,, inst(Collection) new_collection);
	errvt method(Resource, resize,, size_t new_size);

)
