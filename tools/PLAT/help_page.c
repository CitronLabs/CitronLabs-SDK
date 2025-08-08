
void __HELP_PAGE(){
	
	println(WHITE"\tPLAT - "BLUE"(P)rograms, "LIGHTPURPLE"(L)ibaries"LIGHTRED", (A)nd"YELLOW" (T)ools "WHITE"Packaging DevTool");
	println("Usage:\n\t plat [FLAGS] [COMMAND] [ARGS...] -- [NEXT COMMAND]"NC);
	println("\n");
	println(WHITE"\tCommands"NC);
	println("---------------------------------");
	println(WHITE"   pack "NC"\t[packages up directories and files into a .plat file]\n");

	println(WHITE"   unpack"NC"\t[unpacks a .plat file into a directory with all of its contents]\n");

	println(WHITE"   install"NC"\t[installs the .plat file with accordance to its __plat_install file]\n");

	println(WHITE"   uninstall"NC"\t[uninstalls a previous .plat file installed with the 'install' command]\n");

	println(WHITE"   upgrade"NC"\t[upgrades a currently installed .plat file with a new one specified as a arguement]\n");
	
	println(WHITE"   list "NC"\t[lists all currently installed .plat files along with information about the install]\n");
	println("\n");

	println(WHITE"\tFlags"NC);
	println("----------------------------------");
	
	println("-v, --verbose   [annouces all log information through stdout]\n");
	
}
