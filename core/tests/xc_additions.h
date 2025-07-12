#pragma once
#include "../include/std-libc.h"

#define __USER_ERRORCODES__ \
ERR_TEST 

bool TEST_INIT();
#define __USER_INIT_FUNC__ TEST_INIT
