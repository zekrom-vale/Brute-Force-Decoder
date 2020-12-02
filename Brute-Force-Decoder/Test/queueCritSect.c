#include "../queue.h"
#include <pthread.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

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
	queue_push(q, val);
	assert(q->end->data==val);//Yes comparing pointers
	assert(q->end->next==NULL);
}

void* test_lokedQueue_push(void* q){
	//Create a space to store the copy 
	char** cpy=malloc(size*sizeof(char));
	//Get the id of the array
	char* id=malloc(20*sizeof(char));
	sprintf(id, "%lX", pthread_self());

	//Now copy and push
	for(int i=0; i<size; i++){
		//Copy
		cpy[i]=malloc(strlen(str[i])+30);
		strcpy(cpy[i], str[i]);
		//Append
		strcat(cpy[i], id);
		//Add to the queue
		queue_push(q, cpy[i]);
	}
	printf("%lX : Done coppying", pthread_self());
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
	printf("%lX : Done popping", pthread_self());
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
	printf("%lX : Done Popping", pthread_self());
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
		pthread_create(&(trd[i]), NULL, test_lokedQueue_push, (void*)q);
	}
	printf("Running Threads to push\n");
	//Wait to for the threads to return
	for(int i=0; i<TRD; i++){
		//Save the return to the strs array
		pthread_join((trd[i]), (void*)strs[i]);
	}
	printf("Passed Creation\n");
	//Create the threads to pop the values in an unknown order
	for(int i=0; i<TRD; i++){
		pthread_create(&(trd[i]), NULL, test_lockedQueue_pop, (void*)q);
	}
	printf("Running Threads to pop\n");

	//Wait for it to return
	for(int i=0; i<TRD; i++){
		pthread_join((trd[i]), NULL);
	}

	printf("Running End\n");

	//Verify everything was removed
	test_lockedQueue_assertend();

	printf("Destroying queue\n");

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
		pthread_create(&(trd_push[i]), NULL, test_lokedQueue_push, q);
	}
	//Create the pop threads without waiting for the other threads to finish
	for(int i=0; i<TRD; i++){
		pthread_create(&(trd_pop[i]), NULL, test_lokedQueue_pop_nl, q);
	}
	printf("Created Threads\n");
	//Wait for the threads to end
	for(int i=0; i<TRD; i++){
		//Save the nodes added into strs
		pthread_join((trd_push[i]), (void*)strs[i]);
	}
	for(int i=0; i<TRD; i++){
		pthread_join((trd_pop[i]), NULL);
	}
	//Finish up collecting the extra nodes
	printf("Cleaning Up\n");
	char* val=queue_pop(q);
	while(val!=NULL){
		free(val);
		val=queue_pop(q);
	}
	printf("Running End\n");
	test_lockedQueue_assertend();
	printf("Destroying queue\n");
	queue_destroy(q);
}

#define TEST 8
int main(){
	//Thread queue tests
	//Need to loop as there is no gurentee that it will be the same every time it is run
	for(int i=0; i<TEST; i++){
		test_lockedQueue_seq();
		printf("Pass Sequental Test\n");
		printf("================================\n");
		test_lockedQueue_rand();
		printf("Pass Random Test\n");
	}
}