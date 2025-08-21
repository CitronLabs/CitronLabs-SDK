#pragma once
#include "../extern.h"


typedef void* socketHandle;
typedef u8 ipv4_netaddress[4];
typedef u16 ipv6_netaddress[8];
typedef int socketType;

Type(socketAddress,
     	socketType type;
	union{
	    struct ipv4Address{
		u16 port;
		ipv4_netaddress address;
     	    }ipv4;
	    struct ipv6Address{
		u16 port;
		ipv6_netaddress address;
     	    }ipv6;
	    struct localAddress{
		inst(String) path;
     	    }local;
     	}data;
);

typedef struct ipv4Address ipv4Address;
typedef struct ipv6Address ipv6Address;
typedef struct localAddress localAddress;


Interface(network,
	const cstr stdVersion;
	errvt 		vmethod(initSystem);
	errvt 		vmethod(exitSystem);
	namespace(socket,
	  namespace(type,
	     	socketType
		UNIX,
		IPV4,
		IPV6,
		TCP ,
		UDP ,
		RAW ;
	  )
	socketHandle 	vmethod(init,  		socketType   type);	
	errvt 		vmethod(bind, 		socketHandle handle, socketAddress* address);
	errvt 		vmethod(listen,     	socketHandle handle, u32 num_connect);
	socketHandle 	vmethod(connect,    	socketHandle handle);
	socketHandle	vmethod(accept,     	socketHandle handle);
	errvt 		vmethod(send, 	    	socketHandle handle);
	errvt 		vmethod(recieve,    	socketHandle handle);
	errvt 		vmethod(groupJoin,  	socketHandle handle);
	errvt 		vmethod(groupLeave,   	socketHandle handle);
	errvt 		vmethod(groupSend,    	socketHandle handle);
	errvt 		vmethod(groupRecive,  	socketHandle handle);
	errvt 		vmethod(handleEvents, 	socketHandle handle, Queue(OSEvent) evntQueue);
	u64  	 	vmethod(pollEvents);
	)

)

Enum(socketEventType,
    socketEvent_NewClient,
    socketEvent_Recive,
    socketEvent_Close
)
Type(socketEvent,
    socketHandle handle;
    socketEventType type;
)
