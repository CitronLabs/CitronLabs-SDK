#include "command.h"
#include "std-data.h"
#include "std-error.h"
#include "std-types.h"
#include "stdext-string.h"

u32 parseSubCommands(std_cmd **command, std_str *args){

	u32 arg_index = 0;

	while(args[arg_index].txt != NULL){
	    	
		u32 mindex = mapSearch(
	    		(*command)->sub_commands, 
	    		args[arg_index]);
		
		if(mindex != UINT32_MAX){
	    		mapIndex((*command)->sub_commands,
				mindex,
				command);
		}else if(arg_index == 0){
			posterr(CMDERR_PARSE, "unknown sub-command")
		   	return UINT32_MAX;
		}else
			break;
	    arg_index++;
	}
return arg_index;
}

errvt parseArgAndData(std_cmd *command, std_str arg, std_str data){

	std_data arg_data = {0};
	u32 mindex = UINT32_MAX;

	checkposterr((mindex = 
	    mapSearch(
	 	command->args, 
	 	(String_CutFrntCpy(arg, 1)))	
	   ) == UINT32_MAX,
	
		CMDERR_PARSE, "unknown arguement",
		println("ERROR:", $(arg.txt));
	return UINT32_MAX;
	);

	mapIndex(command->args, mindex, &arg_data);
	
	switch(arg_data.type){
	case TYPEID_XC_STRING:{
	break;}
	case TYPEID_XC_NUMBER:{
	break;}
	case TYPEID_XC_LIST:{
	break;}
	default:{
		return posterr(
			CMDERR_CALL, "critical error invalid arg type");
	break;}
	}
return NOERROR;
}

u32 parseArgs(std_cmd *command, std_str *args){

	u32 arg_index = 0;

	while(args[arg_index].txt != NULL){
	    switch(args[arg_index].txt[0]){
	    case '-': {
		checkposterr(parseArgAndData(command, 
			       args[arg_index], 
			       args[arg_index + 1]),

	       	    CMDERR_PARSE, "failed to parse arguement"
	       	);
	    break;}
	    default:{
		if(command->var_args != NULL){
			queueWrite(
				command->var_args, 
				&args[arg_index], 
				1
			);
		}
	    }
	    }
	}

return arg_index;
}

errvt cmdCall(std_cmd *command){

	checkreturnerr(command->func == NULL, 
		CMDERR_CALL, "no function specified for this command")

	std_list 
	* arg_entries = mapGetEntries(command->args),
	* args_list = listInit(listSize(arg_entries), std_data);

	listForEach(arg_entries, data_entry, ent_bucket){
		listAppend(args_list, ent_bucket.data);
	}
	
	std_struct args_struct = listGetPointer(args_list, 0);
	
	command->func(args_struct);

	listForEach(args_list, std_data, arg_data){
		switch(arg_data.type){
		case TYPEID_XC_STRING:{
			stringFree(*(std_str*)arg_data.data);
		break;}
		case TYPEID_XC_NUMBER:{
			((std_num*)arg_data.data)->as_u64 = 0;
		break;}
		case TYPEID_XC_LIST:{
			listFlush(arg_data.data);
		break;}
		default:{
			return posterr(
				CMDERR_CALL, "critical error invalid arg type");
		break;}
		}
	}

return NOERROR;
}

errvt cmdParse(std_cmd *command, std_str *args){

	u32 arg_index = 0;
	std_cmd *current_command = command;

	// top level loop
	for(;;){
		// parsing sub commands
		arg_index += parseSubCommands(&current_command, &args[arg_index]);
		
		checkreturnerr(arg_index == UINT32_MAX,
			CMDERR_CALL, "command parse failed"
		)
	
		arg_index += parseArgs(current_command, &args[arg_index]);
		// parsing command arguements
		
		checkreturnerr(arg_index == UINT32_MAX,
			CMDERR_CALL, "command parse failed"
		)

		checkreturnerr(cmdCall(current_command),
			CMDERR_CALL, "command call failed"
		)

		checkreturnerr(args[arg_index].txt != NULL && 
		    	       stringCompare(args[arg_index], s(";")),
			CMDERR_PARSE, "unexpected token after command",
			println("ERROR:", $(args[arg_index].txt));
		 )
	
		if(args[arg_index].txt[0] == ';') 
		    {arg_index++; current_command = command;}
		else
			if(args[arg_index].txt == NULL) break;
	}

return NOERROR;
}



