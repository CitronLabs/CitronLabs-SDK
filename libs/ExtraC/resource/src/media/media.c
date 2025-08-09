#include "../../include/media.h"

private(Media,
	inst(Resource) resource_handle,* data_resource; 
	inst(File) media_file;
	MEDIA_DATA_TYPE* media_data;
	void* format_data;
	u64 format_size;
	u8 is_loaded : 1;
)

u64 getMediaFileSize(const char* path){
	fsEntry file_ent = {0};

	if(getFileSystemEntry((char*)path, &file_ent) != ERR_NONE){
		ERR(RESOURCERR_INVALID, "could not find media file from path");
		return NULL;
	}
	if(file_ent.is_dir){
		ERR(RESOURCERR_INVALID, "path does not lead to an media file");
		return NULL;
	}

return file_ent.size;
}


bool methodimpl(Media, isLoaded){

	if(priv->is_loaded) return true;

	errvt ioerr;
	if((ioerr = File.Read(priv->media_file, priv->format_data, priv->format_size)) != ERR_NONE){
		if(ioerr != IOERR_ASYNC){
			ERR(RESOURCERR_FAIL, "failed to load resource");
			return false;
		}else{
			return false;
		}
	}
	priv->media_data = self->format->parse(priv->format_data);
	
	priv->is_loaded = true;

return true;	
}

errvt methodimpl(Media, forceLoad){
	
	if(priv->is_loaded) return OK;

	errvt ioerr;
	while((ioerr = File.Read(priv->media_file, priv->format_data, priv->format_size)) != ERR_NONE){
		if(ioerr != IOERR_ASYNC)
			return ERR(RESOURCERR_FAIL, "failed to load resource");
	}

return OK;
}


inst(Media) Media___COLLECT(inst(Collection) collection, Media_ConstructArgs args){
	
	u32 format_size = getMediaFileSize(args.path);

	inst(Resource) media_resource = new(Resource, collection, 
		sizeof(Media_Instance) + sizeof(Media_Private)
	);

	inst(Resource) format_data_resource = new(Resource, collection, format_size);

	if(media_resource == NULL){
		ERR(RESOURCERR_FAIL, "failed to create resource handle for media");
		if(format_data_resource != NULL) del(format_data_resource);
		return NULL;
	}
	
	if(format_data_resource == NULL){
		ERR(RESOURCERR_FAIL, "failed to create resource handle for media");
		if(media_resource != NULL) del(media_resource);
		return NULL;
	}

	inst(Media) self = Resource.getData(media_resource);

	classSetup(Media,
		.resource_handle = media_resource,
	    	.data_resource = format_data_resource,
	    	.is_loaded = false,
	    	.format_data = Resource.getData(format_data_resource),
	    	.format_size = format_size,
	    	.media_data = NULL,
	){	
		if(args.lazy_load){
			priv->media_file = new(File, (char*)args.path, FFL_READ | FFL_ASYNC);
			return self;
		}
        
		priv->media_file = new(File, (char*)args.path, FFL_READ);
        
		if(!isinit(priv->media_file)){
			ERR(RESOURCERR_INVALID, "could not open media file");
			return self;
		}
        
		if(File.Read(priv->media_file, priv->format_data, priv->format_size) != priv->format_size){
			ERR(RESOURCERR_INVALID, "failed to read media file");
			return self;
		}

	    	priv->is_loaded = true;
        
		priv->media_data = args.format->parse(priv->format_data);
		
		if(priv->media_data == NULL){
			ERR(RESOURCERR_INVALID, "failed to parse media file");
			return self;
		}
        
	}

return Resource.getData(media_resource);
}
inst(Media) Media_Create(intf(MediaFormat) format, void* metadata, MEDIA_DATA_TYPE* media_data, inst(Collection) collection){

	inst(Media) self = NULL; 
	
	u32 format_size = format->getAllocSize(metadata, media_data);

	if(collection != NULL){
	

		inst(Resource) media_resource = new(Resource, collection, 
			sizeof(Media_Instance) + sizeof(Media_Private)
		);

		inst(Resource) format_data_resource = new(Resource, collection, format_size);

		if(media_resource == NULL){
			ERR(RESOURCERR_FAIL, "failed to create resource handle for media");
			if(format_data_resource != NULL) del(format_data_resource);
			return NULL;
		}
	
		if(format_data_resource == NULL){
			ERR(RESOURCERR_FAIL, "failed to create resource handle for media");
			if(media_resource != NULL) del(media_resource);
			return NULL;
		}

		self = Resource.getData(media_resource);

		set_methods(Media);
		set_priv(Media){
			.resource_handle = media_resource,
			.format_data = shift_ptr(self, sizeof(Media_Instance) + sizeof(Media_Private)),
			.format_size = format_size,
			.media_file = NULL,
			.media_data = media_data
		};

	}else{
		self = calloc(1, sizeof(Media_Instance) + sizeof(Media_Private));

		set_methods(Media);
		set_priv(Media){
			.resource_handle = NULL,
			.format_data = malloc(format_size),
			.format_size = format_size,
			.media_file = NULL,
			.media_data = media_data
		};
	}

	priv->format_size = format->format(priv->format_data, priv->media_data, metadata);

	if(priv->format_size == 0){
		ERR(RESOURCERR_FAIL, "failed to format media data for export");
		return NULL;
	}

}

inst(Resource) methodimpl(Media, getResource){
	
	nonull(self, return NULL;);

	if(priv->resource_handle == NULL){
	  	ERR(RESOURCERR_INVALID, "no resource handle associated with this media");
		return NULL;
	}
return priv->resource_handle;
}

MEDIA_DATA_TYPE* methodimpl(Media, getMediaData){
	
	if(!Media.isLoaded(self)){
		ERR(RESOURCERR_NOTLOADED, "media has not loaded yet");
		return NULL;
	}

return priv->media_data;
}

void* methodimpl(Media, getFormatData){
	
	if(!Media.isLoaded(self)){
		ERR(RESOURCERR_NOTLOADED, "media has not loaded yet");
		return NULL;
	}

return priv->format_data;
}

errvt methodimpl(Media, Reformat,, void* metadata){


	u64 new_size = self->format->getAllocSize(metadata, priv->media_data);
	if(new_size > priv->format_size){
		if(priv->resource_handle != NULL){
			Resource.resize(priv->resource_handle, 
		   		new_size +
		   		sizeof(Media_Instance) + 
		   		sizeof(Media_Private)
		   	);
		}
	}
	if(new_size != priv->format_size)
		priv->format_size = new_size;
	

	u64 formatted_len = self->format->format(priv->format_data, metadata, priv->media_data);
		
	if(formatted_len == 0){
		ERR(RESOURCERR_FAIL, "failed to format media data for export");
		return NULL;
	}

return OK;
}


construct(Media,
	.getResource = Media_getResource,
	.forceLoad = Media_forceLoad,
	.isLoaded = Media_isLoaded,
	.getMediaData = Media_getMediaData,
	.reformat = Media_Reformat,
	.create = Media_Create,
	.__COLLECT = Media___COLLECT
){
	fsEntry file_ent = {0};

	if(getFileSystemEntry((char*)args.path, &file_ent) != ERR_NONE){
		ERR(RESOURCERR_INVALID, "could not find media file from path");
		return self;
	}
	if(file_ent.is_dir){
		ERR(RESOURCERR_INVALID, "path does not lead to an media file");
		return self;
	}

	classSetup(Media,		
		.format_data = malloc(file_ent.size),
	    	.format_size = file_ent.size,
	    	.media_data = NULL,
	    	.is_loaded = false
	){	
		if(args.lazy_load){
			priv->media_file = new(File, (char*)args.path, FFL_READ | FFL_ASYNC);
			break;
		}
        
		priv->media_file = new(File, (char*)args.path, FFL_READ);
        
		if(!isinit(priv->media_file)){
			ERR(RESOURCERR_INVALID, "could not open media file");
			break;
		}
        
		if(File.Read(priv->media_file, priv->format_data, priv->format_size) != priv->format_size){
			ERR(RESOURCERR_INVALID, "failed to read media file");
			break;
		}
	    	
		priv->is_loaded = true;
        
		priv->media_data = args.format->parse(priv->format_data);
		
		if(priv->media_data == NULL){
			ERR(RESOURCERR_INVALID, "failed to parse media file");
			break;
		}
        
	}
return self;
}
