#ifndef VALIDATOR_H
#define VALIDATOR_H
#include "../Util/config.h"
#include "../main.h"
#include "../queue.h"
#include <semaphore.h>
#include "../Decoder/decoder.h"
void* validator_main(void* args);
#endif