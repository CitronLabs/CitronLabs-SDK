#include "./datastructs.h"
#include <alloca.h>
#include <float.h>
#include <stdint.h>
#include <stdio.h>

#define skipWS(in, num) while(isblank(in->txt[num])) num++;


/*----------------------------------------------------
	BOOL METHODS
-----*/

u64 imethodimpl(Boolean, Print,, FormatID* formats, inst(StringBuilder) out){
	return StringBuilder.Append(out, 
		*(bool*)object ? 
			s("true") : s("false")
     	);
}

u64 imethodimpl(Boolean, Scan,, FormatID* formats, inst(String) in){

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

u32 imethodimpl(Boolean, __HASH){
	return Map.Hash(
		*(bool*)object ? 
			&(u8){1} : &(u8){0},
		sizeof(u8)
	);
}


Impl(Boolean){
	.Formatter = {
		.Scan 	= Boolean_Scan,
		.Print 	= Boolean_Print
	},
	.__HASH = Boolean___HASH 
};

/*------------------------------|
  	   INT METHODS		|
------------------------------*/

u64 imethodimpl(Integer, Print,, FormatID* formats, inst(StringBuilder) out){
	self(Integer);
	char buff[22] = {0};
	u64 formatted_len = 0;

	if(self->longint){
		if(self->sign)
			formatted_len = snprintf(buff, 22, "%li", self->asType.i64);
		else
			formatted_len = snprintf(buff, 22, "%lu", self->asType.u64);
	}else{
		if(self->sign)
			formatted_len = snprintf(buff, 22, "%i", self->asType.i32);
		else
			formatted_len = snprintf(buff, 22, "%u", self->asType.u32);
	}

	if(formatted_len != 0)
		StringBuilder.Append(out, &(data(String)){
			.txt = buff,
			.len = formatted_len
		});

return formatted_len;
}

u64 imethodimpl(Integer, Scan,, FormatID* formats, inst(String) in){
	self(Integer);
	
	if(in->txt[in->len + 1] != '\0') {
		ERR(ERR_INVALID, "in order to properly scan a string for an integer the string must be null terminated");
		return 0;
	}
	u64 numBuff = 0, scannedLen = 0, scanned = 0; 

	if(self->longint){
		if(self->sign)
			scanned = sscanf(in->txt, "%li%n", &numBuff, (int*)&scannedLen);
		else
			scanned = sscanf(in->txt, "%lu%n", &numBuff, (int*)&scannedLen);
	}else{
		if(self->sign)
			scanned = sscanf(in->txt, "%i%n", (u32*)&numBuff, (int*)&scannedLen);
		else
			scanned = sscanf(in->txt, "%u%n", (u32*)&numBuff, (int*)&scannedLen);
	}

	if(scanned)
		self->asType.u64 = numBuff;	
	
return scannedLen;
}

Impl(Integer){
	.Formatter = {
		.Scan  	= Integer_Scan,
		.Print 	= Integer_Print
	},
};

/*------------------------------|
  	 FLOAT METHODS		|
------------------------------*/

u64 imethodimpl(Float, Print,, FormatID* formats, inst(StringBuilder) out){
	self(Float);
	
	u64 formatted_len = 0;
	char* buff = alloca(snprintf(NULL, DBL_MAX_10_EXP + DBL_DECIMAL_DIG, "%f", self->asType.f64));
	
	if(buff != NULL)
		formatted_len = snprintf(buff, DBL_MAX_10_EXP + DBL_DECIMAL_DIG, "%f", self->asType.f64);

	if(formatted_len != 0)
		StringBuilder.Append(out, &(data(String)){
			.txt = buff,
			.len = formatted_len
		});

return formatted_len;
}

u64 imethodimpl(Float, Scan,, FormatID* formats, inst(String) in){
	self(Float);

	if(in->txt[in->len + 1] != '\0') {
		ERR(ERR_INVALID, "in order to properly scan a string for an integer the string must be null terminated");
		return 0;
	}
	double numBuffDouble = 0;
	float  numBuffFloat  = 0;

	u64 scannedLen = 0, scanned = 0; 

	if(self->dbl)
		scanned = sscanf(in->txt, "%lf%n", &numBuffDouble, (int*)&scannedLen);
	else
		scanned = sscanf(in->txt, "%f%n",  &numBuffFloat,  (int*)&scannedLen);

	if(scanned){
		if(self->dbl)
			self->asType.f64 = numBuffDouble;	
		else
			self->asType.f32 = numBuffFloat;	
	}


return scannedLen;

}

Impl(Float){
	.Formatter = {
		.Scan  	= Float_Scan,
		.Print 	= Float_Print
	},
};


/*------------------------------|
  	 POINTER METHODS	|
------------------------------*/

u64 imethodimpl(Pointer, Print,, FormatID* formats, inst(StringBuilder) out){
	char buff[20] = {0};

	u64 print_len = snprintf(buff, 20, "%p", *(void**)object);

	StringBuilder.Append(out, String_From(buff, print_len));

return print_len;	
}

u64 imethodimpl(Pointer, Scan,, FormatID* formats, inst(String) in){
	self(Pointer)

	u64 scannedLen = 0;

	sscanf(in->txt, "%p%n", &self->data, (int*)&scannedLen);

return scannedLen;
}

Impl(Pointer){
	.Formatter = {
		.Scan  	= Pointer_Scan,
		.Print 	= Pointer_Print
	},
};


/*------------------------------|
  	 CSTRING METHODS	|
------------------------------*/

u64 imethodimpl(CString, Print,, FormatID* formats, inst(StringBuilder) out){
	char* string_ptr = *(char**)object;
	inst(String) string = String_From(string_ptr, UINT64_MAX);
	u64 actual_len = 0;
	if(formats[FORMAT_DATA] == DATA_DSN){
		actual_len += StringBuilder.Append(out, s("\""));
		actual_len += StringBuilder.Append(out, string);
		actual_len += StringBuilder.Append(out, s("\""));
	}else
		actual_len = StringBuilder.Append(out, string);
return actual_len;
}

u64 imethodimpl(CString, Scan,, FormatID* formats, inst(String) in){
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
Impl(CString){
	.Formatter = {
		.Scan  	= CString_Scan,
		.Print 	= CString_Print
	},
};


/*------------------------------|
  	  CHAR METHODS		|
------------------------------*/

u64 imethodimpl(Char, Print,, FormatID* formats, inst(StringBuilder) out){
	u64 actual_len = 1;
	char buff[4] = {0};
	if(formats[FORMAT_STRING] == STRING_NUM)
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
u64 imethodimpl(Char, Scan,, FormatID* formats, inst(String) in){
	*(char*)object = in->txt[0];
	return 1;
}

Impl(Char){
	.Formatter = {
		.Scan  	= Char_Scan,
		.Print 	= Char_Print
	},
};
