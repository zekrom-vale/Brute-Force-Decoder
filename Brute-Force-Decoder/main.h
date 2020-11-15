#ifndef MAIN_H
#define MAIN_H

#include "queue.h"
#include "Decoder/decoder.h"
#include "KeyProducer/keyProducer.h"
#include "Validator/validator.h"
#include <pthread.h>

#define N_KEYS 1;
#define N_DECS 3;
#define N_VALS 6;


extern pthread_t keyProducers[N_KEYS];
extern pthread_t validators[N_VALS];
extern pthread_t decoders[N_DECS];

extern struct queue* keyQueue;
extern struct queue* textQueue;

#endif
