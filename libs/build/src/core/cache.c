#pragma once
#define __EBEE_SRC_DEF__
#include "../ebee-data.h"

errvt EB_cacheLoad(EBEE_CACHEID cache_type, inst(String) key, inst(Struct) data){

	Map.Insert(__eb_data->__private->caches[COMPILE_CACHE],  
		key,
     		data);
return OK;
}
inst(Struct) EB_cacheSearch(EBEE_CACHEID cache_type, inst(String) key){
	
	inst(Struct) result = 
		Map.Search(__eb_data->__private->caches[cache_type], 
		key
	);
	
return result;
}
errvt EB_cacheRemove(EBEE_CACHEID cache_type, inst(String) key){
	
	nonull(key, return nullerr);
	
	if(key->type != CT_ASCI)
		return ERR(BUILDERR_CACHE, "key string can only be in ascii");

	if(Map.Remove(__eb_data->__private->caches[cache_type], key) != ERR_NONE)
		return ERR(BUILDERR_CACHE, "invalid key could not remove");

return OK;
}

errvt EB_cacheStore(EBEE_CACHEID cache_type){



return OK;
}

