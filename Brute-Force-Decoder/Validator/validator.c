#include "validator.h"
#define TRD "Validator"

//Match the word given by WORD_REG
regex_t wordRegex;
//Stop if txt has invalid ascii defined in INVAL_REG
regex_t invalRegex;

void validator_init(){
	//Create Regex
	assert(!regcomp(&wordRegex, WORD_REG, REG_NOSUB|REG_ICASE|REG_EXTENDED));
	assert(!regcomp(&invalRegex, INVAL_REG, REG_NOSUB|REG_EXTENDED));
}

bool validator_validator(struct keyTextWrap* keyText){
	char* txt=keyText->text->arr;
	size_t txtSize=keyText->text->size;
	byte* key=keyText->key->arr;
	size_t keySize=keyText->key->size;

	if(txtSize!=strlen(txt))return false;

	//Find invalid characters
	if(regexec(&invalRegex, txt, 1, NULL, 0)!=REG_NOMATCH)return false;
	//Find the word
	return regexec(&wordRegex, txt, 1, NULL, 0)!=REG_NOMATCH;
}

void* validator_main(void* v){
	//Standard thread start
	struct decodeArgs* args=v;

	print_id(TRD, "Starting Thread");

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
			print(TRD, keyText);
		}
		//Clean up
		free(keyText->text->arr);
		free(keyText->text);
		free(keyText->key->arr);
		free(keyText->key);
		free(keyText);
	}

	print_id(TRD, "Ending Thread");

	//Standard thread end
	if(args)free(args);
	return NULL;
}