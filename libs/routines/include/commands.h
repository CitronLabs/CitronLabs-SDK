#pragma once
#include "../../core/include/std-all.h"
#include "./routines.h"

#define CMDTOOLS_ERRORCODES 	\ 
	CMDERR_INIT,		\
	CMDERR_PARSE,		\
	CMDERR_CALL




#define inlineCMD(name) subroutine(name,	\
     List(DSN_data) name##_args;		\
     List(String) name##_var_args;)

#define CMD(name)



#define newCommand(routine, usage, ...) new(Command, 				\
	#routine, &routine->__methods->Routine, routine, usage __VA_ARGS__),	\

#define subcmds(...) , newList(Command, __VA_ARGS__)

Class(Command,
__INIT(
      char* name;
      intf(Routine) command_routine; void* command_instance;
      char* usage;
      List(Command) sub_commands
),
__FIELD(inst(String) args; intf(Routine) command_routine; void* command_instance;),

      	interface(Routine);
	
	errvt method(Command, Parse);
      	errvt method(Command, AddSubCommand,, inst(Command) sub_command);
	errvt method(Command, GetArgsFromFile,, inst(File) file);
	errvt method(Command, GetArgsFromArgv,, char** argv);
)
