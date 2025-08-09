#pragma once
#include "extern.h"

Decl(AudioDevice);


Type(AudioSpec,


)

Data(Audio,
__INIT(arry(float) samples; size_t len),
	inhert(Buffer);
	AudioSpec spec;
);

#define AUDIO_IN   1
#define AUDIO_OUT  0

Class(Jack,
__INIT(inst(AudioDevice) device; bool direction),
__FIELD(),
	errvt method(Jack, sendAudio,, inst(Audio) audio);
	errvt method(Jack, connect,,   inst(Audio) audio);
);

Class(AudioDevice,
__INIT(errvt fn(callback, inst(Audio) audio, pntr params)),
__FIELD(),
	errvt method(AudioDevice, setParamsStruct,, pntr params, size_t len);
);

