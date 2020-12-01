#include "keyProducer.h"
#define TRD "Key Producer"

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

	print_id(TRD, "Created Thread");

	//Create key used to ccreate all other keys
	byte arr[args->size];
	//Clear array
	for(int i=1; i<args->size; i++){
		arr[i]=0;
	}
	arr[0]=args->start;
#if DBG
	char* buff=malloc(sizeof(char)*3*args->start+10);
	sprintf(buff, "0x");
	for(int i=0; i<args->size; i++){
		sprintf(buff, "%X ", arr[i]);
	}
	sprintf(buff, "\n");
	print_id(TRD, buff);
	free(buff);
#endif
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
	if(!halt)print_id(TRD, "Ran out of keys");
	print_id(TRD, "Ending Key Producer thread");
	return NULL;
}
