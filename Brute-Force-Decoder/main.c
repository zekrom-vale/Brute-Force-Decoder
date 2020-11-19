struct queue* keyQueue=queue_init();
sem_t semKey;
sem_t semKeyMax;

struct queue* textQueue=queue_init();
sem_t semText;
sem_t semTextMax;

pthread_t keyProducers[N_KEYS];
pthread_t validators[N_VALS];
pthread_t decoders[N_DECS];

/**
 * Creates new threads
 * @param arr the array of pthreads to create
 * @param size the ammount of threads to create
 * @param f the function to call
 * @param args arguments to pass to the function as as
 */
void main_create(pthread* arr, int size, void* (f*)(void*), void* args[]){
		for(int i=0; i<size; i++){
			pthread_create(arr+i, NULL, f, args==NULL?NULL:args[i]);
		}
}

int main(){
	sem_init(&semKey, 0, 0);
	sem_init(&semKeyMax, 0, KEY_MAX);

	sem_init(&semText, 0, 0);
	sem_init(&semTextMax, 0, TEXT_MAX);

	//Create key producers
	//No need to keep te array as we will only pass the args
	struct keyArgs* keys[N_KEYS];
	for(int i=0; i<N_KEYS; i++){
		//Malloc the arguments
		keyArgs[i]=malloc(sizeof(struct keyArgs));
		keyArgs[i]->num=N_KEYS;
		keyArgs[i]->start=i;
		keyArgs[i]->size=KEY_SIZE;
	}
	main_create(&keyProducers, N_KEYS, &key_producer_main, keyArgs);

	//Create decoders
	main_create(&decoders, N_DECS, &decoder_main, NULL);
	//Create validators
	main_create(&validators, N_VALS, &validator_main, NULL);
	return 0;
}
