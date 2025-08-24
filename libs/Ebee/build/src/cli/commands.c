#pragma once
#define __EBEE_SRC_DEF__
#include "../ebee-data.h"

errvt EB_addProject(intf(Project) project){
	
	nonull(project, return nullerr);
	
	inst(String) name = new(String, (char*)project->name, 255);

	if(Map.Insert(__eb_data->__private->targets, name, project) == UINT32_MAX)
		return ERR(BUILDERR_TARGETS, "could not add new target");
	

return OK;
}
errvt EB_addCommand(const char* name, void(*command)){

	nonull(command, return nullerr);
	nonull(name, return nullerr);

	inst(Command) new_command = new(Command, 
      	
	);

	if(Command.AddSubCommand(
		__eb_data->__private->commands,
		new_command
	) != ERR_NONE)
		return ERR(BUILDERR_TARGETS, "could not add new command");

return OK;
}

cmd_func(__BUILD_COMMAND){

	List(inst(String)) targets = ((DSN_data*)List.GetPointer(args, 0))->data;
	List(intf(Project)) projects = pushList(intf(Project), 10);
	
	errvt status = ERR_NONE;

	ListForEach(projects, inst(String), target){
	    intf(Project) project = 
		Map.Search(__eb_data->__private->targets, target);
	
	    if(project == NULL){
		fprint(File.err, "Unknown Target: ", $O(target));
		status = BUILDERR_TARGETS;
	    }
	}

	if(status != ERR_NONE){
		pop(projects);
		return status;
	}

	ListForEach(projects, intf(Project), project){
		if(project->build(project)){
			ERR(BUILDERR_TARGETS, "a target has failed to build");
		}
	}

return OK;
}

void readCMDArgs(int argc, char** argv){
	
	u32 first_nonflag_arg = 1;

	__eb_data->__private->commands = new(Command, 
	.sub_commands = l(
		new(Command, "build", __BUILD_COMMAND, "$[]project"),
		)
	);
	
	Command.GetArgsFromArgv(__eb_data->__private->commands, argv);
	Command.Parse(__eb_data->__private->commands);

}
