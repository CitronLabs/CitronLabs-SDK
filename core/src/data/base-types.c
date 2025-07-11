#include "./datastructs.h"


u64 imethodimpl(Bool, Print,, FORMAT_ID* formats, inst(StringBuilder) out){
	return StringBuilder.Append(out, 
		*(bool*)object ? 
			s("true") : s("false")
     	);
}

#define skipWS(in, num) while(isblank(in->txt[num])) num++;

/*----------------------------------------------------*/
/**
 * 	BOOL METHODS
-----
*/
u64 imethodimpl(Bool, Scan,, FORMAT_ID* formats, inst(String) in){

	u64 off = 0;

	skipWS(in, off);

	if(in->len > sizeof("true") &&
		in->txt[off + 0] == 't'   &&
		in->txt[off + 1] == 'r'   &&
		in->txt[off + 2] == 'u'   &&
		in->txt[off + 3] == 'e'
	){ *(bool*)object = true; return off; }
	else
	if(in->len > sizeof("false") &&
		in->txt[off + 0] == 'f'   &&
		in->txt[off + 1] == 'l'   &&
		in->txt[off + 2] == 'a'   &&
		in->txt[off + 3] == 's'   &&
		in->txt[off + 4] == 'e'
	){ *(bool*)object = false; return off; }

return 0;
}

u32 imethodimpl(Bool, __HASH){
	return Map.Hash(
		*(bool*)object ? 
			&(u8){1} : &(u8){0},
		sizeof(u8)
	);
}


static const BaseType_Interface Bool_Interface = {
	.Formatter = {
		.Scan = Bool_Scan,
		.Print = Bool_Print
	},
	.Object = {.__HASH = Bool___HASH } 
};

/*----------------------------------------------------*/
/**
 * 	ULONG METHODS
-----
*/

u64 imethodimpl(ULong, Print,, FORMAT_ID* formats, inst(StringBuilder) out){
	char buff[20] = {0};

	u64 print_len = snprintf(buff, 20, "%lu", *(u64*)object);
	StringBuilder.Append(out, str_cast(buff, print_len));

return print_len;
}
u64 imethodimpl(ULong, Scan,, FORMAT_ID* formats, inst(String) in){
	Number_Instance res = {0};			
	u64 actual_len = Number.Formatter.Scan 	
		(generic &res, formats, in);			
	*(u64*)object = res.as_u64;		
return actual_len;
}

static const BaseType_Interface ULong_Interface = {
	.Formatter = {
		.Scan = ULong_Scan,
		.Print = ULong_Print
	}
};

/*----------------------------------------------------*/
/**
 * 	LONG METHODS
-----
*/

u64 imethodimpl(Long, Print,, FORMAT_ID* formats, inst(StringBuilder) out){
	char buff[20] = {0};

	u64 print_len = snprintf(buff, 20, "%li", *(i64*)object);
	StringBuilder.Append(out, str_cast(buff, print_len));

return print_len;	
}

u64 imethodimpl(Long, Scan,, FORMAT_ID* formats, inst(String) in){
	Number_Instance res = {0};			
	u64 actual_len = Number.Formatter.Scan 	
		(generic &res, formats, in);			
	*(i64*)object = res.as_i64;		
return actual_len;
}

static const BaseType_Interface Long_Interface = {
	.Formatter = {
		.Scan = Long_Scan,
		.Print = Long_Print
	},
};

/*----------------------------------------------------*/
/**
 * 	UINT METHODS
-----
*/

u64 imethodimpl(UInt, Print,, FORMAT_ID* formats, inst(StringBuilder) out){
	char buff[20] = {0};

	u64 print_len = snprintf(buff, 20, "%u", *(u32*)object);
	StringBuilder.Append(out, str_cast(buff, print_len));

return print_len;	
}

u64 imethodimpl(UInt, Scan,, FORMAT_ID* formats, inst(String) in){
	Number_Instance res = {0};			
	u64 actual_len = Number.Formatter.Scan 	
		(generic &res, formats, in);			
	*(u32*)object = res.as_u32;		
return actual_len;
}
static const BaseType_Interface UInt_Interface = {
	.Formatter = {
		.Scan = UInt_Scan,
		.Print = UInt_Print
	},
};
/*----------------------------------------------------*/
/**
 * 	INT METHODS
-----
*/

u64 imethodimpl(Int, Print,, FORMAT_ID* formats, inst(StringBuilder) out){
	char buff[20] = {0};

	u64 print_len = snprintf(buff, 20, "%i", *(i32*)object);
	StringBuilder.Append(out, str_cast(buff, print_len));

return print_len;	
}
u64 imethodimpl(Int, Scan,, FORMAT_ID* formats, inst(String) in){
	Number_Instance res = {0};			
	u64 actual_len = Number.Formatter.Scan 	
		(generic &res, formats, in);			
	*(i32*)object = res.as_i32;		
return actual_len;
}

static const BaseType_Interface Int_Interface = {
	.Formatter = {
		.Scan = Int_Scan,
		.Print = Int_Print
	},
};
/*----------------------------------------------------*/
/**
 * 	POINTER METHODS
-----
*/

u64 imethodimpl(Pointer, Print,, FORMAT_ID* formats, inst(StringBuilder) out){
	char buff[20] = {0};

	u64 print_len = snprintf(buff, 20, "%p", *(void**)object);
	StringBuilder.Append(out, str_cast(buff, print_len));

return print_len;	
}

u64 imethodimpl(Pointer, Scan,, FORMAT_ID* formats, inst(String) in){
	Number_Instance res = {0};			
	u64 actual_len = Number.Formatter.Scan 	
		(generic &res, formats, in);			
	*(void**)object = (void*)res.as_u64;		
return actual_len;
}

static const BaseType_Interface Pointer_Interface = {
	.Formatter = {
		.Scan = Pointer_Scan,
		.Print = Pointer_Print
	},
};

/*----------------------------------------------------*/
/**
 * 	FLOAT METHODS
-----
*/
u64 imethodimpl(Float, Print,, FORMAT_ID* formats, inst(StringBuilder) out){
	char buff[20] = {0};

	u64 print_len = snprintf(buff, 20, "%f", *(double*)object);
	StringBuilder.Append(out, str_cast(buff, print_len));

return print_len;	
}

u64 imethodimpl(Float, Scan,, FORMAT_ID* formats, inst(String) in){
	Number_Instance res = {0};			
	u64 actual_len = Number.Formatter.Scan 	
		(generic &res, formats, in);			
	*(double*)object = res.as_double;		
return actual_len;
}

static const BaseType_Interface Float_Interface = {
	.Formatter = {
		.Scan = Float_Scan,
		.Print = Float_Print
	},
};

/*----------------------------------------------------*/
/**
 * 	CSTRING METHODS
-----
*/
u64 imethodimpl(CString, Print,, FORMAT_ID* formats, inst(StringBuilder) out){
	char* string_ptr = *(char**)object;
	inst(String) string = str_cast(string_ptr, UINT64_MAX);
	u64 actual_len = 0;
	if(formats[FORMAT_DATA] == DATA_DSN){
		actual_len += StringBuilder.Append(out, s("\""));
		actual_len += StringBuilder.Append(out, string);
		actual_len += StringBuilder.Append(out, s("\""));
	}else
		actual_len = StringBuilder.Append(out, string);
return actual_len;
}

u64 imethodimpl(CString, Scan,, FORMAT_ID* formats, inst(String) in){
	char* str_arg = *(char**)object;
	u64 cursor = 0;
	loop(i, in->len){
	    if(!isalnum(in->txt[i])){
		return i;
	    }
		str_arg[i] = in->txt[i];
		if(i + 1 >= in->len)
	  		cursor = i;
	}

return cursor;
}
static const BaseType_Interface CString_Interface = {
	.Formatter = {
		.Scan = CString_Scan,
		.Print = CString_Print
	},
};
/*----------------------------------------------------*/
/**
 * 	CHAR METHODS
-----
*/
u64 imethodimpl(Char, Print,, FORMAT_ID* formats, inst(StringBuilder) out){
	u64 actual_len = 1;
	char buff[4] = {0};
	if(formats[FORMAT_STRINGS] == STRING_NUM)
	    actual_len = Number.Formatter.Print(
			generic &(Number_Instance){
				.type = N_UNSIGNED,
				.len = 0,
				.as_u8 = *(char*)object,
			},
			formats, out
		);
	else if(formats[FORMAT_DATA] == DATA_DSN){
	    buff[0] = '\'';
	    buff[1] = *(char*)object;
	    buff[2] = '\'';
	    actual_len += 2;
	}else
	    buff[0] = *(char*)object;

return actual_len;
}
u64 imethodimpl(Char, Scan,, FORMAT_ID* formats, inst(String) in){
	*(char*)object = in->txt[0];
	return 1;
}

static const BaseType_Interface Char_Interface = {
	.Formatter = {
		.Scan = Char_Scan,
		.Print = Char_Print
	},
};

private(BaseType);
construct(BaseType){

	if(args.ID == BASETYPE_OBJECT || args.ID == BASETYPE_NULL)
		return NULL;

	self->ID = args.ID;
	self->data = self->data;

	switch(args.ID){
	case BASETYPE_BOOL:
		self->__methods = &Bool_Interface;
	break;
	case BASETYPE_ULONG:
		self->__methods = &ULong_Interface;
	break;
	case BASETYPE_LONG:
		self->__methods = &Long_Interface;
	break;
	case BASETYPE_UINT:
		self->__methods = &UInt_Interface;
	break;
	case BASETYPE_INT:
		self->__methods = &Int_Interface;
	break;
	case BASETYPE_POINTER:
		self->__methods = &Pointer_Interface;
	break;
	case BASETYPE_FLOAT:
		self->__methods = &Float_Interface;
	break;
	case BASETYPE_STRING:
		self->__methods = &CString_Interface;
	break;
	case BASETYPE_CHAR:
		self->__methods = &Char_Interface;
	break;
	default:{
		return NULL;
	}
	}

return self;
}
