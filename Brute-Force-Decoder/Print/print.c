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
	fprintf(OUT, "Found match:\n");
	print_key(OUT, keyText->key);
	fprintf(OUT, "%s\n", (char*)(keyText->text->arr));
	fprintf(OUT, "Terminating...\n");
}

void print_id(char* TRD, char* txt){
#if DBG
	if(TRD==NULL)fprintf(OUT, "%4d %20s \n", 1, "Main");
	else fprintf(OUT, "%4d %20s \n", pthread_self(), TRD);
	fprintf(OUT, txt);
#endif
}