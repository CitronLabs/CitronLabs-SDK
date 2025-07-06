#pragma once
#ifdef __unix__
#include "../network.h"
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <net/if.h>
#include <sys/epoll.h>


#define ipv4addr_to_unix(ipv4addr) (*((in_addr_t*)ipv4addr))
#define ipv6addr_to_unix(ipv6addr) (*((struct in6_addr*)ipv6addr))
#define as_xcaddr(type, ptr) (*((address_sock##type*)ptr))
#define as_unaddr(type, ptr) (*((struct sockaddr_##type*)ptr))

private(Socket,
	int fd;
	socket_settings settings;
	struct sockaddr address;
	u16 sizeofaddr;
);

private(Connection,
	int fd;
	socket_settings settings;
	struct sockaddr addresses[2];
	socklen_t sizeofaddr;
	u8 watched : 1;
	u8 io_ready : 1;
);

static int epoll_fd = 0;
static Map(int, inst(Connection)) connections = NULL;

static socklen_t XCAddrToUnix(u8 type, void* xc_addr, struct sockaddr* unix_addr){

	switch(type){
	case SOCKET_DOMAIN_IPV4:{
	
		memcpy(unix_addr, &(struct sockaddr_in){
 			.sin_family = AF_INET,
 			.sin_port = as_xcaddr(ipv4, xc_addr).port,
 			.sin_addr = ipv4addr_to_unix(as_xcaddr(ipv4, xc_addr).address)
 		},
   		sizeof(struct sockaddr_in));
	return sizeof(struct sockaddr_in);
  	}
	case SOCKET_DOMAIN_IPV6:{
 		memcpy(unix_addr, &(struct sockaddr_in6){
 			.sin6_family = AF_INET6,
 			.sin6_port = as_xcaddr(ipv6, xc_addr).port,
 			.sin6_addr = ipv6addr_to_unix(as_xcaddr(ipv6, xc_addr).address)
 		},
   		sizeof(struct sockaddr_in));
	return sizeof(struct sockaddr_in);
	}
	case SOCKET_DOMAIN_LOCAL:{
 		memcpy(unix_addr, &(struct sockaddr_un){
			.sun_family = AF_LOCAL,
			.sun_path = {0}
 		},
   		sizeof(struct sockaddr_un));
		strncpy(
			((struct sockaddr_un*)unix_addr)->sun_path,
			as_xcaddr(local, xc_addr).path->txt,
			100
		);
	return sizeof(struct sockaddr_un);
	}
	default:{
		ERR(NETERR_SOCKINVAL, "invalid domain type");
	}
	}
return 0;
}
static errvt unixAddrToXCAddr(u8 type, struct sockaddr* unix_addr, void* xc_addr){

	switch (type) {
	case SOCKET_DOMAIN_IPV4:{
		*((address_sockipv4*)xc_addr) = (address_sockipv4){
			.address = {
				((u8*)&(as_unaddr(in, unix_addr).sin_addr.s_addr))[0],
				((u8*)&(as_unaddr(in, unix_addr).sin_addr.s_addr))[1],
				((u8*)&(as_unaddr(in, unix_addr).sin_addr.s_addr))[2],
				((u8*)&(as_unaddr(in, unix_addr).sin_addr.s_addr))[3],
			},
			.port = as_unaddr(in, unix_addr).sin_port
		};
	}
	case SOCKET_DOMAIN_IPV6:{
		*((address_sockipv6*)xc_addr) = (address_sockipv6){
			.address = {
				((u16*)&(as_unaddr(in6, unix_addr).sin6_addr))[0],
				((u16*)&(as_unaddr(in6, unix_addr).sin6_addr))[1],
				((u16*)&(as_unaddr(in6, unix_addr).sin6_addr))[2],
				((u16*)&(as_unaddr(in6, unix_addr).sin6_addr))[3],
				((u16*)&(as_unaddr(in6, unix_addr).sin6_addr))[4],
				((u16*)&(as_unaddr(in6, unix_addr).sin6_addr))[5],
				((u16*)&(as_unaddr(in6, unix_addr).sin6_addr))[6],
				((u16*)&(as_unaddr(in6, unix_addr).sin6_addr))[7],
			},
			.port = as_unaddr(in, unix_addr).sin_port
		};
	}
	case SOCKET_DOMAIN_LOCAL:{
		*((address_socklocal*)xc_addr) = (address_socklocal){
			.path = str_cast(as_unaddr(un, unix_addr).sun_path, 100)
		};
	}
	default:{
		return ERR(NETERR_SOCKINVAL, "invalid domain type");
	}
	}

return OK;
}

#ifndef __NETWORK_SOURCE_DEF__
#include "./connections.c"
#include "./sockets.c"
#include "./netinfo.c"
#endif
#endif
