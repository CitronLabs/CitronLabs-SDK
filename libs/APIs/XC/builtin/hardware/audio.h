#pragma once
#include "../../os.h"

Class(Speaker,
__INIT(),
__FIELD(),

)

Class(Microphone,
__INIT(),
__FIELD(),

)

static inst(Speaker) defaultSpeaker 	= NULL;
static inst(Speaker) defaultMicrophone  = NULL;
