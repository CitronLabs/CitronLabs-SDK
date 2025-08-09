#include "./mem.h"

errvt getLeaf(mmnode node, mmleaf** retleaf, memiddef iddef){
	
	nonull(node.contents);	
	u64 contentsnum = List.Size(node.contents);

	if(contentsnum == 0) return ERR(
		RESOURCERR_TOKENINDEX, "contents are empty");
	if(iddef.leafnum == 0 || iddef.leafnum > contentsnum) return ERR(
		RESOURCERR_TOKENINDEX, "invalid leaf number");	

	mmleaf** res = List.GetPointer(node.contents, iddef.leafnum - 1);
	
	if(res == NULL) return ERR(
		RESOURCERR_TOKENINDEX, "unable to index leaf list");	
	*retleaf = *res;

return OK;
}

errvt methodimpl(MemoryMap, GetLeaf,,memid id, mmleaf_info* metadata){

	nonull(priv);

	mmnode* node = NULL;
	mmleaf* leaf = NULL;

	if(getNode(self, &node, *(memiddef*)&id)) return ERR(
		RESOURCERR_TOKENINDEX, "could not get node from id");

	if(getLeaf(*node, &leaf, *(memiddef*)&id)) return ERR(
		RESOURCERR_TOKENINDEX, "could not get node from id");

	
	*metadata = (mmleaf_info){
		.size = leaf->size,
		.protections = leaf->protections,
		.allocator_index = leaf->allocator_index
	};

return OK;
}
#define creatTokenVal(_nodenum, _leafnum) *(memid*)&(memiddef){.nodenum = _nodenum,.leafnum = _leafnum };
#define getTokenVal(id) ((memiddef*)&id)
#define getTokenFromVal(idval) ((memid*)&idval)

errvt methodimpl(MemoryMap, addLeaf,, mmnode* node, memid* returnid, mmleaf_info metadata){



	mmleaf* res  = NULL;

	if(List.Size(priv->allocators) > metadata.allocator_index)
		return ERR(RESOURCERR_INVALID, "invalid allocator index");
	

	mmalloc* allocator = List.GetPointer(priv->allocators, metadata.allocator_index);

	res = Pool.Allocator.New(priv->leafs, 1);
	*res = (mmleaf){
		.allocator_index = metadata.allocator_index,
		
		.protections = metadata.protections.protections == 0 ?
				node->protections : metadata.protections,
		.data = allocator->alloc_interface->New(allocator->allocator, metadata.size),
		.size = metadata.size
	};

	if(res->data == NULL){
		return ERR(RESOURCERR_TOKENCREATE, "could not allocate data for leaf");
	}
	*returnid = creatTokenVal(node->token.nodenum, List.Size(node->contents));
	
	List.FillSlot(node->contents, &res);

return OK;
}

memid methodimpl(MemoryMap, AddLeaf,, memid maptonode, mmleaf_info metadata){

	nonull(self);

	mmnode* node = NULL;

	if(getNode(self, &node, *(memiddef*)&maptonode)) return ERR(
		RESOURCERR_TOKENINDEX, "could not get node from id");


	memid result = 0;

	if(addLeaf(self, node, &result, metadata)) return ERR(
		RESOURCERR_TOKENINDEX, "could not get node from id");

return result;
}
errvt methodimpl(MemoryMap, CutLeaf,, memid id){

	nonull(priv);

	mmnode* node = NULL;
	mmleaf* leaf = NULL;

	if(getNode(self, &node, *getTokenVal(id))) return ERR(
		RESOURCERR_TOKENINDEX, "could not get node from id");

	if(getLeaf(*node, &leaf, *getTokenVal(id))) return ERR(
		RESOURCERR_TOKENINDEX, "could not get node from id");

	Pool.Allocator.Delete(priv->leafs, leaf);
	List.SetFree(node->contents, getTokenVal(id)->leafnum);

return OK;
}
errvt methodimpl(MemoryMap, MoveLeaf,, memid* id, memid maptoid){

	nonull(priv);
	
	mmnode* node = NULL;
	mmleaf* leaf = NULL;

	//Getting the original node for the leaf
	if(getNode(self, &node, *getTokenVal(id))) return ERR(
		RESOURCERR_TOKENINDEX, "could not get node from id");
	
	//Getting the leaf data
	if(getLeaf(*node, &leaf, *getTokenVal(id))) return ERR(
		RESOURCERR_TOKENINDEX, "could not get node from id");

	List.SetFree(node->contents, getTokenVal(id)->leafnum);

	//Getting the map-to-node
	if(getNode(self, &node, *getTokenVal(maptoid))) return ERR(
		RESOURCERR_TOKENINDEX, "could not get node from map-to-id");
	
	getTokenVal(id)->leafnum = List.FillSlot(node->contents, &leaf);
		
return OK;
}




