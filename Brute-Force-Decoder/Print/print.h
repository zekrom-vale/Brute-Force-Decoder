#ifndef PRINT_H_C
#define PRINT_H_C

#include <stdio.h>
#include "../Util/size.h"
#include "../Util/config.h"
#include "../Decoder/decoder.h"
typedef unsigned char byte;
void print_core(char* TRD, char* txt);
void print(char* TRD, struct keyTextWrap* keyText);
#if DBG
#define print_id(TRD, txt) print_core(TRD, txt)
#else
#define print_id(TRD, txt) ((void)0)
#endif

#endif