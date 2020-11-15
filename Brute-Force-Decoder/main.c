struct queue* keyQueue=queue_init();
sem_t semKey;
sem_t semKeyMax;

struct queue* textQueue=queue_init();
sem_t semText;
sem_t semTextMax;

pthread_t keyProducers[N_KEYS];
pthread_t validators[N_VALS];
pthread_t decoders[N_DECS];

void main_create(pthread* arr, int size, void* (f*)(void*), void* args){
		for(int i=0; i<size; i++){
			pthread_create(arr+i, NULL, f, args);
		}
}

int main(){
	sem_init(&semKey, 0, 0);
	sem_init(&semKeyMax, 0, KEY_MAX);

	sem_init(&semText, 0, 0);
	sem_init(&semTextMax, 0, TEXT_MAX);

	main_create(&keyProducers, N_KEYS, &key_producer_main, NULL);
	main_create(&validators, N_VALS, &validator_main, NULL);
	main_create(&decoders, N_DECS, &decoder_main, NULL);
	return 0;
}
