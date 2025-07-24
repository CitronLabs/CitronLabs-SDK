#pragma once
#include "./utils.h"
#include "./types.h"
#include "config.h"

/*----------------------\
       ERROR CODES	|
-----------------------*/

typedef enum{ 
	#define __ERROR_CODES__
	#include "config.h"
	#undef __ERROR_CODES__
}XC_ERROR_CODES;
typedef struct{	errvt val; const cstr msg; }std_err;
#define errorstuff __func__

/*----------------------\
       ERROR FUNCS	|
-----------------------*/

typedef struct String_Instance String_Instance;

#if __Debug
// utility for quickly removing debug statements
      #define debug(...) __VA_ARGS__
#else
      #define debug(...) 
#endif

Interface(Loggable,
	errvt imethod(log,, inst(String) txt);
)

Type(LogBook,
	intf(Loggable) interface;
     	inst(Object) object;
);
Enum (LogType,
	LOGGER_ERROR,
	LOGGER_INFO
)

Class(Logger,
__INIT( const cstr name;
      data(LogBook)
      * errorlog,
      * infolog
),
__FIELD(),
      	inst(Logger) std_logger;

	errvt method(Logger, logWithFormat,, LogType type, ...);
	errvt method(Logger, log,, LogType type, inst(String) txt);
)
Enum(ErrorSignal,
	SIG_FGPE = 1 , 
	SIG_ILL = 2  , 
	SIG_INT = 4  ,
	SIG_ABRT = 8 , 
	SIG_SEGV = 16
);

#define SIG_ALL (SIG_FGPE | SIG_ILL | SIG_INT | SIG_ABRT | SIG_SEGV)

Class(Error,
__INIT(errvt errorcode; cstr message;),
__FIELD(errvt errorcode; cstr message;),

	#define OK ERR_NONE

	#define ERR(code, msg) Error.Set(&(Error_Instance){NULL,&Error,code, #code}, msg, __func__)
	#define check(...) Error.Clear(); __VA_ARGS__; for(inst(Error) err = geterr(); err->errorcode != ERR_NONE; Error.Clear())
	#define nonull(var, ...) if(var == NULL){errvt nullerr = ERR(ERR_NULLPTR, #var " is null"); __VA_ARGS__;}
	#define NOT_IMPLEM(returnval) ERR(ERR_NOTIMPLEM, "not implemented yet..."); return returnval;


	#define errnm  (geterr()->errorcode)
	#define errstr (geterr()->message)
	
	#define quiet(...) Error.Hide(); __VA_ARGS__ Error.Show();

	inst(Logger) STDLOG;

	void method(Error, Print);
	errvt method(Error, Set,, const cstr errname, const char funcname[]);
      	void vmethod(Show);
      	void vmethod(Clear);
      	void vmethod(Hide);
	void vmethod(setLogger, inst(Logger) logger);
	void vmethod(setSignalHandler, u8 signals_to_handle, void fn(sighandler, ErrorSignal signal))
)

static inst(Error) core_geterr(){
	static data(Error) err;
	return &err;
}
static inst(Error)(*geterr)() = core_geterr;

