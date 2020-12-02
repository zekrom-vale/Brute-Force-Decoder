#ifndef VALIDATOR_H
#define VALIDATOR_H
#include "../Util/config.h"
#include "../main.h"
#include "../queue.h"
#include <semaphore.h>
#include "../Decoder/decoder.h"
#include <regex.h>
#include <stdbool.h>
#include "../Print/print.h"

#define VALEXT false

#ifndef WORD_REG
#define WORD_REG "Russia"
#endif

#ifndef EN_ONLY
#define EN_ONLY true
#endif

#if EN_ONLY
#ifndef NON_EN
#define NON_EN "\xBF-\xFF"
#endif
#else
#ifndef NON_EN
#define NON_EN ""
#endif
#endif

#ifndef INVAL_REG
#define INVAL_REG "[\x01-\x08\x0B\x0E-\x1F\x7F-\x9F"NON_EN"]"
#endif

void validator_init();
void* validator_main(void* args);
#endif