#include "../queue.h"
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

/** 
 * Size of the string array
 */
size_t size=sizeof(str)/sizeof(str[0]);

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

/** 
 * Basic non-threaded queue functionality
 * We will know the order of the queue so we assert it
 */
void test_queue(){
	struct queue* q=queue_init();

	//Loop to ensure clearing works
	for(int j=0; j<2; j++){
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
	}

	queue_destroy(q);
}

int main(){
	//Simple queue test
	test_queue();
}