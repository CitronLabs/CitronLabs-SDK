#pragma once
#include "../../include/error.h"
#include "../../include/alloc.h"
#include "../../include/stringutils.h"

private(Logger,
	inst(String) name;
	data(LogBook) 
		* error,
		* info;
)

static bool showErrors = true;
