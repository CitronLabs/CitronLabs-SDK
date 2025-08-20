#include "__systems.h"

#if 	__LinuxEnv_AudioBackend == LinuxEnv_Audio_PipeWire
	#include "../backends/pipewire.c"
#endif

const ImplAs(audio, LinuxAudio){	
	.initSystem 	  = LinuxAudio_initSystem,
	.exitSystem 	  = LinuxAudio_exitSystem,
	.enumDevices 	  = LinuxAudio_enumDevices,
	.grabStream  	  = LinuxAudio_grabStream,
	.closeStream 	  = LinuxAudio_closeStream,
	.startStream 	  = LinuxAudio_startStream,
	.stopStream  	  = LinuxAudio_stopStream,
	.readStream  	  = LinuxAudio_readStream,
	.writeStream 	  = LinuxAudio_writeStream,
	.handleEvents 	  = LinuxAudio_handleEvents,
	.pollEvents 	  = LinuxAudio_pollEvents
};
