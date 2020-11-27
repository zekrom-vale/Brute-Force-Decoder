#include "validator.h"

bool validator_validator(struct keyTextWrap* keyText){
	char* txt=keyText->text->arr;
	size_t txtSize=keyText->text->size;
	byte* key=keyText->key->arr;
	size_t keySize=keyText->key->arr;

	//Validate
	return true||false;
}

void* validator_main(void* v){
	//Standard thread start
	struct decodeArgs* args=v;

	//Loop until told to stop
	while(!halt){
		//Retreve text
		sem_wait(&semText);
		//May need to send the size as well
		//We do need to send the key to print
		struct keyTextWrap* keyText=queue_pop(textQueue);
#if TEXT_MAX!=0
		sem_post(&semTextMax);
#endif
		//End retreve
		
		if(validator_validator(keyText)){
			halt=true;
			//Print
		}
		//Clean up
		free(keyText->text->arr);
		free(keyText->text);
		free(keyText->key->arr);
		free(keyText->key);
		free(keyText);
	}

	//Standard thread end
	if(args)free(args);
	return NULL;
}