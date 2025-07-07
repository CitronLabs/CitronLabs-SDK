#include "error.h"

errvt methodimpl(Logger, Log,, LOG_TYPE type, inst(String) text){
	nonull(self, return nullerr);
	nonull(text, return nullerr);

	switch(type){
	case LOG_INFO:
		return priv->info == NULL ? 0 : priv->info->interface->log(priv->info->object, text);
	case LOG_ERROR:
		return priv->error == NULL ? 0 : priv->error->interface->log(priv->error->object, text);
	default:{
		ERR(ERR_INVALIDERR, "invalid log type");
		return 0;
	}
	}

return ERR(ERR_INVALIDERR, "error unreachable code");
}

errvt methodimpl(Logger, LogWithFormat,, LOG_TYPE type, ...){
	nonull(self, return nullerr);

	va_list args;
	u64 formatted_len = 0;
	va_start(args, type);

	inst(StringBuilder) textbldr = push(StringBuilder, NULL, UINT64_MAX);
	
	if(FormatUtils.FormatVArgs(textbldr, args) == 0)
		return ERR(ERR_INVALIDERR, "failed to format text for log");

	data(String) text = StringBuilder.GetStr(textbldr);

	switch(type){
	case LOG_INFO:
		formatted_len = priv->info == NULL ? 0 :
			priv->info->interface->log(priv->info->object, &text);
	case LOG_ERROR:
		formatted_len = priv->error == NULL ? 0 : 
			priv->error->interface->log(priv->error->object, &text);
	default:{
		ERR(ERR_INVALIDERR, "invalid log type");
		formatted_len = 0;
	}
	}

	va_end(args);
	pop(textbldr);

return formatted_len;
}

errvt imethodimpl(Logger, Destroy){
	self_as(Logger);
	nonull(self, return nullerr);

	del(priv->name);
return OK;
}

construct(Logger,
	.log = Logger_Log,
	.logWithFormat = Logger_LogWithFormat,
	.Object = {
		.__DESTROY = Logger_Destroy 
	}
){
	nonull(args.name, return NULL);

	priv->name = new(String, args.name, 1048);
	priv->error = args.errorlog;
	priv->info = args.infolog;	
return self;
}
