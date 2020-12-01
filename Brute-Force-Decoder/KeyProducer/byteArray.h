#ifndef BYTE_ARRAY_H
#define BYTE_ARRAY_H

#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef unsigned char byte;
#define MAX 255

bool byte_array_inc(byte* arr, int inc, size_t size);

#endif
