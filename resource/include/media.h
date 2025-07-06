#pragma once
#include "./resource.h"

typedef struct MediaFormat_Interface MediaFormat_Interface;

typedef enum {
	MEDIA_IMAGE,
	MEDIA_AUDIO,
	MEDIA_VECTOR,
	MEDIA_MODEL3D,
	MEDIA_VIDEO
}MEDIA_DATA_TYPE;

Class(Media,
__INIT(const char* path; intf(MediaFormat) format; bool lazy_load),
__FIELD(intf(MediaFormat) format),
	
      	inst(Media)(*create)(intf(MediaFormat) format, void* metadata, MEDIA_DATA_TYPE* media_data, inst(Collection) collection);
      	errvt method(Media, reformat,, void* metadata);

      	inst(Resource) method(Media, getResource);
      	MEDIA_DATA_TYPE* method(Media, getMediaData);
      	void* method(Media, getFormatData);
      	bool method(Media,  isLoaded);
      	errvt method(Media, forceLoad);
      	
)

Interface(MediaFormat,
	  u64  (*format)(void* result, void* metadata, MEDIA_DATA_TYPE* media_data);
	  MEDIA_DATA_TYPE* (*parse)(void* formatted_data);
	  u64 (*getAllocSize)(void* metadata, MEDIA_DATA_TYPE* media_data);
)



Type(Image,
	MEDIA_DATA_TYPE type;
)

Type(Audio,
	MEDIA_DATA_TYPE type;

)

Type(Vector,
	MEDIA_DATA_TYPE type;

)

Type(Model3D,
	MEDIA_DATA_TYPE type;

)

Type(Video,
	MEDIA_DATA_TYPE type;

)


/**
	Builtin Formats
---*/

Static(PNG,
	interface(MediaFormat);
)


Type(JPGMetaData,
	u8 compression_percentage;
)


Static(JPG,
	interface(MediaFormat);
)


void test(){
	


}
