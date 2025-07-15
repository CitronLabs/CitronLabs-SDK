#include "../XC/core.h"

Interface(EB_Utils,
	bool 	       	vmethod(checkExtension, fsPath path, inst(String) extension);
	errvt 	       	vmethod(runShell,       inst(String) shell_cmd);
	inst(String)   	vmethod(makeUniqueName, inst(String) path);
	List(EBSource) 	vmethod(addSourceDirs,  List(String) dirs, inst(String) file_extension, bool recursive);
)
