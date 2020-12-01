#include "mutex.h"
void mutext_init(pthread_mutex_t* mutex){
#if DBG
	pthread_mutexattr_t attr;
	int ret=pthread_mutexattr_init(&attr);
	if(ret!=0){
		fprintf(stderr, "Mutex failed to create attr: %s %d", strerror(ret), ret);
		exit(ret);
	}
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK);
	ret=pthread_mutex_init(mutex, &attr);
	pthread_mutexattr_destroy(&attr);
	if(ret!=0){
		fprintf(stderr, "Mutex failed to init mutex: %s %d", strerror(ret), ret);
		exit(ret);
	}
#else
	int ret=pthread_mutex_init(mutex, NULL);
	if(!ret){
		fprintf("Mutex failed to init mutex: %s", strerror(ret));
		exit(ret);
	}
#endif
	return;
}