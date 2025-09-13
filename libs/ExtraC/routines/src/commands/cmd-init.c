#include "command.h"
#include "std-data.h"
#include "std-types.h"

std_str parseCommandArgName(std_str* string){
	
	std_strbuilder* name_builder = 
		stringBuilderInit(NULL, UINT64_MAX);

	loop(i, string->len){
	    if(!isalpha(string->txt[i])){
		break;
	    }else{
		stringBuilderAppend(name_builder, &(std_str){
			.txt = &string->txt[i], .len = 1});
	    }
	}
	std_str res = stringBuilderCreateStr(name_builder);
	
	stringBuilderFree(name_builder);

return res;
}

std_data parseComandArgData(std_typeid type, std_str* string){

	std_data arg_data = {0};
    	
	if(string->txt[0] == '['){
	    if(string->txt[1] == ']'){
		arg_data.type = TYPEID_XC_LIST;
		arg_data.type_size = typeGetSize(TYPEID_XC_LIST);
		arg_data.data = listInitTyped(
				10, 
				type, 
				typeGetSize(type)
		);
	    }
	    String_CutFrnt((*string), 2);
	}else if(isalpha(string->txt[0])){
		arg_data.type = type;
		arg_data.type_size = typeGetSize(type);
		arg_data.data = memNew(typed_malloc, 1, type);
	}else{
		posterr(CMDERR_PARSE, "invalid argument type");
		return (std_data){0};
	}

return arg_data;
}
u32 parseComandArg(std_map(std_str->std_data) args, std_typeid type, std_str string){

	std_data arg_data;
	std_str arg_name;
	u64 prev_string_size = string.len;

	checkposterr((arg_data = parseComandArgData(type, &string)).data == NULL,
	      CMDERR_PARSE, "unable to parse cmd arguemnt",
	      return UINT32_MAX;)
	
	if(string.txt[0] == '('){
	    for(;;){
		checkposterr((arg_name = parseCommandArgName(&string)).txt == NULL,
		      CMDERR_PARSE, "unable to parse cmd name",
		      return UINT32_MAX;)
		mapInsert(args, arg_name, arg_data);

		if(string.txt[0] == ')') break;
	    }
	}else{
		checkposterr((arg_name = parseCommandArgName(&string)).txt == NULL,
		      CMDERR_PARSE, "unable to parse cmd name",
		      return UINT32_MAX;)
	}
return prev_string_size - string.len;
}
//ebee build =>  ; 
#define parse_errorcheck()				\
    checkposterr(current_arg.data.data == NULL,		\
	CMDERR_PARSE, "failed to parse usasge string",	\
	println("parse_error: ",current_arg.name.txt);	\
	listFree(args); return NULL;)

std_map(std_str->std_data) parseUsageString(std_queue(std_str)* var_args, std_str usage_str){
	
	std_map(std_data) args = mapInit(10, std_str,std_data);

	u32 index = 0;
	while(index < usage_str.len){
	    switch(usage_str.txt[index]){
	    case '$':{
		  index += parseComandArg(args, 
			TYPEID_XC_STRING, 
			String_CutFrntCpy(usage_str, index));
	    break;}	
	    case '!':{
		  index += parseComandArg(args, 
			TYPEID_BOOL, 
			String_CutFrntCpy(usage_str, index));
	    break;}	
	    case '#':{	
		  index += parseComandArg(args, 
			TYPEID_XC_NUMBER, 
			String_CutFrntCpy(usage_str, index));
	    break;}	
	    case '.':{
		    if(usage_str.txt[index + 1] == '.' && 
		       usage_str.txt[index + 2] == '.'){
		    	*var_args = queueInit(10, std_str);
		    }
	    break;}	
	    }
	}

return args;
}

std_cmd* cmdInit(std_str name, 
	cmd_func(command_func), 
	std_str usage, ...
){
	std_cmd* res = NULL,* sub_command = NULL;

	checkposterr((res == calloc(1, sizeof(std_cmd))), 
	      CMDERR_INIT, "could not allocate command",
	      return NULL;)
	res->name = stringCopy(name);
	res->func = command_func;
	res->args = parseUsageString(&res->var_args, usage); 
	checkposterr(res->args == NULL, 
	      CMDERR_INIT, "could not parse usage string", 
	      return NULL;)

	va_list args;
	va_start(args, usage);

	while((sub_command = va_arg(args, std_cmd*)) != NULL){
		if(res->sub_commands == NULL) 
			res->sub_commands = mapInit(10, std_str, std_cmd*);	
		mapInsert(
			res->sub_commands,
	    		sub_command->name,
	    		sub_command);
	}

return res;
}

errvt cmdFree(std_cmd* command){




return NOERROR;
}
