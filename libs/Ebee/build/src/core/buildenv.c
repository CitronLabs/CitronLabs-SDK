#pragma once
#define __EBEE_SRC_DEF__
#include "../../include/ebee-data.h"

inst(Dir) createBuildFilesDirectory(){
	inst(Dir) res = NULL, * temp = NULL;

		if((res = Dir.Create("./build_files", 0)) == NULL){
	       		ERR(BUILDERR_BUILDENV, "could not create build_files directory");
			return NULL;
		}
		if((temp = Dir.Create("./build_files/out_files", 0)) == NULL){ 
	       		ERR(BUILDERR_BUILDENV, "could not create out_files directory");
			del(res);
			return NULL;
		}
		del(temp);

		if((temp = Dir.Create("./build_files/external", 0)) == NULL){ 
	       		ERR(BUILDERR_BUILDENV, "could not create external directory");
			del(res);
			return NULL;
		}
return res;
}

inst(Dir) createBinarysDirectory(){
	inst(Dir) res = NULL, * temp = NULL;

		if((res = Dir.Create("./bin", 0)) == NULL){
	       		ERR(BUILDERR_BUILDENV, "could not create build_files directory");
			return NULL;
		}
		if((temp = Dir.Create("./bin/libs", 0)) == NULL){ 
	       		ERR(BUILDERR_BUILDENV, "could not create out_files directory");
			del(res);
			return NULL;
		}
		del(temp);

return res;
}

errvt checkMissingBuildFiles(){

	inst(Dir)*
	curr_dir = &__eb_data->__private->build_dirs[BUILD_FILES];

	if((*curr_dir = new(Dir, "./build_files", 0)) == NULL){
		*curr_dir = createBuildFilesDirectory();
		if(*curr_dir == NULL)
	  	     return ERR(BUILDERR_BUILDENV, "could not get build_files directory");
	}
	if(FileSys.search("./build_files/out_files", 0) != ERR_NONE ){
		return ERR(BUILDERR_BUILDENV, "could not find out_files directory");
	}
	if(FileSys.search("./build_files/external", 0) != ERR_NONE ){
	       return ERR(BUILDERR_BUILDENV, "could not find externals directory");
	}

	curr_dir = &__eb_data->__private->build_dirs[BINARY_OUT];
	
	if((*curr_dir = new(Dir, "./bin", 0)) == NULL){
		*curr_dir = createBinarysDirectory();
		if(*curr_dir == NULL)
	  	     return ERR(BUILDERR_BUILDENV, "could not get build_files directory");
	}
	
	if(FileSys.search("./bin/libs", 0) != ERR_NONE ){
	       return ERR(BUILDERR_BUILDENV, "could not create binary libraries directory");
	}

return OK;	
}

void fetchBuildData(){
	inst(File)*
	curr_file = &__eb_data->__private->build_files[BUILD_DATA];
	
	if((*curr_file = new(File, "./build_files/build.dsn", sizeof(char), FFL_READ)) == NULL){
		*curr_file = File.Create("./build_files/build.dsn", sizeof(char), FFL_WRITE);
	}else{
		fscan(*curr_file, $(__eb_data->__private->caches[COMPILE_CACHE]));

		File.Remove(*curr_file);
		__eb_data->__private->build_files[BUILD_DATA] = 
			File.Create(
				"./build_files/build.dsn",
				sizeof(char),
				FFL_WRITE
			);
	}
	
	curr_file = &__eb_data->__private->build_files[DEPENDENCY_DATA];

	if((*curr_file = new(File, "./build_files/external.dsn", sizeof(char), FFL_READ)) == NULL){
		*curr_file = File.Create("./build_files/external.dsn", sizeof(char), FFL_WRITE);
	}

}

void initStructures(){
	__eb_data->__private->targets = newMap(String, Project);

	__eb_data->__private->caches[COMPILE_CACHE] = newMap(String, fsPath);
}

void exitStructures(){
	
	inst(Map) selectmap = __eb_data->__private->caches[COMPILE_CACHE];

	fprint(__eb_data->__private->build_files[BUILD_DATA],
		$(selectmap)
	);

	del(__eb_data->__private->targets);
	del(__eb_data->__private->caches[COMPILE_CACHE]);
}

errvt establishBuildEnvironment(){

	initStructures();
	checkMissingBuildFiles();
	fetchBuildData();

return OK;
}
