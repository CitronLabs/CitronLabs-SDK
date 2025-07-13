#pragma once
#include "std-libc.h"
#include "std-types.h"
#include "std-utils.h"
#include "stdext-string.h"

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

#define msgSend(conn, error_handling, ...){ 	\
	msg_packet __parent_packet = {0};	\
		__VA_ARGS__; 			\
	if(connectSend(conn, __parent_packet))	\
		error_handling; 		\
} 

#define msgReturn(...){			 	\
	msg_packet __parent_packet = {0};	\
		__VA_ARGS__; 			\
	return __parent_packet;			\
} 
#define msgBuff(buff, size) (msg_packet){size,buff}
#define msgText(string) __parent_packet = (msg_packet){strnlen(string, UINT64_MAX), string}; 
#define msgInline(...) msgText(#__VA_ARGS__)
#define msg(protocal, ...)	 		\
	 msg_packet* protocal##_packet 		\
		 = &__parent_packet; 		\
	for(msg_packet __parent_packet = {0};	\
	    protocal##_packet->size == 0; 	\
	    *protocal##_packet = msg##protocal(	\
		(protocal##_header){__VA_ARGS__}\
		, __parent_packet))

typedef u8 ipv4_netaddress[4];
typedef u16 ipv6_netaddress[8];

Type(address_sockipv4,
	u16 port;
	ipv4_netaddress address;
)


Type(address_sockipv6,
	u16 port;
	ipv6_netaddress address;
)


Type(address_socklocal,
	inst(String) path;
)


Type(socket_settings,
	u8 protocal : 2;
	u8 domain   : 2;
	u8 blocking : 1;
)

Type(nethost_resolve,
	inst(String) host_name;
	ipv4_netaddress* ipv4_addrs;
	ipv6_netaddress* ipv6_addrs;
)

errvt netDomainResolve(nethost_resolve* resolve, inst(String) host_name, u8 domain_type);


typedef struct Connection_Instance Connection_Instance;

Class(Socket,
__INIT(socket_settings settings;),
__FIELD(),

	errvt method(Socket,Bind,, void* address);
	errvt method(Socket,Listen,, u32 num_waiting);
	inst(Connection) method(Socket,Accept);
	socket_settings method(Socket,GetSettings);
      	errvt method(Socket, GetAddress,, void* address);
);


Type(msg_packet,
	u32 size;
	void* buff;
);

Class(Connection,
__INIT(socket_settings settings; void* address;), 
__FIELD(),

	errvt method(Connection,Send,, msg_packet message);
	errvt method(Connection,Recieve,, msg_packet message);
	errvt method(Connection,Watch);
	errvt method(Connection,UnWatch);
	bool method(Connection,Check);
	errvt method(Connection,GroupJoin,, void* address, void* interface_addr);
	errvt method(Connection,GroupLeave);
	errvt method(Connection,GroupSend,, msg_packet message);
	errvt method(Connection,GroupRecive,, msg_packet message);
	socket_settings method(Connection,GetSettings);
);

enum HTTP_Method{
	HTTP_GET,
	HTTP_POST,
	HTTP_PUT,
};

typedef struct{enum HTTP_Method method; cstr route;} HTTP_header;
msg_packet msgHTTP(HTTP_header header, msg_packet body);
