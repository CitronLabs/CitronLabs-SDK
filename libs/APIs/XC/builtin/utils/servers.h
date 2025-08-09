#include "../../os.h"

Interface(Server,
	errvt imethod(handlePacket,, inst(Connection) client, inst(Packet) packet);
	errvt imethod(reviewNewClient,, inst(Connection) client);
)

Class(ServerManager,
__INIT(ifob(Server) server; inst(Logger) logger; u16 max_threads),
__FIELD(
	inst(Thread) 	main_thread;
     	inst(TimeWatch) active_timewatch;
     	inst(Logger)	logger
),
	errvt method(ServerManager, startServer);
	errvt method(ServerManager, limitThreads,, u16 limit);
)
