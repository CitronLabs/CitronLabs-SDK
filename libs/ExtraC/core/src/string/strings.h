#pragma once
#include "../../include/stringutils.h"
#include "../../include/data.h"

private(StringBuilder,
	List(char) data;
	u64 max_len;
);
private(String,
	u8 inline_alloc : 1;
);


