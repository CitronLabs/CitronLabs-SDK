#pragma once
#include "./interface.h"

#define SOCKET_PROTOCAL_NULL 0x00
#define SOCKET_PROTOCAL_UDP 0x01
#define SOCKET_PROTOCAL_TCP 0x02
#define SOCKET_PROTOCAL_RAW 0x03

#define SOCKET_DOMAIN_NULL 0x00
#define SOCKET_DOMAIN_IPV6 0x01
#define SOCKET_DOMAIN_IPV4 0x02
#define SOCKET_DOMAIN_LOCAL 0x03

#define D_IPV4 SOCKET_DOMAIN_IPV4
#define D_IPV6 SOCKET_DOMAIN_IPV6
#define D_LOCAL SOCKET_DOMAIN_LOCAL


#define Protocal(name, ...) 					\
	typedef struct{ __VA_ARGS__ } name##_header; 		\
	inline Packet msg##name(name##_header header, Packet body)

#define msgHandler(protocal, ...) 				\
	inline Packet msg##name(name##_header header, Packet body)

#define msgBuild(packet, ...){ 			\
	Packet __parent_packet = {0};		\
		__VA_ARGS__; 			\
	packet = __parent_packet;		\
} 
#define msgSend(conn, ...){ 			\
	Packet __parent_packet = {0};		\
		__VA_ARGS__; 			\
	Connection.Send(conn, __parent_packet);	\
} 

#define msgReturn(...){			 	\
	Packet __parent_packet = {0};		\
		__VA_ARGS__; 			\
	return __parent_packet;			\
}

#define msgBuff(buff, size) (Packet){size,buff}
#define msgString(string) __parent_packet = (Packet){strnlen(string, UINT64_MAX), string}; 
#define msgText(...) msgString(#__VA_ARGS__)
#define msg(protocal, ...)	 		\
	 Packet* protocal##_packet 		\
		 = &__parent_packet; 		\
	for(Packet __parent_packet = {0};	\
	    protocal##_packet->size == 0; 	\
	    *protocal##_packet = msg##protocal(	\
		(protocal##_header){__VA_ARGS__}\
		, __parent_packet))


Type(socket_settings,
	u8 protocal : 2;
	u8 domain   : 2;
	u8 blocking : 1;
)

typedef struct Connection_Instance Connection_Instance;

Class(Socket,
__INIT(socket_settings settings;),
__FIELD(),

	errvt method(Socket,Bind,, socketAddress address);
	errvt method(Socket,Listen,, u32 num_waiting);
	inst(Connection) method(Socket,Accept);
	socket_settings method(Socket,GetSettings);
      	socketAddress method(Socket, GetAddress);
);


Type(Packet,
	u32 size;
	void* buff;
);

Class(Connection,
__INIT(socket_settings settings; socketAddress address), 
__FIELD(),

	errvt method(Connection,Send,, Packet message);
	errvt method(Connection,Recieve,, Packet message);
	errvt method(Connection,Watch);
	errvt method(Connection,UnWatch);
	bool method(Connection,Check);
	errvt method(Connection,GroupJoin,, socketAddress address, void* interface_addr);
	errvt method(Connection,GroupLeave);
	errvt method(Connection,GroupSend,, Packet message);
	errvt method(Connection,GroupRecive,, Packet message);
	socket_settings method(Connection,GetSettings);
      	socketAddress method(Socket, GetAddress,, bool groupAddress);
);

