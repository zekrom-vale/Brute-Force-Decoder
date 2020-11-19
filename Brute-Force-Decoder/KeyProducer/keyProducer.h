#ifndef KEY_PRODUCER_H
#define KEY_PRODUCER_H
#include "byteArray.h"

typedef byte unsigned char;

struct keyArg{
	int num;
	int size;
};

char key_getChar(byte i);
char* key_toChar(byte arr[]);
byte* key_toByte(char str[]);
byte key_getByte(char i);
byte* key_generateKey(int size, long value);
#endif
