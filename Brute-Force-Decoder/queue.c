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

/**
 * Locks the end of the queue
 * @param this the queue to lock
 */
void queue_lockEnd(struct queue* this){
	assert(pthread_mutex_lock(&(this->endLock)));
}

/**
* Locks the front of the queue
* @param this the queue to lock
*/
void queue_lockFront(struct queue* this){
	assert(pthread_mutex_lock(&(this->frontLock)));
}

/**
* Unlocks the end of the queue
* @param this the queue to unlock
*/
void queue_unlockEnd(struct queue* this){
	assert(pthread_mutex_unlock(&(this->endLock)));
}

/**
* Unlocks the start of the queue
* @param this the queue to unlock
*/
void queue_unlockFront(struct queue* this){
	assert(pthread_mutex_unlock(&(this->frontLock)));
}

/**
 * Adds an item to the queue
 * Must be a pointer from `malloc` or `static`
 * @param  this the queue to add to
 * @param data the value to add
 */
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

/**
* Removes an item from the queue
* @return the value of the removed node or `NULL` if none exist
*/
void* queue_pop(struct queue* this){
	assert(this!=NULL);
	assert(this->front==this->DUMMY);
	//Is there any data?
	if(this->front->next==NULL)return NULL;
	queue_lockFront(this);
	struct node* start=this->front->next;
	//If the node to remove is at the end
	if(start->next==NULL){
		//Lock the other side
		queue_lockEnd(this);
		//Update the end
		this->end=this->DUMMY;
		queue_unlockEnd(this);
	}
	this->front->next=start->next;
	queue_unlockFront(this);
	//Extract the data
	void* data=start->data;
	//Free the node
	free(start);
	return data;
}

/** 
 * Initalizes the queue
 */
struct queue* queue_init(){
	struct queue* q=malloc(sizeof(struct queue*));
	q->DUMMY=malloc(sizeof(struct node));
	q->DUMMY->data=NULL;
	q->DUMMY->next=NULL;
	//Set the front and end to the dummy
	q->front=q->DUMMY;
	q->end=q->DUMMY;
	//Create the locks
	assert(pthread_mutex_init(&(q->frontLock), NULL));
	assert(pthread_mutex_init(&(q->endLock), NULL));
	return q;
}

/**
 * Destroys the queue
 * @param this the queue to destroy
 */
void queue_destroy(struct queue* this){
	queue_lockEnd(this);
	queue_lockFront(this);
	//Loop through everything including the dummy node
	for(struct node* cur=this->front; cur!=NULL;){
		struct node* next=cur->next;
		//Free current
		free(cur);
		cur=next;
	}
	this->front=NULL;
	this->end=NULL;
	queue_unlockEnd(this);
	queue_unlockFront(this);
	//Destroy the locks
	pthread_mutex_destroy(&(this->endLock));
	pthread_mutex_destroy(&(this->frontLock));
	//free
	free(this);
}
