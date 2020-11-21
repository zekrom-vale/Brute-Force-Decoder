#ifndef KEY_PRODUCER_H
#define KEY_PRODUCER_H
#include "byteArray.h"
#include "../main.h"
#include <stdlib.h>

typedef unsigned char byte;

struct keyArg{
	int num;
	int size;
	int start;
};

byte* key_generateKey(byte* arr, size_t size);
void* key_main(void* v);
#endif
