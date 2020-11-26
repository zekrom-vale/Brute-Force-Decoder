#ifndef MUTEX_H
#define MUTEX_H

#ifndef PTHREAD_MUTEX_ERRORCHECK
#define PTHREAD_MUTEX_ERRORCHECK PTHREAD_MUTEX_ERRORCHECK_NP
#endif

#include "config.h"
#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>

void mutext_init(pthread_mutex_t* mutex);
#endif