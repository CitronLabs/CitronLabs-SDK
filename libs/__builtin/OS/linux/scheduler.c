#include "OS.h"

int main(int argc, cstr argv[]);
Type(LinuxThread,
	pthread_t thread;
);

void vmethodimpl(LinuxScheduler, sleep, u64 millisec){
	usleep(millisec);
}

threadHandle vmethodimpl(LinuxScheduler, newThread, void fn(startfn,void*), void* args){
	nonull(startfn, return NULL);

	LinuxThread* result = new(LinuxThread);

	if(-1 == pthread_create(&result->thread, NULL, (void*(*)(void*))startfn, args)){
		switch (errno) {
		
		}
	}

return result;
}
processHandle vmethodimpl(LinuxScheduler, newProcess, cstr exePath, cstr args){
	nonull(exePath, return NULL);

	List(cstr) list = pushList(cstr);
	u64 start = 0;	
	for(int i = 0;;){
		if(args[i] == '\0') break;
		if(args[i] == ' '){
			List.Append(list, push(cstr, &args[start], i - start), 1);
			i++;
			while(!isalpha(args[i]) && args[i] != '\0') i++;
			if(args[i] == '\0') break;
			start = i;
		}
		i++;	
	}
	processHandle result = (processHandle)(u64) fork();
	if(result == (processHandle)(i64)-1) {
		switch (errno) {
		
		}
		return NULL;
	}
	if(result == (processHandle)0){ 
		execv(exePath, List.GetPointer(list, 0));
		switch (errno) {
				
		}
		exit(0);
	}	
	pop(list);
return result;
}

errvt vmethodimpl(LinuxScheduler, killProcess, processHandle handle){
	nonull(handle, return nullerr);

	if(kill(addrasval(handle), SIGTERM) == -1){
		switch (errno) {
		
		}
	}
	if(kill(addrasval(handle), SIGKILL) == -1){
		switch (errno) {
		
		}
	}
return OK; 
}
const ImplAs(scheduler, LinuxScheduler){
	.sleep = LinuxScheduler_sleep,
	.newThread = LinuxScheduler_newThread,
	.newProcess = LinuxScheduler_newProcess,
	.killProcess = LinuxScheduler_killProcess	
};
