#pragma once
#ifndef NO_HEADERS
#include "../../include/std-all.h"
#endif

static List(inst(Thread)) active_threads = NULL;
static Stack(inst(Thread)) freed_threads = NULL;

