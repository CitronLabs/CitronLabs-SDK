#pragma once
#include "./types.h"
#include "./error.h"
#include <stddef.h>
#include <uchar.h>
#include <wchar.h>

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
	#define $(expr)    NULL, &(asObject(expr)->__methods->Formatter), generic asObject(expr)

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


Class(StringBuilder,
__INIT(inst(String) init_str; u64 limit;),
__FIELD(),
	#define endstr NULL, 0
      	#define str_t String_Instance

      	interface(Loggable);
      	interface(Formatter);
	interface(IterableList);

	u64 method(StringBuilder,Set,, inst(String) string, ...);
	u64 method(StringBuilder,Append,, inst(String) string, ...);
	u64 method(StringBuilder,Prepend,, inst(String) string, ...);
	u64 method(StringBuilder,Insert,, u64 index, inst(String) string, ...);
	errvt method(StringBuilder,Replace,, u64 index, inst(String) string);
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
wchar_t: 	sizeof(wchar_t)		\
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
wchar_t: 	sizeof(wchar_t)		\
)


static inline size_t str16nlen(char16_t* str, size_t maxlen){
	size_t len = 0;
	while (str[len] != u'\0' || len == maxlen) {
		len++;
	}
return len;
}

static inline size_t str32nlen(char32_t* str, size_t maxlen){
	size_t len = 0;
	while (str[len] != u'\0' || len == maxlen) {
		len++;
	}
return len;
}

#define getStringLen(string, maxlen)			\
_Generic((string),					\
char*: 		strnlen(generic string, maxlen),	\
char16_t*: 	str16nlen(generic string, maxlen),	\
char32_t*: 	str32nlen(generic string, maxlen),	\
wchar_t*: 	wcsnlen(generic string, maxlen)		\
)

#define getStringLiteralLen(string) (sizeof(string) / sizeof(typeof(*string)))

#define pushString(string, max_len) String_Construct(			\
	(String_ConstructArgs){						\
		string, getStringLen(string, max_len), 			\
		getCharType(string), true 				\
	},								\
	alloca(								\
 		sizeof(String_Instance)  + 				\
 		sizeof_String_Private    + 				\
 		getStringLen(string, max_len) + 1			\
	)								\
)

#define newString(string, max_len) String_Construct(			\
	(String_ConstructArgs){						\
		string, getStringLen(string, max_len), 			\
		getCharType(string), true				\
	}, 								\
	malloc(								\
 		sizeof(String_Instance)  + 				\
 		sizeof_String_Private    + 				\
 		getStringLen(string, max_len) + 1			\
	)								\
)

#define s(string) String_Construct(					\
	(String_ConstructArgs){						\
		string, getStringLiteralLen(string) - 1,		\
		getCharType(string), true 				\
	},								\
	alloca(								\
 		sizeof(String_Instance) + 				\
 		sizeof_String_Private   + 				\
 		sizeof(string)						\
	)								\
)
#define S(string) String_Construct(					\
	(String_ConstructArgs){						\
		string, getStringLiteralLen(string) - 1,		\
		getCharType(string), true 				\
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

#define cat(...)     (String.Cat(push(String), CAT_CSTRING, __VA_ARGS__))
#define catNew(...)  (String.Cat(new(String), CAT_CSTRING, __VA_ARGS__))
#define xcat(...)    (String.Cat(push(String), CAT_XCSTRING, __VA_ARGS__))
#define xcatNew(...) (String.Cat(new(String), CAT_XCSTRING, __VA_ARGS__))

#define switchs(string) inst(String) __string__switch = string; loop(__loop_once__,1)
#define cases(str) if(String.Compare(__string__switch, s(str)))
#define defaults else

Enum(chartype, CHAR_UTF8 = 0, CHAR_ASCII = 1, CHAR_UTF16 = 2, CHAR_UTF32 = 4);

Type(str_regex_result,
	u64 str_offset;
	u64 len;
);

typedef union{ 
    struct {
	chartype type;
	union {
	    char utf8; 
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

Class(String,
__INIT(typeof((TextEncoding){0}.string) txt; u64 len; bool inline_alloc),
__FIELD(typeof((TextEncoding){0}.string) txt; u64 len),
	
	interface(Formatter);
	interface(IterableList);

	u64 		method(String, Scan,, ...);
	bool 		method(String, Compare,, inst(String) string2);
	i64 		method(String, Regex,, inst(String) regex, str_regex_result* result_buffer, size_t buffer_max);
	inst(String) 	method(String, Copy);
	inst(String) 	method(String, Cat,, bool usingCstr, ...);
	inst(String) 	method(String, Cut,, bool fromFront, u64 by);
	errvt 		method(String, Convert,, void* result, chartype type);
)

void test(){
	inst(String) str  = String_FromLiteral("Hello");
	inst(String) str2 = String_View(str, 1, 4);
}

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

#define asObject(var)										\
_Generic((var), 										\
i32:    	(&(data(Integer)){NULL, &Integer, &((typeof(var)){var}), true,  false}),	\
u32:		(&(data(Integer)){NULL, &Integer, &((typeof(var)){var}), false, false}), 	\
i64:    	(&(data(Integer)){NULL, &Integer, &((typeof(var)){var}), true,  true }), 	\
u64:    	(&(data(Integer)){NULL, &Integer, &((typeof(var)){var}), false, true }), 	\
i16:   		(&(data(Integer)){NULL, &Integer, &((typeof(var)){var}), true,  false}), 	\
u16:   		(&(data(Integer)){NULL, &Integer, &((typeof(var)){var}), false, false}),	\
i8:   		(&(data(Integer)){NULL, &Integer, &((typeof(var)){var}), true,  false}),	\
u8:   		(&(data(Integer)){NULL, &Integer, &((typeof(var)){var}), false, false}),	\
float:   	(&(data(Float))  {NULL, &Float,   &((typeof(var)){var}), false}),		\
double:   	(&(data(Float))  {NULL, &Float,   &((typeof(var)){var}), true}),		\
const char*: 	(&(data(CString)){NULL, &CString, &((typeof(var)){var})}),			\
cstr:	 	(&(data(CString)){NULL, &CString, &((typeof(var)){var})}),			\
c8:	 	(&(data(Char))   {NULL, &Char,    &((typeof(var)){var})}),			\
char:	 	(&(data(Char))   {NULL, &Char,    &((typeof(var)){var})}),			\
void*:	  	(&(data(Pointer)){NULL, &Pointer, &((typeof(var)){var})}),			\
bool:		(&(data(Boolean)){NULL, &Boolean, &((typeof(var)){var})}), 			\
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

