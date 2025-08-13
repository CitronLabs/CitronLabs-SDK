#pragma once
#include "../extern.h"

#define AUDIO_IN   1
#define AUDIO_OUT  0

typedef bool audioDirection;

Type(AudioSpec,
    u32 sample_rate;    // e.g., 44100, 48000 Hz
    u16 channels;       // e.g., 1 (mono), 2 (stereo)
    u16 bits_per_sample; // e.g., 16, 24, 32 bits
);

Type(audioDevice,
	inst(String) name;
	inst(String) manufacturer;
	inst(String) model;
	
	void* uniqueID;
    
	audioDirection direction;

	u32 maxChannels;              	// Maximum number of channels supported.
    	u32* supportedSampleRates; 	// A list of supported sample rates (terminated by 0).
    	u32* supportedBitsPerSample;  	// A list of supported bits per sample (terminated by 0).
    	u32 minLatencyFrames;         	// Minimum latency in frames.
    	u32 maxLatencyFrames;         	// Maximum latency in frames.
    	u32 defaultLatencyFrames;     	// Default latency in frames.

)

typedef void* audioHandle; // aka an audio stream
Interface(audio,
	errvt 			vmethod(initSystem);
	errvt 			vmethod(exitSystem);
	audioHandle 		vmethod(grabStream,  bool direction, audioDevice* device, size_t framesize, AudioSpec spec);
	arry(audioDevice) 	vmethod(enumDevices, u64* numDevices);
	errvt			vmethod(startStream, audioHandle handle);
	errvt			vmethod(stopStream,  audioHandle handle);
	errvt			vmethod(closeStream, audioHandle handle);
	errvt			vmethod(writeStream, audioHandle handle, void* buffer, size_t frames);
	errvt			vmethod(readStream,  audioHandle handle);

	errvt 		  	vmethod(handleEvents,     audioHandle handle, Queue(OSEvent) evntQueue);
	u64 		  	vmethod(pollEvents);

)

Enum(audioEventType,
	AUDIO_EVENT_NEWFRAME,
)

Type(audioEvent,
	audioHandle handle;
	audioEventType type;
)
