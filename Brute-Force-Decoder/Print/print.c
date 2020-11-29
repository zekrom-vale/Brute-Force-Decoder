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

void print(struct keyTextWrap* keyText){
	fprintf(stdout, "Found match:\n");
	print_key(stdout, keyText->key);
	fprintf(stdout, "%s\n", (char*)(keyText->text->arr));
	fprintf(stdout, "Terminating...");
}