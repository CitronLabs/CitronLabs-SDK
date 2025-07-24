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

	u64 method(StringBuilder,Set,, ...);
	u64 method(StringBuilder,Append,, inst(String) string, ...);
	u64 method(StringBuilder,Prepend,, inst(String) string, ...);
	u64 method(StringBuilder,Insert,, u64 index, inst(String) string, ...);
	errvt method(StringBuilder,Replace,, u64 index, inst(String) string);
	errvt method(StringBuilder,Clear);
	errvt method(StringBuilder,Max,, u64 max_len);
	str_t method(StringBuilder,GetStr);
	inst(String) method(StringBuilder,CreateStr);
)


Enum(chartype, CT_ASCI, CT_UTF8);

Type(str_regex_result,
	u64 str_offset;
	u64 len;
);

Class(String,
__INIT(cstr c_str; u64 len; bool inline_alloc),
__FIELD(u64 len; cstr txt; chartype type;),
	
	#define pushString(string, max_len) String_Construct(			\
		(String_ConstructArgs){string, strnlen(string, max_len), true},	\
		alloca(								\
	 		sizeof(String_Instance)  + 				\
	 		sizeof_String_Private    + 				\
	 		strnlen(string, max_len) + 1				\
      		)								\
	)
	
	#define newString(string, max_len) String_Construct(			\
		(String_ConstructArgs){string, strnlen(string, max_len), true},	\
		alloca(								\
	 		sizeof(String_Instance)  + 				\
	 		sizeof_String_Private    + 				\
	 		strnlen(string, max_len) + 1				\
      		)								\
	)

	#define s(string) String_Construct(					\
		(String_ConstructArgs){string, sizeof(string) - 1, true},	\
		alloca(								\
	 		sizeof(String_Instance) + 				\
	 		sizeof_String_Private   + 				\
	 		sizeof(string)						\
      		)								\
	)
	#define S(string) String_Construct(					\
		(String_ConstructArgs){string, sizeof(string) - 1, true},	\
		malloc(								\
	 		sizeof(String_Instance) + 				\
	 		sizeof_String_Private   + 				\
	 		sizeof(string)						\
      		)								\
	)
	#define str_cast(str_, maxlen_) (&(str_t){NULL, &String, strnlen(str_, maxlen_), str_, CT_ASCI })
	
	#define str_cutfcpy(str, by) (&(str_t){NULL, &String, str->len - by, &str->txt[by]})
	#define str_cutbcpy(str, by) (&(str_t){NULL, &String,str->len - by, &str->txt[str->len - 1 - by]})
	#define str_cutb(str, by) str->txt = &str->txt[str->len - 1 - by]; str->len = str->len - by;
	#define str_cutf(str, by) str->txt = &str->txt[by]; str->len = str->len - by;

      	#define str_view(str, start, end) (&(str_t){NULL, &String, end - start, &str->txt[start]})
	
	#define CAT_XCSTRING false
	#define CAT_CSTRING  true

	#define cat(...)     (String.Cat(push(String), CAT_CSTRING, __VA_ARGS__))
	#define catNew(...)  (String.Cat(new(String), CAT_CSTRING, __VA_ARGS__))
	#define xcat(...)    (String.Cat(push(String), CAT_XCSTRING, __VA_ARGS__))
	#define xcatNew(...) (String.Cat(new(String), CAT_XCSTRING, __VA_ARGS__))

	#define switchs(string) inst(String) __string__switch = string; loop(__loop_once__,1)
	#define cases(str) if(String.Compare(__string__switch, s(str)))
	#define defaults else
	
	interface(Formatter);

	u64 		method(String, Scan,, ...);
	errvt 		method(String, ModCharLen,, chartype type);
	bool 		method(String, Compare,, inst(String) string2);
	i64 		method(String, Regex,, inst(String) regex, str_regex_result* result_buffer, size_t buffer_max);
	inst(String) 	method(String, Copy);
	inst(String) 	method(String, Cat,, bool usingCstr, ...);
)

Class(Integer,,
__FIELD(void* data; u8 sign : 1, longint : 1),
	interface(Formatter);
)

Class(Float,,
__FIELD(void* data; u8 dbl : 1),
	interface(Formatter);
)

Class(CString,,
__FIELD(void* data),
	interface(Formatter);
)

Class(Char,,
__FIELD(void* data),
	interface(Formatter);
)

Class(Pointer,, 
__FIELD(void* data),
	interface(Formatter);
)
Class(Boolean,, 
__FIELD(void* data),
	interface(Formatter);
)

#define asObject(var)								\
_Generic((var), 								\
i32:    	(&(data(Integer)){NULL, &Integer, &(var), true,  false}),	\
u32:		(&(data(Integer)){NULL, &Integer, &(var), false, false}), 	\
i64:    	(&(data(Integer)){NULL, &Integer, &(var), true,  true }), 	\
u64:    	(&(data(Integer)){NULL, &Integer, &(var), false, true }), 	\
i16:   		(&(data(Integer)){NULL, &Integer, &(var), true,  false}), 	\
u16:   		(&(data(Integer)){NULL, &Integer, &(var), false, false}),	\
i8:   		(&(data(Integer)){NULL, &Integer, &(var), true,  false}),	\
u8:   		(&(data(Integer)){NULL, &Integer, &(var), false, false}),	\
float:   	(&(data(Float))  {NULL, &Float,   &(var), false}),		\
double:   	(&(data(Float))  {NULL, &Float,   &(var), true}),		\
const char*: 	(&(data(CString)){NULL, &CString, &(var)}),			\
cstr:	 	(&(data(CString)){NULL, &CString, &(var)}),			\
c8:	 	(&(data(Char))   {NULL, &Char,    &(var)}),			\
void*:	  	(&(data(Pointer)){NULL, &Pointer, &(var)}),			\
bool:		(&(data(Boolean)){NULL, &Boolean, &(var)}), 			\
default: 	var)		

#define getMethods(type)  	\
_Generic(((data(type)){0}), 	\
i32:    	Integer		\
u32:		Integer		\
i64:    	Integer		\
u64:    	Integer		\
i16:   		Integer		\
u16:   		Integer		\
u8:   		Integer		\
i8:   		Integer		\
float:   	Float		\
double:  	Float		\
const char*: 	CString		\
cstr:	  	CString		\
pntr: 	 	Pointer		\
bool:		Boolean		\
default: 	type)		

