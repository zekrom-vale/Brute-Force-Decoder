#include "decoder.h"
void* decoder_main(void* v){
	struct decodeArgs* args=v;

	while(!halt){

		sem_wait(&semKey);
		byte* arr=queue_pop(keyQueue);
#if KEY_MAX!=0
		sem_post(&semKeyMax);
#endif
		//------------//
		//   Decode   //
		//------------//
		char* decoded="???????";

#if TEXT_MAX!=0
		sem_wait(&semTextMax);
#endif
		queue_push(textQueue, decoded);
		sem_post(&semText);
	}
	free(args);
	return NULL;
}