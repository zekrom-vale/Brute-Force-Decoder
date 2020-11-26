#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>

//Just to stop VS linting errors
#ifndef PTHREAD_MUTEX_ERRORCHECK
#define PTHREAD_MUTEX_ERRORCHECK 2
#endif

#define DBG true

void mutext_init(pthread_mutex_t* mutex);