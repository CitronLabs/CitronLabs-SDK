#pragma once
#define __AUTOREBUILD_SRC_DEF__
#include "../autoRebuild.h"

static bool rebuild = false;


errvt evalautoRebuild(){

	if(rebuild){
		eb_rebuild();
	}
return NOERROR;
}

void checkautoRebuild(const char* file_path){

	fsEntry file_entry;

	std_str 
	file_path_str = String_From((char*)file_path, sizeof(fsPath)),
	time_lastmodified_str = eb_cache_search(COMPILE_CACHE, file_path_str);

	if(time_lastmodified_str.txt == NULL){
	
		println(YELLOW"autoRebuild: Registering Build-File -> "GREEN, $(file_path),NC);

		std_strbuilder* data = *_new(std_strbuilder*);


		getFileSystemEntry((char*)file_path, &file_entry);
		stringBuilderAppend(data, NULL, STR_FORMAT( 
			$(file_entry.time_modified)
		));
		std_str data_str = *stringBuilderGetStr(data);

		eb_cache_load(COMPILE_CACHE, file_path_str, data_str);
		
		_del(data);
		
		println(
			GREEN"[Registration Complete]", $(file_path), YELLOW 
	  		"\n Note: Changes made during this build may not be noted until rerun" NC);

		return;
	}

	std_timeshort time_lastmodified = {0};

	stringScan(time_lastmodified_str, STR_SCAN(
		$$(time_lastmodified)	
	));
	
	if(getFileSystemEntry((char*)file_path, &file_entry) != ERR_NONE)
		eb_cache_remove(COMPILE_CACHE, String_From((char*)file_path, sizeof(fsPath)));


	else{

		if(timeCompare(
		(std_time){.scale = TIME_SHORT, .time_short = file_entry.time_modified},
       		(std_time){.scale = TIME_SHORT, .time_short = time_lastmodified},
		NULL) != true)
	{
		rebuild = true;
		println(YELLOW"autoRebuild: Modification Detected in file -> "GREEN, $(file_path),
	  		YELLOW"\n[Rebuild Flag Set!]"NC);
		
		eb_cache_remove(COMPILE_CACHE, String_From((char*)file_path, sizeof(fsPath)));
		
		std_strbuilder* data = stringBuilderInit(NULL, UINT64_MAX);

		stringBuilderAppend(data, NULL, STR_FORMAT( 
			$(file_entry.time_modified)
		));
		std_str data_str = *stringBuilderGetStr(data);

		eb_cache_load(COMPILE_CACHE, file_path_str, data_str);
		
		_del(data);
	}}

}
