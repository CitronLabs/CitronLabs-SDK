#pragma once
#define __LANGS_SRC_DEF__
#include "../header.h"

EBEE_SOURCE C_blueprint_linkExe(
	std_str linker,
	std_list(std_str) libs,
	std_list(std_str) files_to_link,
	std_str name
){

	dirSetCurrent("./build_files");
	if(eb_getflag(EBFL_VERBOSE))
		println(LIGHTPURPLE"--Linking executable:"NC);

	std_strbuilder* command = *_new(std_strbuilder*);
	std_str* ofiles = listGetPointer(files_to_link, 0);

	stringBuilderSet(command, STR_FORMAT(
		$(linker)," -L ../bin/libs "));

	if(libs != NULL){
		std_str* libs_strs = listGetPointer(libs, 0);
		loop(i,listSize(libs)){
			stringBuilderAppend(command, NULL, STR_FORMAT(
				"-l", $(libs_strs[i]), " "));
		}
	}

	loop(i, listSize(files_to_link)){
		if(eb_getflag(EBFL_VERBOSE))
			println("::  -->\t", $(ofiles[i].txt), ",");
		stringBuilderAppend(command, NULL, STR_FORMAT(
			$(ofiles[i].txt), " "));
	}
	stringBuilderAppend(command, NULL, STR_FORMAT(
		"-o ../bin/",$(name)));
	
	if(eb_getflag(EBFL_VERBOSE))
		print("LD");
	
	println("==>",GREEN"../bin/",$(name),NC);

	eb_shell(stringBuilderGetStr(command));	

	_del(command);
	dirSetCurrent("..");

return (EBEE_SOURCE){.src_path = name, .output_name = };
}

EBEE_SOURCE C_blueprint_linkLib(std_str archiver, std_list(std_str) files_to_link, std_str name){

	dirSetCurrent("./build_files");

	if(eb_getflag(EBFL_VERBOSE))
		println(LIGHTPURPLE"--Linking library: \n"NC);
	
	std_strbuilder* command = *_new(std_strbuilder*);
	std_str* ofiles = listGetPointer(files_to_link, 0);

	stringBuilderSet(command, STR_FORMAT(
		$(archiver)," ../bin/libs/", $(name), " "));

	loop(i, listSize(files_to_link)){
		if(eb_getflag(EBFL_VERBOSE))
			println("::\t", $(ofiles[i].txt), ",\n");
		stringBuilderAppend(command, NULL, STR_FORMAT(
			$(ofiles[i].txt), " "));
	}
	
	if(eb_getflag(EBFL_VERBOSE))
		print("AR");
	
	println("==>",GREEN"../bin/libs/",$(name),NC);

	eb_shell(stringBuilderGetStr(command));	

	_del(command);
	dirSetCurrent("..");

return NOERROR;
}
