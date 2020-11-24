#include "decoder.h"
void* decoder_main(void* v){
	//Standard thread start
	struct decodeArgs* args=v;

	//Loop until told to stop
	while(!halt){
		//Fetch the key to decode
		sem_wait(&semKey);
		struct sizeWrapper* wrp=queue_pop(keyQueue);
		//Unwrap
		byte* arr=wrp->arr;
		size_t size=wrp->size;
		//TODO pass to validator
		free(wrp);
#if KEY_MAX!=0
		sem_post(&semKeyMax);
#endif
		//End fetch

		//------------//
		//   Decode   //
		//------------//
		char* decoded="???????";  //Must end with \0

		//Put text into the queue for next
#if TEXT_MAX!=0
		sem_wait(&semTextMax);
#endif
		//TODO add key 
		queue_push(textQueue, decoded);
		sem_post(&semText);
		//End put
	}

	//Standard thread end
	if(args)free(args);
	return NULL;
}