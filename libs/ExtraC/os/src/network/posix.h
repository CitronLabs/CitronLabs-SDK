#pragma once
#include "../../include/all.h"
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



#ifndef __NETWORK_SOURCE_DEF__
#include "./connections.c"
#include "./sockets.c"
#include "./netinfo.c"
#endif
