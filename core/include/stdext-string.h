#pragma once
#include "std-libc.h"
#include "std-utils.h"
#include "std-error.h"
#include "std-types.h"

enum FORMAT_ID_DOMAIN{
#ifdef __USER_TYPE_FORMAT_DOMAINS__
	__USER_TYPE_FORMAT_DOMAINS__
#endif
	FORMAT_NUMS, FORMAT_STRINGS, FORMAT_DATA,
};
typedef enum {
	NUMS_REG, NUMS_HEX, NUMS_FLOAT, NUMS_BIN,
	STRING_REG, STRING_WORD, STRING_NUM, 
	DATA_DSN, DATA_DEBUG,
#ifdef __USER_TYPE_FORMAT__
	__USER_TYPE_FORMAT__
#endif
}FORMAT_ID;

#define NUMS_DEFAULT NUMS_REG
#define STRING_DEFAULT STRING_REG
#define DATA_DEFAULT DATA_DSN

#define FORMAT_DOMAIN_TOP FORMAT_DATA

static const FORMAT_ID __default_formats[FORMAT_DOMAIN_TOP + 1] = 
	{
	[FORMAT_NUMS] = NUMS_DEFAULT,
	[FORMAT_DATA] = DATA_DEFAULT,
	[FORMAT_STRINGS] = STRING_DEFAULT,
	#ifdef __USER_TYPE_FORMAT_DEFAULTS__
		__USER_TYPE_FORMAT_DEFAULTS__
	#endif
	}; 

#define FMT ((void*)1)
#define F(format_type, format, ...) 				\
	FMT, FORMAT_##format_type, format_type##_##format,	\
	__VA_ARGS__, 						\
	FMT,FORMAT_##format_type, format_type##_##format

typedef struct String_Instance String_Instance;
typedef struct StringBuilder_Instance StringBuilder_Instance;

Interface(Formatter,
	u64 imethod(Scan,, FORMAT_ID* format, inst(String) in);
	u64 imethod(Print,, FORMAT_ID* format, inst(StringBuilder) out);
)

Static(FormatUtils,
	u64 (*FormatVArgs)(inst(StringBuilder) out, va_list args);
	u64 (*ScanVArgs)(inst(String) in, va_list args);
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

	#define switchs(string) inst(String) __string__switch = string; loop(__loop_once__,1)
	#define cases(str) if(String.Compare(__string__switch, s(str)))
	#define defaults else
	
	interface(Formatter);

	u64 method(String, Scan,, ...);
	errvt method(String, ModCharLen,, chartype type);
	bool method(String, Compare,, inst(String) string2);
	i64 method(String, Regex,, inst(String) regex, str_regex_result* result_buffer, size_t buffer_max);
	inst(String) method(String, Copy);
)
