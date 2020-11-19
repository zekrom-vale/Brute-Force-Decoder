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

#define KEY_SIZE 256;


extern pthread_t keyProducers[N_KEYS];
extern pthread_t validators[N_VALS];
extern pthread_t decoders[N_DECS];

extern struct queue* keyQueue;
#define KEY_MAX 40
extern sem_t semKey;
extern sem_t semKeyMax;

extern struct queue* textQueue;
#define TEXT_MAX 20
extern sem_t semText;
extern sem_t semTextMax;

#endif
