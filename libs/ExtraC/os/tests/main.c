#include "../../../APIs/XC/os.h"

int main(int argc, char** argv){

	iferr(
	    OS.initOS((AppData){
		.domainName = "thecitronlabs.com", .appName = "ExtraC-OS-TestSuite", 
		.argv = argv

	    })
	){
		ERR(ERR_INITFAIL, "failed to initialize OS");
		return EXIT_FAILURE;
	}

	
	iferr(OS.exitOS()){
		ERR(ERR_FAIL, "failed to exit OS");
		return EXIT_FAILURE;
	}

return EXIT_SUCCESS;
}
