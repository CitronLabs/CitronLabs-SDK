#include "__systems.h"

#if 	__LinuxEnv_AudioBackend == LinuxEnv_Audio_PipeWire
	#include "../backends/pipewire.c"
#endif



const ImplAs(audio, LinuxAudio){	
	.initSystem 	  = LinuxAudio_initSystem,
	.exitSystem 	  = LinuxAudio_exitSystem,
	.enumAudioDevices = LinuxAudio_enumAudioDevices,
	.grabAudioStream  = LinuxAudio_grabAudioStream,
	.closeAudioStream = LinuxAudio_closeAudioStream,
	.startAudioStream = LinuxAudio_startAudioStream,
	.stopAudioStream  = LinuxAudio_stopAudioStream,
	.readAudioStream  = LinuxAudio_readAudioStream,
	.writeAudioStream = LinuxAudio_writeAudioStream,
	.handleEvents 	  = LinuxAudio_handleEvents,
	.pollEvents 	  = LinuxAudio_pollEvents
}
