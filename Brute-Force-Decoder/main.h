#ifndef MAIN_H
#define MAIN_H

#include "queue.h"
#include "file.h"
#include "Decoder/decoder.h"
#include "KeyProducer/keyProducer.h"
#include "Validator/validator.h"
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>

#ifndef N_KEYS
#define N_KEYS 1
#endif
#ifndef N_DECS
#define N_DECS 3
#endif
#ifndef N_VALS
#define N_VALS 6
#endif

#ifndef KEY_SIZE
#define KEY_SIZE 256
#endif


extern pthread_t keyProducers[N_KEYS];
extern pthread_t validators[N_VALS];
extern pthread_t decoders[N_DECS];

extern struct queue* keyQueue;
#ifndef KEY_MAX
#define KEY_MAX 40
#endif
extern sem_t semKey;
#if KEY_MAX!=0
extern sem_t semKeyMax;
#endif

extern struct queue* textQueue;
#ifndef TEXT_MAX
#define TEXT_MAX 20
#endif
extern sem_t semText;
#if TEXT_MAX!=0
extern sem_t semTextMax;
#endif

extern bool halt;
#ifndef CYPHER_FILE
#define CYPHER_FILE "cypher.txt"
#endif
extern struct sizeWrapper* cypherText;

#endif
