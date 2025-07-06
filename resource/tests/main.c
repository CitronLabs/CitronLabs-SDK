#include "../include/resource.h"
#include "../include/media.h"

int main(int argc, char **argv){
	
	inst(MemoryMap) resource_map = new(MemoryMap, 
		&CMalloc.Allocator, 
		c_malloc, 
		(mmprot_info){
			.flags.direct_access = true
		}
	);

	memid overworld_scene = MemoryMap.AddNode(resource_map,	ROOT_TOKEN, NULL);

	inst(Collection) image_collection = new(Collection, resource_map, overworld_scene);

	Media_Instance
		* cat_image  = collect(image_collection, Media, "cat.png", &PNG.MediaFormat),
		* dog_image  = collect(image_collection, Media, "dog.png", &PNG.MediaFormat),
		* bird_image = collect(image_collection, Media, "bird.png", &PNG.MediaFormat)
	;

	cat_image->format = &JPG.MediaFormat;
	if(!Media.reformat(cat_image, &(data(JPGMetaData)){
		.compression_percentage = 30		
	})){
		exit(-1);
	}

	MemoryMap.CutNode(resource_map, overworld_scene);

return 0;	
}
