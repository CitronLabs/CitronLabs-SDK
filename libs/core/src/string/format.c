#include "./string.h"


#define ESC_VALUE 0
#define FMT_VALUE 1

#define format_number(formatid, num_type, num_len, _type) 	\
	case formatid :{					\
		Number_Instance res = {				\
			.type = num_type,			\
			.len = num_len,				\
			.as_##_type = va_arg(args, _type)	\
		};						\
		actual_len = Number.Formatter.Print 		\
			(generic &res, formats, output);	\
	break;}

u64 formatString(FORMAT_ID formats[FORMAT_DOMAIN_TOP], __Base_Type_ID__ typeid, va_list args, inst(StringBuilder) output){
	
	u64 actual_len = 0;

	intf(Formatter) type_formatter = va_arg(args, intf(Formatter));

	switch(typeid){
	case BASETYPE_POINTER :{
		char buff[21];
		actual_len = snprintf(buff, 20, "%p", va_arg(args, void*));
		buff[actual_len] = '\0';
		StringBuilder.Append(output, pushString(buff, actual_len));
	break;}
	case BASETYPE_BOOL :{
		if(va_arg(args, int))
			StringBuilder.Append(output, s("true"));
		else 
			StringBuilder.Append(output, s("false"));
	break;}
	case BASETYPE_STRING :{
		cstr string_ptr = va_arg(args, cstr);
		inst(String) string = str_cast(string_ptr, UINT64_MAX);
		if(formats[FORMAT_DATA] == DATA_DSN){
			actual_len += StringBuilder.Append(output, s("\""));
			actual_len += StringBuilder.Append(output, string);
			actual_len += StringBuilder.Append(output, s("\""));
		}else
			actual_len = StringBuilder.Append(output, string);
	break;}
	case BASETYPE_CHAR :{
		char buff[3];
		if(formats[FORMAT_STRINGS] == STRING_NUM)
		    actual_len = Number.Formatter.Print(
				generic &(Number_Instance){
					.type = N_UNSIGNED,
					.len = 0,
					.as_u8 = va_arg(args, int),
				},
				formats, output
			);
		else if(formats[FORMAT_DATA] == DATA_DSN){
		    buff[0] = '\'';
		    buff[1] = va_arg(args, int);
		    buff[2] = '\'';
		    actual_len += 2;
		    actual_len = StringBuilder.Append(output, pushString(buff, 3));
		}else{
		    buff[0] = va_arg(args, int);
		    actual_len = StringBuilder.Append(output, pushString(buff, 1));
		}
	break;}
	case BASETYPE_FLOAT:{
		    actual_len = Number.Formatter.Print(
				generic &(Number_Instance){
					.type = N_FLOATING,
					.len = 3,
					.as_u8 = va_arg(args, double),
				},
				formats, output 
			);
	break;};
	format_number(BASETYPE_INT, N_SIGNED, 2, i32);
	format_number(BASETYPE_UINT, N_UNSIGNED, 2, u32);
	format_number(BASETYPE_LONG, N_SIGNED, 3, i64);
	format_number(BASETYPE_ULONG, N_UNSIGNED, 3, u64);
	case BASETYPE_OBJECT:{
		if(type_formatter == NULL){
			ERR(STRINGERR_FORMAT, "cannot format an object without a specified formatter interface");
			return UINT64_MAX;
		}
		actual_len = type_formatter->Print(va_arg(args, void*), formats, output);
	break;}
	case BASETYPE_NULL:
	default:{
		return UINT64_MAX;
	}
	}
	

return actual_len;
}

u64 Print_VArgs(inst(StringBuilder) builder, va_list args){
	
	bool quit = false;
	u64 len = 0;
	
	FORMAT_ID formats[FORMAT_DOMAIN_TOP + 1];
	loop(i, FORMAT_DOMAIN_TOP + 1)
		formats[i] = __default_formats[i];

	while(!quit){
	    cstr str_arg = va_arg(args, cstr);
	    switch(addrasval(str_arg)){
	    case ESC_VALUE :{
		u64 formatted_len = formatString(
			formats,
			va_arg(args, __Base_Type_ID__),
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
		enum FORMAT_ID_DOMAIN domain = va_arg(args, enum FORMAT_ID_DOMAIN);
		
		if(domain > FORMAT_DOMAIN_TOP){ 
			ERR(STRINGERR_FORMAT, "invalid format");
	       		return 0;
		}

		formats[domain] = va_arg(args, FORMAT_ID);
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
