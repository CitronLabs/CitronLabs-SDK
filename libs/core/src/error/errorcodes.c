#include "error.h"


errvt methodimpl(Error, Set,, const cstr errmsg, const char funcname[]){

	inst(Error) curr_err = geterr();
	u8 count = 0;
	
	curr_err->message = errmsg == NULL ? self->message : errmsg;
	curr_err->errorcode = self->errorcode;
	
	if(showErrors && self->errorcode != ERR_NONE){
		fprintf(stderr,
		 RED"[ERROR] %s\n"NC"In the function: %s\nerrormsg: %s\n\n",self->message, funcname, curr_err->message);
	}

return self->errorcode;
}

void methodimpl(Error, Print){

	fprintf(stderr,
	 RED"[ERROR] %s\n",self->message);

return;
}
void Error_Hide(){
	showErrors = false;
}


extern inst(Logger) error_logger;

void Error_SetLogger(inst(Logger) logger){
	nonull(logger, return);
	error_logger = logger;
}

void Error_Show(){
	showErrors = true;
}

void Error_Clear(){
	inst(Error) curr_err = geterr();
	curr_err->errorcode = 0;
	curr_err->message = "No Error";
}

private(Error);
construct(Error,
	.Set = Error_Set,
	.Print = Error_Print,
	.Show = Error_Show,
	.Hide = Error_Hide,
	.Clear = Error_Clear,
	.setLogger = Error_SetLogger,
){
	self->errorcode = args.errorcode;
	self->message = args.message;
	
return self;
}
