struct queue* keyQueue;
struct queue* textQueue;

pthread_t keyProducers[N_KEYS];
pthread_t validators[N_VALS];
pthread_t decoders[N_DECS];

void main_create(pthread* arr, int size, void* (f*)(void*), void* args){
		for(int i=0; i<size; i++){
			pthread_create(arr+i, NULL, f, args);
		}
}

int main(){
	main_create(&keyProducers, N_KEYS, &key_producer_main, NULL);
	main_create(&validators, N_VALS, &validator_main, NULL);
	main_create(&decoders, N_DECS, &decoder_main, NULL);
	return 0;
}
