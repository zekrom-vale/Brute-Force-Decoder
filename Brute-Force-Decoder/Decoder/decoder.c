#include "decoder.h"
void* decoder_main(void* v){
	struct decodeArgs* args=v;

	while(!halt){

		sem_wait(&semKey);
		struct sizeWrapper* wrp=queue_pop(keyQueue);
		byte* arr=wrp->arr;
		size_t size=wrp->size;
		free(wrp);
#if KEY_MAX!=0
		sem_post(&semKeyMax);
#endif
		//------------//
		//   Decode   //
		//------------//
		char* decoded="???????";  //Must end with endl (\0)

#if TEXT_MAX!=0
		sem_wait(&semTextMax);
#endif
		queue_push(textQueue, decoded);
		sem_post(&semText);
	}
	free(args);
	return NULL;
}