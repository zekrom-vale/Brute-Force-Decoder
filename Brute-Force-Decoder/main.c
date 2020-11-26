#include "main.h"

//Key Producer - Decoder Communication
struct queue* keyQueue;
sem_t semKey;
#if KEY_MAX!=0
sem_t semKeyMax;
#endif

//Decoder - Validator Communication
struct queue* textQueue;
sem_t semText;
#if TEXT_MAX!=0
sem_t semTextMax;
#endif

//Store refferences of threads
pthread_t keyProducers[N_KEYS];
pthread_t validators[N_VALS];
pthread_t decoders[N_DECS];

/**
 * The flag to stop all threads in the loop
 */
bool halt=false;

/**
 * The cypher text, wraped with size and a char* array
 * As `\0` can be used in the middle
 */
struct sizeWrapper* cypherText;

/**
 * Creates new threads
 * @param arr the array of pthreads to create
 * @param size the ammount of threads to create
 * @param f the function to call
 * @param args arguments to pass to the function as as
 */
void main_create(pthread_t* arr, int size, void* (*f)(void*), void* args[]){
		for(int i=0; i<size; i++){
			pthread_create(arr+i, NULL, f, args==NULL?NULL:args[i]);
		}
}

int main(){
	//Set the cypherText by reading the file
	cypherText=file_readAllRaw(CYPHER_FILE);
	//Init queues
	keyQueue=queue_init();
	textQueue=queue_init();

	//Init semaphores
	sem_init(&semKey, 0, 0);
#if KEY_MAX!=0
	sem_init(&semKeyMax, 0, KEY_MAX);
#endif

	sem_init(&semText, 0, 0);
#if TEXT_MAX!=0
	sem_init(&semTextMax, 0, TEXT_MAX);
#endif

	//Create key producers
	//No need to keep te array as we will only pass the args
	struct keyArg* keys[N_KEYS];
	for(int i=0; i<N_KEYS; i++){
		//Malloc the arguments
		keys[i]=malloc(sizeof(struct keyArg));
		keys[i]->num=N_KEYS;
		keys[i]->start=i;
		keys[i]->size=KEY_SIZE;
	}
	//Create producers
	main_create(&keyProducers, N_KEYS, key_main, keys);
	//Create decoders
	main_create(&decoders, N_DECS, decoder_main, NULL);
	//Create validators
	main_create(&validators, N_VALS, validator_main, NULL);
	//There is no reason to keep this main thread as we will not be joining
	return 0;
}
