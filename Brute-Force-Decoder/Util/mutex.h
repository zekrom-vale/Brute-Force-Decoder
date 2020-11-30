#ifndef MUTEX_H
#define MUTEX_H
#define _XOPEN_SOURCE 700



#include "config.h"
#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void mutext_init(pthread_mutex_t* mutex);
#endif