#pragma once
#define __EBEE_SRC_DEF__
#include "../ebee-data.h"
#include <unistd.h>

bool checkExtension(fsPath path, inst(String) extension){

	inst(String) path_str = pathtostr(path);
	u32 extension_start = path_str->len;
	
	loop(i, path_str->len){
		if(path_str->txt[path_str->len - i] == '.')
			{ break;}
		extension_start--;
	}
	return strncmp(&path_str->txt[extension_start + 1], extension->txt, extension->len) == 0;
}
void eb_rebuild(){		

	if(system("ebee init") != 0){
		println(RED "rebuild failed..." NC);
		exit(0);
	}

	EB.rerun();
}

inst(String) makeUniqueName(inst(String) path){

	nonull(path, return NULL)

	u32 cut_front = 0;
	u32 cut_back = 0;

	for(int i = 0; i < path->len; i++)
	   if(path->txt[path->len - i - 1] == '.')
		{cut_back = path->len - i - 1; break;}
	
	if(cut_back == 0){
		ERR(BUILDERR_UTILS, "could not create unique name");
		println("failed path: ", $O(path));
		return NULL;
	}
	
	for(int i = cut_back; i < path->len; i++)
	   if(path->txt[path->len - i - 1] == '/')
		{cut_front = path->len - i - 1; break;}
		

	inst(String) file_name = str_cutfcpy(str_cutbcpy(path, cut_back), cut_front);

	inst(StringBuilder) output_name = push(StringBuilder, NULL, 100);

	u32 hashed_srcpath = Map.Hash(path->txt, path->len);

	StringBuilder.Set(output_name,
	F(NUMS,HEX, $(hashed_srcpath)),"_", $O(file_name), endstr);

	inst(String) result = StringBuilder.CreateStr(output_name);
	
	pop(output_name);

return result;
}


void EB_rerun(){
	del(__eb_data);

	execv("./eb", __eb_data->__private->argv);

	exit(0);
}
bool EB_getFlag(enum EB_FLAGS flag){

	switch (flag) {
	case EBFL_VERBOSE: {return __eb_data->__private->verbose;}
	}
return false;
}
