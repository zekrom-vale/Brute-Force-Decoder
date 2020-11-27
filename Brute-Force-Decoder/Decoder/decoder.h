#ifndef DECODER_H
#define DECODER_H
#include "../Util/config.h"
#include "../main.h"
#include "../queue.h"
#include <semaphore.h>
void* decoder_main(void* args);

struct keyTextWrap{
	struct sizeWrapper* key;
	struct sizeWrapper* text;
};
#endif