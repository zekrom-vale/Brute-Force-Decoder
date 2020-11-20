#include "queue.h"

/** 
 * front -> DUMMY -> [x] -> [x] -> [x] -> [x] <- end
 * front -> DUMMY <- end
 * front -> DUMMY <- end
 * front -> DUMMY -> [x] <- end
 * front -> DUMMY -> [x] -> [x] <- end
 * front -> DUMMY -> [x] <- end
 * front -> DUMMY <- end
 */


void queue_lockEnd(struct queue* this){
	assert(pthread_mutex_lock(&(this->endLock)));
}

void queue_lockFront(struct queue* this){
	assert(pthread_mutex_lock(&(this->frontLock)));
}

void queue_unlockEnd(struct queue* this){
	assert(pthread_mutex_unlock(&(this->endLock)));
}

void queue_unlockFront(struct queue* this){
	assert(pthread_mutex_unlock(&(this->frontLock)));
}

void queue_push(struct queue* this, void* data){
	//Create the data
	struct node* n=malloc(sizeof(struct node));
	n->data=data;
	n->next=NULL;
	//Add to the end
	queue_lockEnd(this);
	this->end->next=n;
	this->end=n;
	queue_unlockEnd(this);
}

void* queue_pop(struct queue* this){
	assert(this!=NULL);
	assert(this->front==this->DUMMY);
	if(this->front->next==NULL)return NULL;
	queue_lockFront(this);
	if(this->front->next->next==NULL){
		queue_lockEnd(this);
		this->end=this->DUMMY;
		queue_unlockEnd(this);
	}
	struct node* start=this->front->next;
	this->front->next=start->next;
	queue_unlockFront(this);
	void* data=start->data;
	free(start);
	return data;
}

struct queue* queue_init(){
	struct queue* q=malloc(sizeof(struct queue*));
	q->DUMMY=malloc(sizeof(struct node));
	q->DUMMY->data=NULL;
	q->DUMMY->next=NULL;
	q->front=q->DUMMY;
	q->end=q->DUMMY;
	assert(pthread_mutex_init(&(q->frontLock), NULL));
	assert(pthread_mutex_init(&(q->endLock), NULL));
	return q;
}
