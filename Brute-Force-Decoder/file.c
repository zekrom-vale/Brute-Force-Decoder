#include "file.h"

char* file_readAll(char* file){
	FILE *f = fopen(file, "rb");
	assert(!fseek(f, 0, SEEK_END));
	size_t fsize = ftell(f);
	assert(!fseek(f, 0, SEEK_SET));

	char *string = malloc(fsize + 1);
	assert(string);
	assert(fread(string, 1, fsize, f)==fsize);
	assert(!fclose(f));

	string[fsize] = 0;
	return string;
}