#include "./string.h"

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


u64 scanData(FORMAT_ID* formats, __Base_Type_ID__ typeid, va_list args, inst(String) input, u64 cursor){
	
	u64 actual_len = 0;
	
	intf(Formatter) type_formatter = va_arg(args, intf(Formatter));

	switch(typeid){
	case BASETYPE_POINTER :{
		FORMAT_ID temp_store = formats[NUMBERS_FORMAT];

		void** ptr_res = va_arg(args, void**);

		inst(Number) ptr_num = 	&(Number_Instance){
			.type = N_UNSIGNED, 
			.len = 3, 
			.as_u64 = 0
		};

		formats[NUMBERS_FORMAT] = NUMS_HEX;

		actual_len = Number.Formatter.Scan(generic ptr_num,
				formats,
				input
		);
		formats[NUMBERS_FORMAT] = temp_store;
		
		*ptr_res = (void*)ptr_num->as_u64;
	break;}
	case BASETYPE_BOOL :{
		if(input->txt[0] == 't' &&
     		   input->txt[1] == 'r' &&
     		   input->txt[2] == 'u' &&
     	 	   input->txt[3] == 'e' &&
     	 	   isblank(input->txt[4])
     		){
			*va_arg(args, bool*) = true;
			actual_len = sizeof("true");
		}
		else if(
		   input->txt[0] == 'f' &&
     		   input->txt[1] == 'a' &&
     		   input->txt[2] == 'l' &&
     	 	   input->txt[3] == 's' &&
     	 	   input->txt[4] == 'e' &&
     	 	   isblank(input->txt[5])
     		){
			*va_arg(args, bool*) = false;
			actual_len = sizeof("false");
		}
	break;}
	case BASETYPE_STRING :{
		cstr str_arg = *va_arg(args, cstr*);
		loop(i, input->len - cursor){
		    if(!isalnum(input->txt[i])){
			return i;
		    }
			str_arg[i] = input->txt[cursor + i];
		}	
	break;}
	case BASETYPE_CHAR :{
		*va_arg(args, cstr) = input->txt[cursor];
		return 1;
	break;}
	scan_number(BASETYPE_FLOAT,  double)
	scan_number(BASETYPE_INT,    i32)
	scan_number(BASETYPE_UINT,   u32)
	scan_number(BASETYPE_LONG ,  i64)
	scan_number(BASETYPE_ULONG,  u64)
	case BASETYPE_OBJECT:{
		if(type_formatter == NULL){
			ERR(STRINGERR_FORMAT, "cannot scan for an object without a specified formatter interface");
			return UINT64_MAX;
		}
		actual_len = type_formatter->Scan(va_arg(args, void*), formats, input);
	}
	case BASETYPE_NULL:
	default:{
		return UINT64_MAX;
	}
	}
	
return actual_len;
}



u64 Scan_VArgs(inst(String) str, va_list args){
	
	bool quit = false;
	u64 cursor = 0;
	
	FORMAT_ID formats[FORMAT_DOMAIN_TOP + 1];
	loop(i, FORMAT_DOMAIN_TOP + 1)
		formats[i] = __default_formats[i];

	while(!quit || cursor >= str->len){
	    cstr str_arg = va_arg(args, cstr);
	    switch(addrasval(str_arg)){
	    case ESC_VALUE :{
		u64 scanned_len = scanData(
			formats,
			va_arg(args, __Base_Type_ID__),
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
		enum FORMAT_ID_DOMAIN domain = va_arg(args, enum FORMAT_ID_DOMAIN);
		
		if(domain > FORMAT_DOMAIN_TOP){ 
			ERR(STRINGERR_FORMAT, "invalid format");
	       		return 0;
		}

		formats[domain] = va_arg(args, FORMAT_ID);
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
