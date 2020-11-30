#include "print.h"

void print_key(FILE* file, struct sizeWrapper* key){
	fprintf(file, "0x");
	//Print the key in reverse order as it is stored that way
	for(int i=key->size-1; i>=0; i--){
		//Print as hex
		fprintf(file, "%X ", ((byte*)(key->arr))[i]);
	}
	fprintf(file, "\n");
}

void print(char* TRD, struct keyTextWrap* keyText){
	print_core(TRD, "Found match:\n");
	print_key(OUT, keyText->key);
	fprintf(OUT, "%s\n", (char*)(keyText->text->arr));
	print_core(TRD, "Terminating...\n");
}

void print_core(char* TRD, char* txt){
	if(TRD==NULL)fprintf(OUT, "%4d %20s ", 1, "Main");
	else fprintf(OUT, "%4lu %20s ", pthread_self(), TRD);
	fprintf(OUT, "%s\n", txt);
}