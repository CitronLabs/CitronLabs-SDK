#include "../test-utils.h"
#include "stringutils.h"
#include "types.h"



bool RUN_LOGGER_TESTS(){
	data(StringBuilder)
		* errlog  = push(StringBuilder),
	 	* infolog = push(StringBuilder);
	
	inst(Logger) logger = push(Logger, "Test-Log",
		.infolog = push(LogBook, .interface = &StringBuilder.Loggable, .object = generic infolog),
		.errorlog = push(LogBook, .interface = &StringBuilder.Loggable, .object = generic errlog)
	);

	pop(logger);
	pop(errlog);
	pop(infolog);

return TEST_RESULT;
}
