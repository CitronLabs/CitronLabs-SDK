#include "./datastructs.h"

void numBinaryLiteral(FORMAT_ID* formats, inst(String) in, inst(Number) num){
	
	inst(StringBuilder) num_str = new(StringBuilder, NULL, UINT64_MAX);
	u64 cursor = 0;
	
	//Parsing the 0b\*number*\ Format
	if(in->txt[cursor] == '\\'){
		cursor++;
		while(in->txt[cursor] != '\\'){
			//Checking the character is not 1 or 0 and not whitespace
			if((in->txt[cursor] < '0' || 
			    in->txt[cursor] > '1') &&
			   !isblank(in->txt[cursor])) break;
			
			if(in->txt[cursor] <= ' '){ cursor++; continue;}
	
			if(in->txt[cursor] == '1') 
				StringBuilder.Append(num_str, s("1"));
			else 
				StringBuilder.Append(num_str, s("0"));

			cursor++;
		}
	}
	//Parsing the 0b*number* Format
	else{
		while(in->txt[cursor] == '0' || in->txt[cursor] == '1'){

			if(in->txt[cursor] == '1') 
				StringBuilder.Append(num_str, s("1"));
			else 
				StringBuilder.Append(num_str, s("0"));
			
			cursor++;
		}
	
	}
	cstr end;
	String_Instance num_txt = StringBuilder.GetStr(num_str);
	num->as_u64 = strtoull(num_txt.txt, &end, 2);
}

#define isvalidhex(c) (isdigit(c) || ((c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F')))
void numHexLiteral(FORMAT_ID* formats, inst(String) in, inst(Number) num){
	
	inst(StringBuilder) num_str = new(StringBuilder, NULL, UINT64_MAX);
	u64 cursor = 0;
	
	//Parsing the 0b\*number*\ Format
	if(in->txt[cursor] == '\\'){
		cursor++;
		while(in->txt[cursor] != '\\'){
			//Checking the character is not 1 or 0 and not whitespace
			if(!isvalidhex(in->txt[cursor]) &&
			   !isblank(in->txt[cursor])) 
				break;
			
			if(isblank(in->txt[cursor])){ cursor++; continue;}
	
			if(in->txt[cursor] == '1') 
				StringBuilder.Append(num_str, s("1"));
			else 
				StringBuilder.Append(num_str, s("0"));

			cursor++;
		}
	}
	//Parsing the 0b*number* Format
	else{
		while(in->txt[cursor] == '0' || in->txt[cursor] == '1'){

			if(in->txt[cursor] == '1') 
				StringBuilder.Append(num_str, s("1"));
			else 
				StringBuilder.Append(num_str, s("0"));
			
			cursor++;
		}
	
	}
	cstr end;
	String_Instance num_txt = StringBuilder.GetStr(num_str);
	num->as_u64 = strtoull(num_txt.txt, &end, 2);
}

void numFloatLiteral(FORMAT_ID* formats, inst(String) in, inst(Number) num){
	cstr end;
	num->as_double = strtod(in->txt, &end);

}
void numIntegerLiteral(FORMAT_ID* formats, inst(String) in, inst(Number) num){
	cstr end;
	num->as_i64 = strtoll(in->txt, &end, 10);
}
void numUnsignedIntegerLiteral(FORMAT_ID* formats, inst(String) in, inst(Number) num){
	cstr end;
	num->as_i64 = strtoll(in->txt, &end, 10);
}

#define format(formatstr, type) \
	formatted_len = snprintf(buff, 50, formatstr, self->as_##type)

u64 imethodimpl(Number, Print,, FORMAT_ID* formats, inst(StringBuilder) out){
	u64 formatted_len = 0;
	char buff [50] = {0};
	cstr format = NULL;
	self(Number);

	if(formats[FORMAT_NUMS] != NUMS_DEFAULT)
		switch(formats[FORMAT_NUMS]){
		case NUMS_HEX:
			format = "%x";		
		break;
		default: {return 0;}
		}
	switch(self->type){
	case N_SIGNED: {
		switch(self->len){
		case 1:{format(format != NULL ? format : "%hi", i32); break;}
		case 2:{format(format != NULL ? format : "%i", i32); break;}
		case 3:{format(format != NULL ? format : "%li" ,i64); break;}
		}
	break;}
	case N_UNSIGNED: {	
		switch(self->len){
		case 1:{format(format != NULL ? format : "%hu", u64); break;}
		case 2:{format(format != NULL ? format : "%u", u32); break;}
		case 3:{format(format != NULL ? format : "%lu", u32); break;}
		}
	break;}
	case N_FLOATING:{format(format != NULL ? format : "%lf", double); break;}
	default:{ return 0; }
	}
	StringBuilder.Append(out, pushString(buff, 50));
return formatted_len;
}
u64 imethodimpl(Number, Scan,, FORMAT_ID* formats, inst(String) in){
	
	FORMAT_ID number_format = NUMS_DEFAULT;
	u64 cursor = 0;
	self(Number);
	
	if(in->txt[0] == '0'){
		cursor++;
		switch(in->txt[cursor]){
		case 'x': number_format = NUMS_HEX; break;
		case 'b': number_format = NUMS_BIN; break;
		}
	}else{
	    if(in->txt[cursor] == '-'){ cursor++;}
	
	    while(isdigit(in->txt[cursor]) || in->txt[cursor] == '.'){
		if(in->txt[cursor] == '.' && number_format == NUMS_DEFAULT){
			number_format = NUMS_FLOAT;
			cursor++;
		}
		else{
			cursor++;
		}
	    }
	}
	if(number_format != formats[FORMAT_NUMS] || cursor == 0) return 0;

	switch(number_format){
	case NUMS_FLOAT:{numFloatLiteral(formats, str_cutbcpy(in, in->len - cursor), self); break;}
	case NUMS_HEX:{	numHexLiteral(formats, str_cutbcpy(in, in->len - cursor), self); break;}
	case NUMS_BIN:{ numBinaryLiteral(formats, str_cutbcpy(in, in->len - cursor), self); break; }
	case NUMS_DEFAULT:{ 
		if(in->txt[0] == '-') 
			numIntegerLiteral(formats, str_cutbcpy(in, in->len - cursor), self);
		else 
			numUnsignedIntegerLiteral(formats, str_cutbcpy(in, in->len - cursor), self);
	}
	default:
		return 0;
	}
return in->len - cursor;
}

private(Number);
construct(Number,
	.Formatter = {
		.Scan = Number_Scan,
	  	.Print = Number_Print
	}
){
	self->as_double = args.number;
return self;
}
