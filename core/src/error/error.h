#pragma once
#include "../../include/std-all.h"

private(Logger,
	inst(String) name;
	data(LogBook) 
		* error,
		* info;
)

static bool showErrors = true;
