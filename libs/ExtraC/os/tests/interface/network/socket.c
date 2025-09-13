#include "../../extern.h"

using_namespace(OS.network.socket, socketAPI)

void SOCKET_INTERFACE_TESTS(){
	const int type = socketAPI->type.IPV4 | socketAPI->type.TCP;
	const ipv4Address address = {
       		.address = {192,168,1,0}, 
		.port    = 8080,
	};
	
	networkHandle sock = socketAPI->init(type);
	
	socketAPI->bind(sock, 
	    push(socketAddress,
		.type = type,
       		.data.ipv4 = address
	    )
	);

	socketAPI->listen(sock, 1);
	networkHandle client = socketAPI->accept(sock);
}
