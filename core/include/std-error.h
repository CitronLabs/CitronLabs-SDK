#pragma once
#include "std-libc.h"
#include "std-utils.h"
#include "std-types.h"

#ifndef __USER_CONFIG__
#include "xc-user-config.h"
#endif

/*----------------------\
       ERROR CODES	|
-----------------------*/

typedef enum{ 
	ERR_NONE, ERR_INVALIDERR, ERR_NULLPTR, 	ERR_INITFAIL, 
	ERR_NOTIMPLEM,

	ERR_SEGFAULT, ERR_ABORT,

	DATAERR_MEMALLOC, DATAERR_SIZETOOLARGE, 	
	DATAERR_OUTOFRANGE,DATAERR_LIMIT, 		
	DATAERR_EMPTY, DATAERR_DSN,		
	
	THREADERR_DESTROY, THREADERR_RUNNING, THREADERR_MUTEX_LOCKED,	
	THREADERR_MUTEX_NOTINIT,THREADERR_SEM_FULL, 

	NETERR_SOCKBIND, NETERR_CONNSEND, NETERR_CONNRECV, NETERR_CONNECT,
	NETERR_SOCKLISTEN, NETERR_SOCKINVAL, NETERR_HOSTRESOLVE, NETERR_WATCH,	

	IOERR_PERMS, IOERR_ALRDYEXST, IOERR_NOTFOUND, IOERR_ASYNC,		
	IOERR_READ,IOERR_WRITE, IOERR_FAIL,

	MEMERR_OVERFLOW, MEMERR_INITFAIL, MEMERR_LEAK, MEMERR_INVALIDSIZE,	

	STRINGERR_REGEX,STRINGERR_FORMAT	

	#ifdef __USER_ERRORCODES__
		,__USER_ERRORCODES__
	#endif
}errvt;
typedef struct{	errvt val; const cstr msg; }std_err;
#define errorstuff __func__



/*----------------------\
       ERROR FUNCS	|
-----------------------*/

typedef struct String_Instance String_Instance;

#ifdef DEBUG
// utility for quickly removing debug statements
      #define debug(...) __VA_ARGS__
#else
      #define debug(...) 
#endif

Interface(Loggable,
	errvt imethod(log,, inst(String) text);
)

Type(LogBook,
	intf(Loggable) interface;
     	inst(Object) object;
);

typedef enum LOG_TYPE{
	LOG_ERROR,
	LOG_INFO
}LOG_TYPE;

Class(Logger,
__INIT( const cstr name;
      data(LogBook)
      * errorlog,
      * infolog
),
__FIELD(),

	errvt method(Logger, logWithFormat,, LOG_TYPE type, ...);
	errvt method(Logger, log,, LOG_TYPE type, inst(String) text);
)

Class(Error,
__INIT(errvt errorcode; cstr message;),
__FIELD(errvt errorcode; cstr message;),

	#define OK ERR_NONE

	#define ERR(code, msg) Error.Set(&(Error_Instance){NULL,&Error,code, #code}, msg, __func__)
	#define check(...) Error.Clear(); __VA_ARGS__ if(errnm != ERR_NONE)
	#define nonull(var, ...) if(var == NULL){errvt nullerr = ERR(ERR_NULLPTR, #var " is null"); __VA_ARGS__;}
	#define NOT_IMPLEM(returnval) ERR(ERR_NOTIMPLEM, "not implemented yet..."); return returnval;

	#define geterr() (Thread.GetErr(Thread.GetCurrent()))

	#define errnm  (geterr()->errorcode)
	#define errstr (geterr()->message)
	
	#define quiet(...) Error.Hide(); __VA_ARGS__ Error.Show();

	inst(Logger) STDLOG;

	void method(Error, Print);
	errvt method(Error, Set,, const char errname[], const char funcname[]);
      	void (*Show)();
      	void (*Clear)();
      	void (*Hide)();
	void (*SetLogger)(inst(Logger) logger);
)


