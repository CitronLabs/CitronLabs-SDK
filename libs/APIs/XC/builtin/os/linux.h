#pragma once
#include "../../os.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>
#include <unistd.h>
#include <bits/pthreadtypes.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <net/if.h>
#include <sys/epoll.h>

Static(LinuxEnv,
	interface(OS);
	
)



