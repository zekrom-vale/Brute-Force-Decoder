#include "keyProducer.h"

struct sizeWrapper* key_generateKey(byte* arr, size_t size){
	//copy array
	byte* cpy=calloc(size, sizeof(byte));
	memcpy(cpy, arr, size);
	//wrap in wrapper
	struct sizeWrapper* wpr=malloc(sizeof(struct sizeWrapper));
	wpr->size=size;
	wpr->arr=cpy;
	return wpr;
}

/**
 * The main of the keyProducer thread
 * @param v the arguments (needs to be casted)
 * @return NULL
 */
void* key_main(void* v){
	//Get args
	assert(v!=NULL);
	struct keyArg* args=v;

	//Create key used to ccreate all other keys
	byte arr[args->size];
	arr[0]=args->start;
	//Increment then push to the queue
	//Only if halt is false and inc does not run out
	while(!halt&&byte_array_inc(arr, args->num, args->size)){
		//Push the generated key into the queue
#if KEY_MAX!=0
		sem_wait(&semKeyMax);
#endif
		queue_push(keyQueue, key_generateKey(arr, args->size));
		sem_post(&semKey);
		//End push
	}
	//Free the args and return
	free(args);
	return NULL;
}
