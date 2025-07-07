#pragma once
#ifndef NO_HEADERS
#include "../../../include/std-all.h"
#include <ctype.h>
#endif

private(StringBuilder,
	List(char) data;
	u64 max_len;
);
private(String,
	u8 inline_alloc : 1;
);

u64 Print_VArgs(inst(StringBuilder) builder, va_list args);
u64 Scan_VArgs(inst(String) str, va_list args);

Impl(FormatUtils){
	.FormatVArgs = Print_VArgs,
	.ScanVArgs = Scan_VArgs
};
