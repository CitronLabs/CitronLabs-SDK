#pragma once
#include "../extern.h"

Type(VideoMode,
	u32 width;
	u32 height;
	u16 refreshRate;
)

#define FOURCC_CODE(code) ((u32)(code[0]) | ((u32)(code[1]) << 8) | ((u32)(code[2]) << 16) | ((u32)(code[3]) << 24))

Enum(VideoPixelFormat_Type,
	VideoPixelFormat_MPEG = FOURCC_CODE("MPEG")
)
Type(VideoPixelFormat,
	VideoPixelFormat_Type type;
     	u32 
     	    bottomMostModeIndex,
     	    topMostModeIndex;
)

Type(VideoFrame,
	void* buffer;
     	u32 frameIndex;
)
#define VIDEO_IN true
#define VIDEO_OUT false

typedef bool videoDirection;

Type(graphicsDevice,
	inst(String) name;
	inst(String) manufacturer;
	inst(String) model;

	void* uniqueID;
     	
	videoDirection direction;

	u32 currentMode;
	VideoMode* supportedModes;

	union{
	  struct{
		u16 dpi;
		u16 bitDepth;
		u16 rotation;
	
		bool primary;
	  } display;
	  struct{
		u32 currentPixFmt;
		VideoPixelFormat* supportedPixFmts;
	  } video;
	} info;


)
typedef void* graphicsHandle;

Interface(graphics,
	errvt 			vmethod(initSystem);
	errvt 			vmethod(exitSystem);
	graphicsHandle 		vmethod(initDisplay, 	 u32 x, u32 y, u32 w, u32 h, graphicsHandle parent);
	graphicsHandle 		vmethod(grabDevice, 	 graphicsDevice* device);
	arry(graphicsDevice) 	vmethod(enumDevices, 	 u64* numDevices);
	errvt	 		vmethod(closeDisplay,    graphicsHandle handle);
	errvt	 		vmethod(updateDisplay,   graphicsHandle handle, u32 x, u32 y, u32 w, u32 h, graphicsHandle parent);
	bool	 		vmethod(isDisplayClosed, graphicsHandle);
	errvt			vmethod(startVideo, 	 graphicsHandle handle);
	errvt			vmethod(stopVideo,  	 graphicsHandle handle);
	errvt			vmethod(closeVideo, 	 graphicsHandle handle);
	errvt			vmethod(pullVideoFrame,	 graphicsHandle handle, VideoFrame* frame);
	errvt			vmethod(pushVideoFrame,	 graphicsHandle handle, VideoFrame* frame);
	errvt 		  	vmethod(handleEvents,    graphicsHandle handle, Queue(OSEvent) evntQueue);
	u64 		  	vmethod(pollEvents);
)

Enum(displayEventType,
    DISPLAY_EVENT_RESIZE,	
    DISPLAY_EVENT_CLOSE,	
    DISPLAY_EVENT_VISIBILITY,	
)
Type(displayEvent,
    graphicsHandle handle;
 	displayEventType type;
)

Enum(videoEventType,
    VIDEO_EVENT_NEWFRAME,
)
Type(videoEvent,
    graphicsHandle handle;
 	videoEventType type;
)
