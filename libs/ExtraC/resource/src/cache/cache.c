#include "cachy.h"

#define DEFAULT_CACHECLEANUP_COUNTER 100
#define DEFAULT_CACHESLOT_FREQUENCY 5

typedef struct cacheslot{
	u64 frequency, 
	    size;
	void* ptr;
	std_str label;
}cacheslot;

typedef struct std_cache{
	bool autocleanup;
	std_mempool* data;
	std_list(cacheslot) slots; 
	std_stack(cache_id) free_slots;
	std_map(cache_id) labels;
	u16 cleanup_counter;
}std_cache;

std_cache* cacheInit(size_t max_size_in_bytes, bool autocleanup, u16 cleanup_counter){
	
	std_cache* res = calloc(1, sizeof(std_cache));
	*res = (std_cache){
		.data = memPoolInit(max_size_in_bytes, NULL),
		.labels = mapInit(10, std_str, cache_id),
		.autocleanup = autocleanup,
		.cleanup_counter = autocleanup && cleanup_counter != 0 ?
			cleanup_counter :
			DEFAULT_CACHECLEANUP_COUNTER
	};
	
return res;
}

errvt cacheClean(std_cache* cache){
	
	return_ifnull(cache)

	listForEach(cache->slots, cacheslot, slot){
		
		if(slot.frequency == 0){
			u64 key = UINT64_MAX;
			memPoolReturn(cache->data, slot.ptr, slot.size);
			if((key = mapSearch(cache->labels, slot.label)) != UINT64_MAX)
				mapRemove(cache->labels, key);
			stackPush(cache->free_slots, &slot_iterator);
		} 
		else slot.frequency--;
	}

return NOERROR;
}

cache_id cacheSearch(std_cache* cache, std_str label){

	post_ifnull(cache, return UINT64_MAX)
	post_ifnull(label.txt, return UINT64_MAX)

	cacheslot* slot = NULL;
	u32 mindex = UINT32_MAX;
	cache_id slot_id;

	checkposterr((mindex = mapSearch(cache->labels, label)) == UINT32_MAX, 
	      CACHYERR_SEARCH, "could not find cache slot with specified label");

	checkposterr(mapIndex(cache->labels, mindex, &slot_id),
	      CACHYERR_SEARCH, "could not index cache slot", return NULL;)

	if(cache->autocleanup) cache->cleanup_counter--;
}


cache_id cacheAdd(std_cache* cache, size_t size,  std_str label, void* data){
	
	post_ifnull(cache, return UINT64_MAX)
	post_ifnull(data, return UINT64_MAX)
	
	cache_id res;
	void* cache_data = NULL;
	cacheslot slot = {
		.label = label,
		.size = size,
		.ptr = data,
		.frequency = DEFAULT_CACHESLOT_FREQUENCY

	};

	checkposterr((cache_data = memPoolGet(cache->data, size)) != NULL, 
	      CACHYERR_ADD, "could not add data to cache");

	if(stackCount(cache->free_slots) > 0){
		stackPop(cache->free_slots, &res);
		cacheslot* slotptr = listGetPointer(cache->slots, res);
		*slotptr = slot;
	}else{
		res = listSize(cache->slots);
		listAppend(cache->slots, &slot);
	}

return res;
}

void* cacheGet(std_cache* cache, cache_id id){

	cacheslot* slotptr = NULL;
	checkposterr((slotptr = listGetPointer(cache->slots, id)) == NULL,
	      CACHYERR_GET, "invalid cache id")
	
	slotptr->frequency++;

	return slotptr->ptr;
}

errvt cacheFree(std_cache* cache){
	return_ifnull(cache);

	memPoolFree(cache->data);	
	listFree(cache->slots);
	mapFree(cache->labels);
	stackFree(cache->free_slots);
	free(cache);

return NOERROR;
}
