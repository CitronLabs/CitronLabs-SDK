#pragma once
#include "../extern.h"


typedef void* socketHandle;
Enum(socketType,
	SOCKET_UNIX = 1,
	SOCKET_IPV4 = 2,
	SOCKET_IPV6 = 3,
	SOCKET_TCP  = 4,
	SOCKET_UDP  = 8,
	SOCKET_RAW  = 12,
)
typedef u8 ipv4_netaddress[4];
typedef u16 ipv6_netaddress[8];

Type(socketAddress,
     	socketType type;
	union{
	    struct{
		u16 port;
		ipv4_netaddress address;
     	    }ipv4;
	    struct{
		u16 port;
		ipv6_netaddress address;
     	    }ipv6;
	    struct{
		inst(String) path;
     	    }local;
     	}data;
)
Interface(network,
	errvt 		vmethod(initSystem);
	errvt 		vmethod(exitSystem);
	socketHandle 	vmethod(newSocket,  	socketType   type);	
	errvt 		vmethod(bindSocket, 	socketHandle handle, socketAddress address);
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

Enum(socketEventType,
    SOCKET_EVENT_NEWCLIENT,
    SOCKET_EVENT_RECIVE,
    SOCKET_EVENT_CLOSE
)
Type(socketEvent,
    socketHandle handle;
    socketEventType type;
)
