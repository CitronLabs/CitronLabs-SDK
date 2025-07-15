#pragma once
#ifndef NO_HEADERS
#include "../../include/all.h"
#include <ctype.h>
#endif

private(StringBuilder,
	List(char) data;
	u64 max_len;
);
private(String,
	u8 inline_alloc : 1;
);
