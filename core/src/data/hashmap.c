#include "datastructs.h"


#if !(STDDATA_MAP_OVERIDEHASH)

#define HASHMAP_HASH_INIT 2166136261u
u32 Map_Hash(void* data_ptr, u64 size){
	char* data = data_ptr;
	size_t nblocks = size / 8;
	u64 hash = HASHMAP_HASH_INIT;
	for (size_t i = 0; i < nblocks; ++i)
	{
		hash ^= (u64)data[0] << 0 | (u64)data[1] << 8 |
			 (u64)data[2] << 16 | (u64)data[3] << 24 |
			 (u64)data[4] << 32 | (u64)data[5] << 40 |
			 (u64)data[6] << 48 | (u64)data[7] << 56;
		hash *= 0xbf58476d1ce4e5b9;
		data += 8;
	}

	u64 last = size & 0xff;
	switch (size % 8)
	{
	case 7:
		last |= (u64)data[6] << 56; /* fallthrough */
	case 6:
		last |= (u64)data[5] << 48; /* fallthrough */
	case 5:
		last |= (u64)data[4] << 40; /* fallthrough */
	case 4:
		last |= (u64)data[3] << 32; /* fallthrough */
	case 3:
		last |= (u64)data[2] << 24; /* fallthrough */
	case 2:
		last |= (u64)data[1] << 16; /* fallthrough */
	case 1:
		last |= (u64)data[0] << 8;
		hash ^= last;
		hash *= 0xd6e8feb86659fd93;
	}

	return (u32)(hash ^ hash >> 32);
}
#endif

errvt methodimpl(Map,SetDefault,, void* data){
	
	nonull(self);
	nonull(data);
	
	data_entry def_bucket = {
		.hash = 0,
		.key = NULL,
		.data = calloc(1, priv->item_size),
	};

	if(NULL == def_bucket.data) return ERR(
		DATAERR_MEMALLOC, "could not initialize default data bucket");


	memcpy(def_bucket.data, data, priv->item_size);

	List.Append(priv->buckets, &def_bucket, 1);

return OK;
}

u32 methodimpl(Map,Insert,, void* key_data, void* itemptr){
	
	nonull(self, return UINT32_MAX);
	nonull(key_data, return UINT32_MAX);
	nonull(itemptr, return UINT32_MAX);
	
	
	u64 place = 10;
	u8 placenum = 10;
	u32 key = UINT32_MAX;
	u32 hashvalue =
	    priv->key_hash_func == NULL ?
		Map.Hash(key_data, priv->key_size) 
		:
		priv->key_hash_func(key_data);
	
	for(;;){
		if(priv->bucket_indexes[hashvalue%place] == 0){
			key = (hashvalue%place);
			u32 index = List.Size(priv->buckets);
			priv->bucket_indexes[key] = index;
			List.Append(priv->buckets, &(data_entry){
				.hash = hashvalue,
				.data = calloc(1, priv->item_size),
				.key = calloc(priv->key_size, sizeof(u8)),
			}, 1);
			memcpy(
				((data_entry*)List.GetPointer(
					priv->buckets, 
					index)
				)->key,
				key_data,
				priv->key_size);
			memcpy(
				((data_entry*)List.GetPointer(
					priv->buckets, 
					index)
				)->data,
				itemptr,
				priv->item_size);
			break;
		}
		place+=placenum;
		if(place >= (10*10000) || place >= priv->allocednum){
			priv->bucket_indexes = realloc(priv->bucket_indexes, 
			    (priv->allocednum * 2) * sizeof(u32));
			priv->allocednum *= 2;
		}	
	}
	
return key;
}

u32 methodimpl(Map, SearchIndex,, void* key){

	nonull(key, return UINT32_MAX);
	nonull(self, return UINT32_MAX);
	
	u64 place = 10;
	u8 placenum = 10;
	u32 hashvalue = 
	    priv->key_hash_func == NULL ?
		Map.Hash(key, priv->key_size) 
		:
		priv->key_hash_func(key);

	for(;;){
		if(priv->bucket_indexes[hashvalue%place] != 0){

			data_entry* bucket = 
				List.GetPointer(
					priv->buckets, 
					priv->bucket_indexes[hashvalue%place]
				);
				
			if(bucket->hash == hashvalue)
				return hashvalue%place;
		}
		place+=placenum;
		if(place >= (10*10000) || place >= priv->allocednum){
			break;
		}
	}
return priv->default_index;
}


void* methodimpl(Map, Search,, void* key){

	u32 mindex = Map.SearchIndex(self, key);

	if(UINT32_MAX == mindex) {
		ERR(DATAERR_EMPTY, "key index not found");
		return NULL;
	}

return Map.Index(self, mindex);
}

void* methodimpl(Map,Index,, u32 key){
	nonull(self, return NULL)

	if(key > priv->allocednum){
		ERR(DATAERR_OUTOFRANGE, "invalid key");
		return NULL;
	}

	data_entry* buckets = List.GetPointer(priv->buckets, 0);
	u32 buck_index = priv->bucket_indexes[key];
	
	if(buck_index == 0) {
		ERR(DATAERR_OUTOFRANGE, "invalid key");
		return NULL;
	}

return buckets->data;
}
errvt methodimpl(Map,Remove,, void* key){
	nonull(self, return nullerr)
	
	u32 mindex = Map.SearchIndex(self, key);

	if(UINT32_MAX == mindex) 
		return ERR(DATAERR_EMPTY, "key index not found");

	data_entry* bucket = 
		List.GetPointer(
			priv->buckets, 
			priv->bucket_indexes[mindex]
		);
	if(bucket == NULL) 
		ERR(DATAERR_OUTOFRANGE, "invalid key");

	bucket->hash = 0; 
	free(bucket->data); 
return OK;
}
List(data_entry) methodimpl(Map,GetEntries){

return priv->buckets;
}
errvt imethodimpl(Map,Free){
	self_as(Map);
	nonull(self, return nullerr;);
	
	del(priv->buckets);
	free(priv->bucket_indexes); 
return OK;
}

u64 methodimpl(Map, Count){
	return List.Size(priv->buckets);
}

errvt methodimpl(Map, Limit,, u64 limit){
	return List.Limit(priv->buckets, limit);
}

u64 imethodimpl(Map, Scan,, FORMAT_ID* formats, inst(String) in){

	nonull(object, return 0;);
	inst(Map) self = object;

return DSN.parseMap(NULL, &self, in);
}

u64 imethodimpl(Map, Print,, FORMAT_ID* formats, inst(StringBuilder) out){

	inst(Map) self = object;

	u64 formated_len = 0;
	switch(formats[FORMAT_DATA]){
	case DATA_DSN:
		formated_len += DSN.formatMap(NULL, self, out);
	break;
	case DATA_DEBUG:
		StringBuilder.Append(out, s("(Map){"));
		
		StringBuilder.Append(out, NULL, ".data = ", $((void*)priv->buckets), ", ", endstr);
		StringBuilder.Append(out, NULL, ".item_size = ", $(priv->item_size), ", ", endstr);

		StringBuilder.Append(out, s(" }"));			
	break;
	default:
		return 0;
	}
return formated_len;
}

construct(Map,
	.Formatter = {
		.Scan = Map_Scan,
		.Print = Map_Print
	},
	.Count = Map_Count,
	.SetDefault = Map_SetDefault,
	.GetEntries = Map_GetEntries,
	.Index = Map_Index,
	.Search = Map_Search,
	.SearchIndex = Map_SearchIndex,
	.Insert = Map_Insert,
	.Remove = Map_Remove,
	.Limit = Map_Limit,
	.Hash = Map_Hash,
	.Object.__DESTROY = Map_Free
){

	u64 init_size = args.init_size == 0 ? 10 : args.init_size;

	*priv = (Map_Private){
		.bucket_indexes = calloc(init_size + (init_size / 2), sizeof(u32)),
		.buckets = new(List, .init_size = 10, .type_size = sizeof(data_entry)),
		.item_size = args.data_type_size,
		.key_size = args.key_type_size,
		.allocednum = init_size + (init_size / 2),
		.default_index = UINT32_MAX,
		.key_hash_func = args.key_hash_func
	};

	if(args.literal != NULL){
	    loop(i, args.init_size){
		    if(args.literal[i].key != NULL){
			Map.Insert(self, args.literal[i].key, args.literal[i].data);
		    }
		    else if(priv->default_index == UINT32_MAX){
			Map.SetDefault(self, args.literal[i].data);
	    	}
	    }
	}
return self;
}
