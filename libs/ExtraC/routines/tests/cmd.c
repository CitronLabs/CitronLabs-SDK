#include "../include/commands.h"


//ebee build extrac -j 12 --run

__start{

	inlineCMD(ebee){
		
	}

	inlineCMD(build){
		
	}
	
	inlineCMD(info){
		
	}
	
	inlineCMD(test){
		
	}

	inst(Command) ebee_commands = 
	newCommand(ebee, NULL,,
	    newList(Command,
	    	newCommand(build, "#j, !(v, run), ...")
	    )
	);
	
	
	Command.GetArgsFromArgv(ebee_commands, argv);
	Command.Parse(ebee_commands);

return 0;
}
