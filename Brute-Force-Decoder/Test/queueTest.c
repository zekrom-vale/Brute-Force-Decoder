#include "../queue.h"
#include <pthread.h>

/** 
 * The test strings
 */
const char* str[]={
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"Hi",
	"adf",
	"adge",
	"5yhb",
	"",
	"fbrh",
	"\"",
	"3rf43"
};

#include <string.h>
#define TRD 6

/** 
 * Size of the string array
 */
size_t size=sizeof(str)/sizeof(str[0]);
/** 
 * An array of pointers to pointers of strings 
 */
char** strs[TRD];

/** 
 * Asserts the input of a queue
 * @param q the queue
 * @param val the val to test
 */
void assert_insert(struct queue* q, char* val){
	queue_push(q, str[i]);
	assert(q->end->data==val);//Yes comparing pointers
	assert(q->end->next==NULL);
}

/** 
 * Basic non-threaded queue functionality
 * We will know the order of the queue so we assert it
 */
void test_queue(){
	struct queue* q=queue_init();

	//Loop to ensure clearing works
	for(int j=0; j<4; j++){
		//Add strings
		for(int i=0; i<size; i++){
			assert_insert(q, str[i]);
		}
		//Remove strings
		for(int i=0; i<size; i++){
			struct node* n=q->front->next;
			//We need the front to be the dummy
			assert(q->front==q->DUMMY);
			assert(n->data==str[i]);
			//Test if the next node points to the correct string
			if(i<size-1)assert(n->next->data==str[i+1]);
			else assert(n->next==NULL);
			assert(str[i]==queue_pop(q));
			n=q->front;
			//Test if the shift worked
			if(i<size-1)assert(n->next->data==str[i+1]);
			else assert(n->next==NULL);
		}
		//Add a random string to test things
		if(i>2)assert(queue_pop(q)==NULL);
		else assert(queue_pop(q)==str[j-1]);
		if(i>=2){
			assert_insert(q, str[j]);
		}
	}

	queue_destroy(q);
}

void* test_lokedQueue_push(void* q){
	//Create a space to store the copy 
	char** cpy=malloc(size*sizeof(char));
	//Get the id of the array
	char* id=malloc(10*sizeof(char));
	sprintf(id, "%d", pthread_self());

	//Now copy and push
	for(int i=0; i<size; i++){
		//Copy
		cpy[i]=malloc(strlen(str[i])+10);
		strcpy(cpy[i], str[i]);
		//Append
		strcat(cpy[i], id);
		//Add to the queue
		queue_push(q, cpy[i]);
	}
	return cpy;
}

/** 
 * Looks up the string and removes it from the list
 * This way we know that everything is removed exactly and only once
 * @param c the exact string to look up
 */
void test_lookup(char* c){
	//Loop through each thread strings as they can mix up
	for(int i=0; i<TRD; i++){
		char** s=strs[i];
		//Loop for each in the thread array
		for(int j=0; j<size; j++){
			//Test if it points to the same location
			if(s[j]==c){
				//Free and set it to null
				free(s[j]);
				s[j]=NULL;
				return;
			}
		}
	}
	//Removed something twice
	assert(false);
}
/** 
 * Pops data from the queue and frees the string if it is not null
 * Does not look up the string in the strs array
 */
void* test_lokedQueue_pop_nl(void* v){
	//Loop for 2x as we may pop too quickely
	//Sure suncronization is posible but that takes time
	for(int i=0; i<size*2; i++){
		//Pop the data
		char* c=queue_pop(v);
		//If not NULL free it
		if(c)free(c);
	}
	return NULL;
}

/** 
 * Pop and verify the data was removed only once
 */
void* test_lockedQueue_pop(void* v){
	for(int i=0; i<size; i++){
		char* c=queue_pop(v);
		assert(c!=NULL);
		test_lookup(c);
		free(c);
	}
	return NULL;
}

/** 
 * Verify evertthing is removed
 */
void test_lockedQueue_assertend(){
	for(int i=0; i<TRD; i++){
		char** s=strs[i];
		for(int j=0; j<size; j++){
			assert(s[j]==NULL);
		}
	}
}

/** 
 * Tests the queue's locks by only poping on pushing at the same time
 * Pop and push does not occur at the same time
 */
void test_lockedQueue_seq(){
	//Create the tread array
	pthread_t trd[TRD];
	//Create the queue
	struct queue* q=queue_init();
	//Create the threads to push the values in an unknown order
	for(int i=0; i<TRD; i++){
		pthread_create(&(trd+i), NULL, test_lokedQueue_push, q);
	}
	//Wait to for the threads to return
	for(int i=0; i<TRD; i++){
		//Save the return to the strs array
		pthread_join(&(trd+i), strs[i]);
	}
	//Create the threads to pop the values in an unknown order
	for(int i=0; i<TRD; i++){
		pthread_create(&(trd+i), NULL, test_lockedQueue_pop, q);
	}
	//Wait for it to return
	for(int i=0; i<TRD; i++){
		pthread_join(&(trd+i), NULL);
	}

	//Verify everything was removed
	test_lockedQueue_assertend();

	//Destroy the queue
	queue_destroy(q);
}

/** 
 * Randomly adds and removes data from the linked list
 * This is to test mutual exclusion in an intence way such that there is no lost nodes
 * DOES NOT test if things are added/removed twice,
 * this is tested in the non-thread queue test and the squeuntal queue test
 */
void test_lockedQueue_rand(){
	//Create thread ids
	pthread_t trd_push[TRD];
	pthread_t trd_pop[TRD];
	//Init queue
	struct queue* q=queue_init();
	//Create the push threads
	for(int i=0; i<TRD; i++){
		pthread_create(&(trd_push+i), NULL, test_lokedQueue_push, q);
	}
	//Create the pop threads without waiting for the other threads to finish
	for(int i=0; i<TRD; i++){
		pthread_create(&(trd_pop+i), NULL, test_lokedQueue_pop_nl, q);
	}
	//Wait for the threads to end
	for(int i=0; i<TRD; i++){
		//Save the nodes added into strs
		pthread_join(&(trd_push+i), strs[i]);
	}
	for(int i=0; i<TRD; i++){
		pthread_join(&(trd_pop+i), NULL);
	}
	//Finish up collecting the extra nodes
	char* val=queue_pop(q);
	while(val!=NULL){
		free(val);
		val=queue_pop(q);
	}
	test_lockedQueue_assertend();
	queue_destroy(q);
}

#define TEST 8
int main(){
	//Simple queue test
	test_queue();
	//Thread queue tests
	//Need to loop as there is no gurentee that it will be the same every time it is run
	for(int i=0; i<TEST; i++){
		test_lockedQueue_seq();
		test_lockedQueue_rand();
	}
}