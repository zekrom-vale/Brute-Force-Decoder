#include "validator.h"
void* decoder_main(void* v){
	struct decodeArgs* args=v;

	while(!halt){
		sem_wait(&semText);
		queue_pop(textQueue);
#if TEXT_MAX!=0
		sem_post(&semTextMax);
#endif
		//Validate

		//If a match is found:
		//halt=true;
	}
	free(args);
	return NULL;
}