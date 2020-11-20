#include "queue.h"

struct node* DUMMY={NULL, NULL};

void queue_push(struct queue* this, void* data){
	struct node* n=malloc(sizeof(struct node));
	n->data=data;
	n->next=NULL;
	pthread_mutex_lock(&(this->endLock));
	this->end->next=n;
	this->end=n;
	pthread_mutex_lock(&(this->endLock));
}

void* queue_pop(struct queue* this){
	assert(this!=NULL);
	if(this->front==DUMMY)return NULL;
	pthread_mutex_lock(&(this->frontLock));
	struct node* start=this->front;
	this->front=start->next;
	pthread_mutex_unlock(&(this->frontLock));
	void* data=start->data;
	free(start);
	return data;
}

struct queue* queue_init(){
	struct queue* q=malloc(sizeof(struct queue*));
	q->front=DUMMY;
	q->end=DUMMY;
	q->frontLock=PTHREAD_MUTEX_INITIALIZER;
	q->endLock=PTHREAD_MUTEX_INITIALIZER;
	return q;
}
