#pragma once
#include "../../include/resource.h"


typedef struct memiddef{
	u64 nodenum : 32;  //4 bytes
	u64 leafnum : 32;  //4 bytes
}memiddef;


typedef struct  mmleaf{	
	memid parentnodetoken;
	void* data;
	u64 size;
	u32 allocator_index;
	mmprot_info protections;
} mmleaf; 

typedef struct  mmnode{
	// META-DATA
	mmprot_info protections;
	u32 childrennum : 24;

	// ID-DATA
	memiddef token;
	struct mmnode* firstchild;
	struct mmnode* nextsibling;
	struct mmnode* parent;

	//CONTENTS
	List(mmleaf*) contents;

} mmnode;

typedef struct mmalloc{
	intf(Allocator) alloc_interface;
	void* allocator;
	u32 num_resources;
} mmalloc;

private(MemoryMap,
	Pool(mmnode) nodes;
	Pool(mmleaf) leafs;
	List(mmalloc) allocators;
	List(mmnode*) active_nodes;
	memiddef maxvalidtoken;
)

/*--------------|
      FUNCS	|
--------------*/

errvt freeEntireTree(inst(MemoryMap) memmap);
errvt getNode(inst(MemoryMap) memmap, mmnode** returnnode, memiddef node);
errvt getLeaf(mmnode node,  mmleaf** retleaf, memiddef tokendef);
errvt addLeaf(inst(MemoryMap) memmap,  mmnode* node, memid* returntoken,  mmleaf_info metadata);
errvt addNode(inst(MemoryMap) memmap,  mmnode* maptonode, memid* returntoken);
