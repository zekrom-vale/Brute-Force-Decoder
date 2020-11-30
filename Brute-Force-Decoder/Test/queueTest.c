#include "../queue.h"
#include <pthread.h>
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

size_t size=sizeof(str)/sizeof(str[0]);
char** strs[TRD];

void assert_insert(struct queue* q, val){
	assert(q->end->data==val);
	assert(q->end->next==NULL);
}

void test_queue(){
	struct queue* q=queue_init();

	for(int j=0; j<4; j++){
		for(int i=0; i<size; i++){
			queue_push(q, str[i]);
			assert_insert(q, str[i]);
		}

		for(int i=0; i<size; i++){
			struct node* n=q->front->next;
			assert(n==q->DUMMY);
			assert(n->next==str[i]);
			if(i<size-1)assert(n->next->next==str[i+1]);
			else assert(n->next==NULL);
			assert(str[i]==queue_pop(q));
		}
		if(i>2)assert(queue_pop(q)==NULL);
		else assert(queue_pop(q)==str[j-1]);
		if(i>=2){
			queue_push(q, str[j]);
			assert_insert(q, str[j]);
		}
	}

	queue_destroy(q);
}

void* test_lokedQueue_push(void* q){
	char** cpy=malloc(size*sizeof(char));
	char* id=malloc(10*sizeof(char));
	sprintf(id, "%d", pthread_self());
	for(int i=0; i<size; i++){
		cpy[i]=malloc(strlen(str[i])+10);
		strcpy(cpy[i], str[i]);
		strcat(cpy[i], id);
		queue_push(q, cpy[i]);
	}
	return cpy;
}

void test_lookup(char* c){
	for(int i=0; i<TRD; i++){
		char** s=strs[i];
		for(int j=0; j<size; j++){
			if(strcmp(s[j], c)==0){
				free(s[j]);
				s[j]=NULL;
				return;
			}
		}
	}
	assert(false);
}

void* test_lokedQueue_pop_nl(void* v){
	for(int i=0; i<size; i++){
		char* c=queue_pop(v);
		if(c)free(c);
	}
	return NULL;
}

void* test_lockedQueue_pop(void* v){
	for(int i=0; i<size; i++){
		char* c=queue_pop(v);
		assert(c!=NULL);
		test_lookup(c);
		free(c);
	}
	return NULL;
}

void test_lockedQueue_seq(){
	pthread_t trd[TRD];
	struct queue* q=queue_init();
	for(int i=0; i<TRD; i++){
		pthread_create(&(trd+i), NULL, test_lokedQueue_push, q);
	}
	for(int i=0; i<TRD; i++){
		pthread_join(&(trd+i), strs[i]);
	}
	for(int i=0; i<TRD; i++){
		pthread_create(&(trd+i), NULL, test_lockedQueue_pop, q);
	}
	for(int i=0; i<TRD; i++){
		pthread_join(&(trd+i), strs[i]);
	}

	for(int i=0; i<TRD; i++){
		char** s=strs[i];
		for(int j=0; j<size; j++){
			assert(s[j]!=NULL);
		}
	}
	queue_destroy(q);
}

void test_lockedQueue_rand(){
	pthread_t trd_push[TRD];
	pthread_t trd_pop[TRD];
	struct queue* q=queue_init();
	for(int i=0; i<TRD; i++){
		pthread_create(&(trd_push+i), NULL, test_lokedQueue_push, q);
	}
	for(int i=0; i<TRD; i++){
		pthread_create(&(trd_push+i), NULL, test_lokedQueue_pop_nl, q);
	}
	for(int i=0; i<TRD; i++){
		pthread_join(&(trd_push+i), NULL);
	}
	for(int i=0; i<TRD; i++){
		pthread_join(&(trd_pop+i), NULL);
	}
	char* val=queue_pop(q);
	while(val!=NULL){
		free(val);
		val=queue_pop(q);
	}
	queue_destroy(q);
}


int main(){
	//Simple queue test
	test_queue();
	test_lockedQueue_seq();
	test_lockedQueue_rand();
}