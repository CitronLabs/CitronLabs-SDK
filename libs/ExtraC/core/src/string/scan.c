#include "./strings.h"

#define ESC_VALUE 0
#define FMT_VALUE 1

#define NUMBERS_FORMAT 0
#define STRINGS_FORMAT 1
#define scan_number(formatid, type) 				\
	case formatid :{					\
		Number_Instance res = {0};			\
		actual_len = Number.Formatter.Scan 		\
			(generic &res, formats, input);		\
		*va_arg(args, type*) = res.as_##type;		\
	break;}


u64 scanData(FormatID* formats, va_list args, inst(String) input, u64 cursor){
	
	u64 actual_len = 0;
	
	intf(Formatter) type_formatter = va_arg(args, intf(Formatter));

	if(type_formatter == NULL){
		ERR(STRINGERR_FORMAT, "cannot scan for an object without a specified formatter interface");
		return UINT64_MAX;
	}
	actual_len = type_formatter->Scan(va_arg(args, void*), formats, input);
	
return actual_len;
}



u64 Scan_VArgs(inst(String) str, va_list args){
	
	bool quit = false;
	u64 cursor = 0;
	
	FormatID formats[FORMAT_DOMAIN_TOP + 1];
	memcpy(formats, __default_formats, FORMAT_DOMAIN_TOP + 1);

	while(!quit || cursor >= str->len){
	    cstr str_arg = va_arg(args, cstr);
	    switch(addrasval(str_arg)){
	    case ESC_VALUE :{
		u64 scanned_len = scanData(
			formats,
			args,
			str,
			cursor
			);
		if(scanned_len == UINT64_MAX){
			quit = true;
			continue;
		}
		if(0 == scanned_len){ ERR( 
			STRINGERR_FORMAT, "invalid format");
	       		return 0;
		}
		cursor += scanned_len;
	    break;}
	    case FMT_VALUE :{
		Format_Domain domain = va_arg(args, Format_Domain);
		
		if(domain > FORMAT_DOMAIN_TOP){ 
			ERR(STRINGERR_FORMAT, "invalid format");
	       		return 0;
		}

		formats[domain] = va_arg(args, FormatID);
	    break;}
	    default:{
		loop(i, str->len - cursor){
		    if(!isalnum(str->txt[i])){
			cursor += i + 1;
			break;		
		    }
			str_arg[i] = str->txt[cursor + i];
			cursor++;
		}	
	    break;}
	    }
	}

return cursor;
}
