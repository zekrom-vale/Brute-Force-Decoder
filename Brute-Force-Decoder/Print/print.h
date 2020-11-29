#ifndef PRINT_H_C
#define PRINT_H_C

#include <stdio.h>
#include "../Util/size.h"
#include "../Util/config.h"
#include "../Decoder/decoder.h"
typedef unsigned char byte;
void print_id(char* TRD, char* txt);
void print(struct keyTextWrap* keyText);
#endif