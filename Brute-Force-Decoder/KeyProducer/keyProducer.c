#include "keyProducer.h"

byte* key_generateKey(byte* arr, size_t size){
	return memcpy(calloc(size, sizeof(byte)), arr, size);
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
	while(byte_array_inc(arr, args->num, args->size)){
#if KEY_MAX!=0
		sem_wait(&semKeyMax);
#endif
		queue_push(keyQueue, key_generateKey(arr, args->size));
		sem_post(&semKey);
	}
	//Free the args and return
	free(args);
	return NULL;
}
