#ifndef MAIN_H
#define MAIN_H

#include "Util/config.h"
#include "queue.h"
#include "file.h"
#include "Decoder/decoder.h"
#include "KeyProducer/keyProducer.h"
#include "Validator/validator.h"
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>

//Defines the ammount of threads to create
//Can pass -DN_KEYS=2 -DN_DECS=6 -DN_VALS=12 to set values
#ifndef N_KEYS
/** 
 * The ammount of key producers to create
 */
#define N_KEYS 1
#endif

#ifndef N_DECS
/** 
 * The ammount of decoders to create
 */
#define N_DECS 3
#endif

#ifndef N_VALS
/** 
 * The ammount of validators to create
 */
#define N_VALS 6
#endif

#ifndef KEY_SIZE
/** 
 * The maxumum key size to itterate to
 * This defines when to give up
 */
#define KEY_SIZE 256
#endif

/** 
 * References to the key producers
 */
extern pthread_t keyProducers[N_KEYS];
/** 
 * References to the validators
 */
extern pthread_t validators[N_VALS];
/** 
 * References to the decoders
 */
extern pthread_t decoders[N_DECS];

extern struct queue* keyQueue;
#ifndef KEY_MAX
/** 
 * The max ammount of keys to store
 */
#define KEY_MAX 40
#endif
extern sem_t semKey;
#if KEY_MAX!=0
extern sem_t semKeyMax;
#endif

extern struct queue* textQueue;
#ifndef TEXT_MAX
/** 
 * The max ammount of decoded text to store
 */
#define TEXT_MAX 20
#endif
extern sem_t semText;
#if TEXT_MAX!=0
extern sem_t semTextMax;
#endif

/**
* The flag to stop all threads in the loop
*/
extern bool halt;

#ifndef CYPHER_FILE
/** 
 * The file to find the cypher text in
 */
#define CYPHER_FILE "cypher.txt"
#endif

/**
 * The cypher text, wraped with size and a char* array
 * As `\0` can be used in the middle
 */
extern struct sizeWrapper* cypherText;

#endif
