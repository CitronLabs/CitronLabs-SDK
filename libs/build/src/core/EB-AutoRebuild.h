#pragma once
#include "ebee.h"


void checkautoRebuild(const char* file_path);
errvt evalautoRebuild();


#ifndef __AUTOREBUILD_SRC_DEF__
#include "./autoRebuild/autoRebuild.c"
#endif
