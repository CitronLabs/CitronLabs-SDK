#include "../../include/std-all.h"

private(Logger,
	inst(String) name;
	data(LogBook) 
		* error,
		* info;
)

static bool showErrors = true;


static errvt imethodimpl(STD_LOG, Log,, inst(String) text){
	nonull(text, return nullerr);
	fprint(File.err, $(text));
return OK;
}

Static(STD_LOG,
	interface(Loggable);
)Impl(STD_LOG){
	.Loggable = {.log = STD_LOG_Log}
};


static const data(Logger) std_logger = {
	.__init = true,
	.__methods = &Logger,
	.__private = &(Logger_Private){
		.name = &(data(String)){
			.__private = NULL,
			.__methods = &String,
			.__init = true,
			.txt = "LOG",
			.len = sizeof("LOG") - 1,
			.type = CT_ASCI
		},
		.info = &(data(LogBook)){
			.object = NULL,
			.interface = &STD_LOG.Loggable
		},
		.error = &(data(LogBook)){
			.object = NULL,
			.interface = &STD_LOG.Loggable
		}
	}
};

static inst(Logger) error_logger = (inst(Logger))&std_logger;
