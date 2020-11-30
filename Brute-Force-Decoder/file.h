#ifndef FILE_H
#define FILE_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Util/size.h"
#include <assert.h>

char* file_readAll(char* file);
struct sizeWrapper* file_readAllRaw(char* file);
#endif