#include "./strings.h"


#define ESC_VALUE 0
#define FMT_VALUE 1

u64 formatString(FormatID* formats, va_list args, inst(StringBuilder) output){
	
	u64 actual_len = 0;

	intf(Formatter) type_formatter = va_arg(args, intf(Formatter));

	if(type_formatter == NULL){
		return UINT64_MAX;
	}
	actual_len = type_formatter->Print(va_arg(args, void*), formats, output);
	

return actual_len;
}

u64 Print_VArgs(inst(StringBuilder) builder, va_list args){
	
	bool quit = false;
	u64 len = 0;
	
	FormatID formats[FORMAT_DOMAIN_TOP + 1];
	memcpy(formats, __default_formats, FORMAT_DOMAIN_TOP + 1);

	while(!quit){
	    cstr str_arg = va_arg(args, cstr);
	    switch(addrasval(str_arg)){
	    case ESC_VALUE :{
		u64 formatted_len = formatString(
			formats,
			args,
			builder
			);
		if(formatted_len == UINT64_MAX){
			quit = true; break;
		}
		if(0 == formatted_len){ 
			ERR(STRINGERR_FORMAT, "invalid format");
	       		return 0;
		}
		
		len += formatted_len;
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
		String_Instance str = {
		.txt = str_arg,
		.len = strnlen(str_arg, UINT64_MAX)
		};
		len += StringBuilder.Append(builder, &str);
	    }
	    }
	}

return len;
}
