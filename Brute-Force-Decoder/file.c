#include "file.h"

char* file_readAllCore(char* file, bool addNull, size_t* size){
	FILE *f = fopen(file, "rb");
	assert(!fseek(f, 0, SEEK_END));
	*size = ftell(f);

	assert(!fseek(f, 0, SEEK_SET));

	char *string = malloc(*size+(size_t)addNull);
	assert(string);
	assert(fread(string, 1, *size, f)==*size);
	assert(!fclose(f));

	if(addNull)string[++(*size)] = 0;
	return string;
}

char* file_readAll(char* file){
	size_t size=0;
	return file_readAllCore(file, false, &size);
}

struct sizeWrapper* file_readAllRaw(char* file){
	struct sizeWrapper* str=malloc(sizeof(struct sizeWrapper));
	str->arr=file_readAllCore(file, true, str->size);
	return str;
}