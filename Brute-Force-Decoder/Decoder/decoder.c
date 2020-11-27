#include "decoder.h"

struct sizeWrapper* decode_decode(struct sizeWrapper* wrp){
	//Unwrap
	byte* arr=wrp->arr;
	size_t size=wrp->size;
	struct sizeWrapper* txt=malloc(sizeof(struct sizeWrapper));
	
	//Decode
	//txt->arr=text+\0
	//txt->size=size+1

	return txt;
}

void* decoder_main(void* v){
	//Standard thread start
	struct decodeArgs* args=v;

	//Loop until told to stop
	while(!halt){
		//Fetch the key to decode
		sem_wait(&semKey);
		struct sizeWrapper* wrp=queue_pop(keyQueue);
#if KEY_MAX!=0
		sem_post(&semKeyMax);
#endif
		//End fetch
		
		struct keyTextWrap* keyTextWrap=malloc(sizeof(struct keyTextWrap));
		keyTextWrap->text=decode_decode(wrp);
		keyTextWrap->key=wrp;

		//Put text into the queue for next
#if TEXT_MAX!=0
		sem_wait(&semTextMax);
#endif
		queue_push(textQueue, keyTextWrap);
		sem_post(&semText);
		//End put
	}

	//Standard thread end
	if(args)free(args);
	return NULL;
}