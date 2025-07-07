#include "../test-utils.h"



bool RUN_LOGGER_TESTS(){
	inst(File) errlog = new(File, "errlog.txt");
	inst(File) infolog = new(File, "infolog.txt");
	
	inst(Logger) logger = new(Logger, "Test-Log",
		.infolog = push(LogBook, .interface = &StringBuilder.Loggable, .object = generic infolog),
		.errorlog = push(LogBook, .interface = &File.Loggable, .object = generic errlog)
	);

return TEST_RESULT;
}
