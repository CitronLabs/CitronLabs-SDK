#include "error.h"

private(Error,
	Buffer(errvt) errors_to_catch;
	jmp_buf try_throw_jumppoint;
	u8 trying : 1;
);

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

noFail methodimpl(Error, Print){

	fprintf(stderr,
	 RED"[ERROR] %s\n",self->message);

return;
}
noFail Error_Hide(){
	showErrors = false;
}


extern inst(Logger) error_logger;

errvt Error_SetLogger(inst(Logger) logger){
	nonull(logger, return err);
	error_logger = logger;
return OK;
}

noFail Error_Show(){
	showErrors = true;
}

noFail Error_Clear(){
	inst(Error) curr_err = geterr();
	curr_err->errorcode = 0;
	curr_err->message = "No Error";
	if(curr_err->__private->trying) {
		curr_err->__private->trying = false;
		curr_err->__private->try_throw_jumppoint[0] = (typeof(*(jmp_buf){0})){0};
	}
}

errvt Error_Try(errvt* errors_to_catch, size_t num){
	inst(Error) curr_err = geterr(); 

	if(setjmp(curr_err->__private->try_throw_jumppoint)){
		curr_err->__private->trying = false;
		return curr_err->errorcode;
	}
	curr_err->__private->errors_to_catch = 
			new(Buffer, 
				.initData = errors_to_catch, 
				.size = num, 
				.typeSize = sizeof(errvt)
			);

	curr_err->__private->trying = true;

return OK;
}

void Error_Throw(){
	inst(Error) curr_err = geterr(); 
	
	if(curr_err->__private->trying)
		longjmp(curr_err->__private->try_throw_jumppoint, 1);
}

construct(Error,
	.Set = Error_Set,
	.Print = Error_Print,
	.Show = Error_Show,
	.Hide = Error_Hide,
	.Try = Error_Try,
	.Throw = Error_Throw,
	.Clear = Error_Clear,
	.setLogger = Error_SetLogger,
){
	self->errorcode = args.errorcode;
	self->message = args.message;
	
return self;
}
