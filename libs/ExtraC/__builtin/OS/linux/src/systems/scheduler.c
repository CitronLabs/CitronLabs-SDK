#include "__systems.h"

#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, cstr argv[]);
Type(LinuxThread,
	pthread_t thread;
);

void vmethodimpl(LinuxEnv_Scheduler, sleep, u64 millisec){
	usleep(millisec);
}

threadHandle vmethodimpl(LinuxEnv_Scheduler, newThread, void fn(startfn,void*), void* args){
	nonull(startfn, return NULL);

	LinuxThread* result = new(LinuxThread);

	if(-1 == pthread_create(&result->thread, NULL, (void*(*)(void*))startfn, args)){
		switch (errno) {
		
		}
	}

return result;
}


void childProcessStart(u32 flags, cstr exePath, cstr* args){

	if(getbitflag(flags, PROCFLAG_DEBUG)){
		ptrace(PTRACE_TRACEME, 0, NULL, NULL);
		switch (errno) {
			
		}
	}


	execv(exePath, args);
	switch (errno) {
			
	}

	exit(-1);
}

processHandle parentProcessStart(u32 flags, processHandle child){

	if(getbitflag(flags, PROCFLAG_DEBUG)){
		ptrace(PTRACE_ATTACH, child, NULL, NULL);	
		switch (errno) {
	
		}
	}
	
	waitpid((pid_t)(u64)child, NULL, 0);
	switch (errno) {
	
	}

return child;
}

processHandle vmethodimpl(LinuxEnv_Scheduler, newProcess, cstr exePath, cstr args, u32 flags){
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
	List.Append(list, &(void*){0}, 1);
	processHandle result = (processHandle)(u64) fork();
	if(result == (processHandle)(i64)-1) {
		switch (errno) {
		
		}
		return NULL;
	}
	if(result == (processHandle)0)
		childProcessStart(flags, exePath, List.GetPointer(list, 0));
	else
		result = parentProcessStart(flags, result); // result gets NULL'd out if error

	pop(list);

return result;
}

errvt vmethodimpl(LinuxEnv_Scheduler, killProcess, processHandle handle){
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


threadHandle vmethodimpl(LinuxEnv_Scheduler, getCurrentThread){
	threadHandle result = (threadHandle)pthread_self();
return result;
}

typedef struct {pthread_mutex_t mut;}lin_mutex;
asClass(lin_mutex){ passover }
mutexHandle vmethodimpl(LinuxEnv_Scheduler, newMutex){
	mutexHandle result = new(lin_mutex, PTHREAD_MUTEX_INITIALIZER);
return result;
}
errvt vmethodimpl(LinuxEnv_Scheduler, lockMutex, mutexHandle handle){
	if(pthread_mutex_lock(&((lin_mutex*)handle)->mut) == -1){
		switch (errno) {
		
		}
	}
return OK;
}
errvt vmethodimpl(LinuxEnv_Scheduler, unlockMutex, mutexHandle handle){
	if(pthread_mutex_unlock(&((lin_mutex*)handle)->mut) == -1){
		switch (errno) {
		
		}
	}
return OK;
}
errvt vmethodimpl(LinuxEnv_Scheduler, tryLockMutex, mutexHandle handle){
	if(pthread_mutex_trylock(&((lin_mutex*)handle)->mut) == -1){
		switch (errno) {
		
		}
	}
return OK;
}

typedef struct {sem_t sem;}lin_semaphore;
asClass(lin_semaphore){ passover }

semaphoreHandle vmethodimpl(LinuxEnv_Scheduler, newSemaphore, size_t num){
	lin_semaphore* result = new(lin_semaphore);
	sem_init(&result->sem, 0, num);
	switch (errno) {
	
	}
return result;
}

errvt vmethodimpl(LinuxEnv_Scheduler, waitSemaphore, semaphoreHandle handle){
	if(sem_wait(&((lin_semaphore*)handle)->sem) == -1){
		switch (errno) {
		
		}
	}
return OK;
}
errvt vmethodimpl(LinuxEnv_Scheduler, postSemaphore, semaphoreHandle handle){
	if(sem_post(&((lin_semaphore*)handle)->sem) == -1){
		switch (errno) {
		
		}
	}
return OK;
}
errvt vmethodimpl(LinuxEnv_Scheduler, tryWaitSemaphore, semaphoreHandle handle){
	if(sem_wait(&((lin_semaphore*)handle)->sem) == -1){
		switch (errno) {
		
		}
	}
return OK;
}
const ImplAs(scheduler, LinuxScheduler){
	.sleep = LinuxEnv_Scheduler_sleep,
	.newThread = LinuxEnv_Scheduler_newThread,
	.newProcess = LinuxEnv_Scheduler_newProcess,
	.killProcess = LinuxEnv_Scheduler_killProcess,
	.getCurrentThread = LinuxEnv_Scheduler_getCurrentThread,
	.newMutex =  LinuxEnv_Scheduler_newMutex,
	.lockMutex =  LinuxEnv_Scheduler_lockMutex,
	.unlockMutex =  LinuxEnv_Scheduler_unlockMutex,
	.tryLockMutex =  LinuxEnv_Scheduler_tryLockMutex,
	.newSemaphore = LinuxEnv_Scheduler_newSemaphore,
	.waitSemaphore = LinuxEnv_Scheduler_waitSemaphore,
	.postSemaphore = LinuxEnv_Scheduler_postSemaphore,
	.tryWaitSemaphore = LinuxEnv_Scheduler_tryWaitSemaphore,
};
