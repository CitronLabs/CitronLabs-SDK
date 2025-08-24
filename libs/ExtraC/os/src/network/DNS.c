#define __NETWORK_SOURCE_DEF__
#include "posix.h"

asClass(ipv4_netaddress);
asClass(ipv6_netaddress);

errvt netDomainResolve(nethost_resolve* resolve, inst(String) host_name, u8 domain_type){
	
	if(domain_type < D_IPV6 && domain_type > (D_IPV6 | D_IPV4))
		return ERR(NETERR_HOSTRESOLVE, "invalid domain_type");

	struct addrinfo 
	hints = {
		.ai_family = 
		domain_type == (D_IPV6 | D_IPV4) ? AF_UNSPEC :
		domain_type == D_IPV4 ? AF_INET :
		domain_type == D_IPV6 ? AF_INET6 : 
		AF_UNSPEC
	},
	* host_data = NULL;
	
	List(ipv4_netaddress) i4_addrs =
		(domain_type == D_IPV4 || 
	         domain_type == (D_IPV4 | D_IPV6)) ?
		pushList(ipv4_netaddress, 10) : NULL;

	List(ipv6_netaddress) i6_addrs = 
		(domain_type == D_IPV6 || 
	         domain_type == (D_IPV4 | D_IPV6)) ?
		pushList(ipv6_netaddress, 10) : NULL;

	in_addr_t addr4 = {0};
	struct in6_addr addr6 = {0};

	if(0 != getaddrinfo(host_name->txt, NULL, &hints, &host_data) ) 
		return ERR(NETERR_HOSTRESOLVE, "could not resolve host");

	while(host_data->ai_next != NULL){

	    if(host_data->ai_family == AF_INET &&
	       (domain_type == D_IPV4 || 
	        domain_type == (D_IPV4 | D_IPV6)))
		{
			inet_pton(AF_INET, host_data->ai_addr->sa_data, &addr4);
			List.Append(i4_addrs, (ipv4_netaddress){ 
					((u8*)&addr4)[0], 
					((u8*)&addr4)[1], 
					((u8*)&addr4)[2], 
					((u8*)&addr4)[3] }
	      		,1);
		
		}else
	    if(host_data->ai_family == AF_INET6 &&
		(domain_type == D_IPV6 || 
	         domain_type == (D_IPV4 | D_IPV6)))
		{
			inet_pton(AF_INET6, host_data->ai_addr->sa_data, &addr6);
			List.Append(i6_addrs, (ipv6_netaddress){ 
					((u16*)&addr6)[0], 
					((u16*)&addr6)[1], 
					((u16*)&addr6)[2], 
					((u16*)&addr6)[3],
					((u16*)&addr6)[4],
					((u16*)&addr6)[5],
					((u16*)&addr6)[6],
					((u16*)&addr6)[7] }
	      		, 1);

		}

	}
	if(i4_addrs != NULL) resolve->ipv4_addrs = List.FreeToPointer(i4_addrs);
	if(i6_addrs != NULL) resolve->ipv6_addrs = List.FreeToPointer(i6_addrs);

return OK;
}
