#include "../../extern.h"

using_namespace(OS.network.obj, netObjAPI)

void NETOBJ_INTERFACE_TESTS(){
	netObjAPI->init(&(netobjInfo){
		.interface = s("HttpServer"),
		.name 	   = s("Bravo"),
		.field 	   = b(
				netField("isOnline", GET_SET, STRING, S("False"))
		),
		.methods   = b(
				netMethodDecl("Startup", 
		 			D("Maintinace_Interval_Hours", N(1000))
		 		)
		)
	});


	networkHandle bravoServer = netObjAPI->find("HttpServer", "Bravo");

	netObjAPI->call(bravoServer, "Startup", NULL);	

	if(String.Compare(netObjAPI->get(bravoServer, "isOnline").asString, s("True"))){
		loginfo("Bravo server online");
	}else{
		logerr("Bravo server failed to go online");
	}

	netObjAPI->close(bravoServer);
}
