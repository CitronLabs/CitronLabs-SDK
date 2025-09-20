#pragma once
#include "./types.h"
#include "./error.h"

Decl(String);
Decl(StringBuilder);

#define __FORMAT_CODES__
typedef enum FormatID{
	#define FORMAT(domain, default, ...) __VA_ARGS__,
		#include "config.h"
	#undef FORMAT
}FormatID;

typedef enum Format_Domain{
	#define FORMAT(domain, default, ...) FORMAT_##domain,
		#include "config.h"
	#undef FORMAT
	FORMAT_DOMAIN_TOP
}Format_Domain;


static const FormatID __default_formats[] = {
	#define FORMAT(domain, default, ...) [FORMAT_##domain] = default,
		#include "config.h"
	#undef FORMAT
};
#undef __FORMAT_CODES__


Interface(Formatter,
	#define $(expr)   (FormatPoint){NULL, {&(asObject(expr)->__methods->Formatter), generic asObject(expr)}}

	#define endprint NULL, NULL
	#define endscan  NULL, NULL

	u64 imethod(Scan,, FormatID* format, inst(String) in);
	u64 imethod(Print,, FormatID* format, inst(StringBuilder) out);
)

Static(FormatUtils,
	
	#define FMT ((pntr)1)
	#define F(format_type, format, ...) 				\
		FMT, FORMAT_##format_type, format_type##_##format,	\
		__VA_ARGS__, 						\
		FMT,FORMAT_##format_type, format_type##_##format

	u64 vmethod(FormatVArgs, inst(StringBuilder) out, va_list args);
	u64 vmethod(ScanVArgs, inst(String) in, va_list args);
)

Type(FormatPoint,
	char* text_ignore; // ignore here so that users can use "text" in the format description
     	ifob(Formatter) formatter;
)

Class(StringBuilder,
__INIT(inst(String) init_str; u64 limit;),
__FIELD(),
	#define endstr NULL, 0
      	#define str_t String_Instance

      	interface(Loggable);
      	interface(Formatter);
	interface(IterableList);

	u64 method(StringBuilder,Set,,       inst(String) string, ...);
	u64 method(StringBuilder,Append,,    inst(String) string, ...);
	u64 method(StringBuilder,Prepend,,   inst(String) string, ...);
	u64 method(StringBuilder,Insert,,    u64 index, inst(String) string, ...);
	errvt method(StringBuilder,Replace,, inst(String) replace_string, inst(String) replace_to);
	errvt method(StringBuilder,Clear);
	errvt method(StringBuilder,Max,, u64 max_len);
	str_t method(StringBuilder,GetStr);
	inst(String) method(StringBuilder,CreateStr);
)

#define getCharType(chars) 		\
_Generic((chars),			\
char*: 		CHAR_UTF8,		\
char:  		CHAR_ASCII,		\
char16_t*: 	CHAR_UTF16,		\
char16_t: 	CHAR_UTF16,		\
char32_t*: 	CHAR_UTF32,		\
char32_t: 	CHAR_UTF32,		\
wchar_t*: 	sizeof(wchar_t),	\
wchar_t: 	sizeof(wchar_t),	\
default:	CHAR_INVALID		\
)

#define getCharSize(chars) 		\
_Generic((chars),			\
char*: 		sizeof(char),		\
char:  		sizeof(char),		\
char16_t*: 	sizeof(char16_t),	\
char16_t: 	sizeof(char16_t),	\
char32_t*: 	sizeof(char32_t),	\
char32_t: 	sizeof(char32_t),	\
wchar_t*: 	sizeof(wchar_t),	\
wchar_t: 	sizeof(wchar_t),	\
default:	0			\
)

#define getStringLenBytes(_string, maxlen)		\
_Generic((_string),					\
char*: 		strnlen(generic _string, maxlen),	\
char16_t*: 	String.Utils.strnlen((TextEncoding){	\
			.string = 			\
	 		{CHAR_UTF16, generic _string}	\
	 	}, maxlen) * sizeof(char16_t),		\
char32_t*: 	String.Utils.strnlen((TextEncoding){	\
	 		.string = 			\
	 		{CHAR_UTF32, generic _string}	\
	 	}, maxlen) * sizeof(char32_t),		\
wchar_t*: 	wcsnlen(generic _string, maxlen) 	\
	 		* sizeof(wchar_t) 		\
)


#define pushString(string, max_len) String_Construct(			\
	(String_ConstructArgs){						\
		{getCharType(string), string},				\
		getStringLenBytes(string, max_len), 			\
		true 							\
	},								\
	alloca(								\
 		sizeof(String_Instance)  + 				\
 		sizeof_String_Private    + 				\
 		getStringLenBytes(string, max_len) + 1			\
	)								\
)

#define newString(string, max_len) String_Construct(			\
	(String_ConstructArgs){						\
		{getCharType(string), string},				\
		getStringLenBytes(string, max_len), 			\
		true							\
	}, 								\
	malloc(								\
 		sizeof(String_Instance)  + 				\
 		sizeof_String_Private    + 				\
 		getStringLenBytes(string, max_len) + 1			\
	)								\
)

#define s(string) String_Construct(					\
	(String_ConstructArgs){						\
		{getCharType(string), string},				\
		(sizeof(string)) - 1,					\
		true 							\
	},								\
	alloca(								\
 		sizeof(String_Instance) + 				\
 		sizeof_String_Private   + 				\
 		sizeof(string)						\
	)								\
)
#define S(string) String_Construct(					\
	(String_ConstructArgs){						\
		{getCharType(string), string},				\
		(sizeof(string)) - 1,					\
		true 							\
	},								\
	malloc(								\
 		sizeof(String_Instance) + 				\
 		sizeof_String_Private   + 				\
 		sizeof(string)						\
	)								\
)

#define String_From(str_, maxlen_) (&(str_t){NULL, &String, {getCharType(str_), str_}, getStringLen(str_, maxlen_)})
#define String_FromLiteral(str_) (&(str_t){NULL, &String, {getCharType(str_), str_}, sizeof(str_) - 1})

#define String_CutFrntCpy(str, by) String.Cut(&(str_t){NULL, &String, str->txt,  str->len}, CUT_FROMFRNT, by)
#define String_CutBackCpy(str, by) String.Cut(&(str_t){NULL, &String, str->txt, str->len}, CUT_FROMBACK, by)
#define String_CutBack(str, by) String.Cut(str, CUT_FROMFRNT, by)
#define String_CutFrnt(str, by) String.Cut(str, CUT_FROMBACK, by)

#define String_View(str, start, end) String_CutFrntCpy(String_CutBackCpy(str, str->len - end), start)

#define CAT_XCSTRING false
#define CAT_CSTRING  true

#define CUT_FROMBACK false
#define CUT_FROMFRNT true

#define cat(...)     (String.Cat(push(String), CAT_CSTRING, __VA_ARGS__, endstr))
#define catNew(...)  (String.Cat(new(String), CAT_CSTRING, __VA_ARGS__, endstr))
#define xcat(...)    (String.Cat(push(String), CAT_XCSTRING, __VA_ARGS__, endstr))
#define xcatNew(...) (String.Cat(new(String), CAT_XCSTRING, __VA_ARGS__, endstr))

#define switchs(string) inst(String) __string__switch = string; loop(__loop_once__,1)
#define cases(str) if(String.Compare(__string__switch, s(str)))
#define defaults else

Enum(chartype, CHAR_UTF8 = 0, CHAR_ASCII = 1, CHAR_UTF16 = 2, CHAR_UTF32 = 4, CHAR_INVALID = 5);

Type(str_regex_result,
	u64 str_offset;
	u64 len;
);

typedef union{ 
    struct {
	chartype type;
	union {
	    char ascii; 
	    char16_t utf16; 
	    char32_t utf32; 
	    wchar_t wide;
	} data;
    } character;
    struct {
	chartype type;
	union {
	    char* utf8; 
	    char16_t* utf16; 
	    char32_t* utf32; 
	    wchar_t* wide;
	} data;
    } string;
}TextEncoding; 

static inline size_t utf8_strnlen(const char *str, size_t len);
static inline size_t str16nlen(char16_t* str, size_t maxlen);
static inline size_t str32nlen(char32_t* str, size_t maxlen);

Class(String,
__INIT(typeof((TextEncoding){0}.string) txt; u64 bytes_len; bool inline_alloc),
__FIELD(typeof((TextEncoding){0}.string) txt; u64 len),
	
	interface(Formatter);
	interface(IterableList);

	u64 		method(String, Scan,, ...);
	bool 		method(String, Compare,, inst(String) string2);
	i64 		method(String, Regex,, inst(String) regex, str_regex_result* result_buffer, size_t buffer_max);
	inst(String) 	method(String, Copy);
	inst(String) 	method(String, Cat,, bool usingCstr, ...);
	inst(String) 	method(String, Cut,, bool fromFront, u64 by);
	inst(String)	method(String, Convert,, chartype type);
	namespace(Utils,
		size_t vmethod(strnlen, TextEncoding text, size_t len);
	)
)


Class(Integer,,
__FIELD(union {u64 u64; i64 i64; u32 u32; i32 i32;} asType; u8 sign : 1, longint : 1),
	interface(Formatter);
)

Class(Float,,
__FIELD(union {double f64; float f32;} asType; u8 dbl : 1),
	interface(Formatter);
)

Class(CString,,
__FIELD(typeof((TextEncoding){0}.string) data),
	interface(Formatter);
)

Class(Char,,
__FIELD(typeof((TextEncoding){0}.character) data),
	interface(Formatter);
)

Class(Pointer,, 
__FIELD(void* data),
	interface(Formatter);
)
Class(Boolean,, 
__FIELD(u8 value : 1),
	interface(Formatter);
)

#define boolToObject(var) 		\
	(&(data(Boolean)){ 		\
		NULL, 			\
		&Boolean, 		\
		*(u8*)&			\
		(typeof(var)){var} 	\
	})


#define pntrToObject(var) 		\
	(&(data(Pointer)){ 		\
		NULL, 			\
		&Pointer, 		\
		*(void**)&		\
		(typeof(var)){var} 	\
	})

#define charToObject(var) 		\
	(&(data(Char)){ 		\
		NULL, 			\
		&Char, 			\
		{getCharType(var), 	\
		*(wchar_t*)&		\
		(typeof(var)){var}} 	\
	})

#define cstrToObject(var) 		\
	(&(data(CString)){ 		\
		NULL, 			\
		&CString, 		\
		{getCharType(var), 	\
		*((void**)&		\
		(typeof(var)){var})} 	\
	})

#define floatToObject(var) 		\
	(&(data(Float)){ 		\
		NULL, 			\
		&Float, 		\
		*(double*)&		\
		(typeof(var)){var}, 	\
		.dbl = _Generic(var, 	\
		float  : false,		\
		double : true,		\
	  	default: false		\
	   	)			\
	})

#define intToObject(var) 		\
	(&(data(Integer)){ 		\
		NULL, 			\
		&Integer, 		\
		*(u64*)&		\
		(typeof(var)){var}, 	\
		.sign = _Generic(var, 	\
		i32 : true, u32 : false,\
		i64 : true, u64 : false,\
		i16 : true, u16 : false,\
		i8  : true, u8  : false,\
	  	default: false		\
	   	),			\
		.longint = _Generic(var,\
		i32 : false, u32 :false,\
		i64 : true,  u64 :true, \
		i16 : false, u16 :false,\
		i8  : false, u8  :false,\
	  	default: false		\
	   	)			\
	})

#define asObject(var)			\
_Generic((var), 			\
i32:    	intToObject(var),	\
u32:		intToObject(var), 	\
i64:    	intToObject(var), 	\
u64:    	intToObject(var), 	\
i16:   		intToObject(var), 	\
u16:   		intToObject(var),	\
i8:   		intToObject(var),	\
u8:   		intToObject(var),	\
float:   	floatToObject(var),	\
double:   	floatToObject(var),	\
const char*: 	cstrToObject(var),	\
char*:	 	cstrToObject(var),	\
c8:	 	charToObject(var),	\
char:	 	charToObject(var),	\
void*:	  	pntrToObject(var),	\
bool:		boolToObject(var), 	\
default: 	var)		

#define getMethods(type)  	\
_Generic(((data(type)){0}), 	\
i32:    	Integer,	\
u32:		Integer,	\
i64:    	Integer,	\
u64:    	Integer,	\
i16:   		Integer,	\
u16:   		Integer,	\
u8:   		Integer,	\
i8:   		Integer,	\
float:   	Float,		\
double:  	Float,		\
const char*: 	CString,	\
cstr:	  	CString,	\
pntr: 	 	Pointer,	\
bool:		Boolean,	\
default: 	type)		
