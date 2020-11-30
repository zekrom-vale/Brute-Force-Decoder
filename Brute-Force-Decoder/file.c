#include "file.h"

char* file_readAllCore(char* file, bool addNull, size_t* size){
	//Open the file in read bianary mode
	FILE *f = fopen(file, "rb");
	//Seek to the end
	assert(!fseek(f, 0, SEEK_END));
	//Get the last character postion
	*size = ftell(f);
	//Go back to the start
	assert(!fseek(f, 0, SEEK_SET));

	//Malloc the space for the string
	char *string = malloc(*size+(size_t)addNull);
	assert(string);
	//Read the entire file
	assert(fread(string, 1, *size, f)==*size);
	//Close the file
	assert(!fclose(f));

	if(addNull)string[++(*size)] = 0;
	return string;
}

/**
 * Reads all characters of a file and appends the null terminator `\0`
 * @param file The file as a string to read
 * @return a malloced location of memory containing an array of chars
 */
char* file_readAll(char* file){
	//Just provide a location for the function to use then discard
	size_t size=0;
	return file_readAllCore(file, false, &size);
}

/** 
 * Reads all characters of a file and does not append the null terminator as it may be included in the middel of the file
 * There is no meaning to each character in the file
 * @param file the file as a string to read
 * @return a wrapper containg a malloced array if chars `arr` and the size of that array `size`
 */
struct sizeWrapper* file_readAllRaw(char* file){
	//Create a spcae for the wrapper
	struct sizeWrapper* str=malloc(sizeof(struct sizeWrapper));
	//Save the char* to arr and pass size to store the size
	//This time we keep the value
	str->arr=file_readAllCore(file, true, &str->size);
	return str;
}