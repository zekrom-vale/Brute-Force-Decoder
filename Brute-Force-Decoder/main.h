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

struct queue* keyQueue=queue_init();
struct queue* textQueue=queue_init();

#endif
