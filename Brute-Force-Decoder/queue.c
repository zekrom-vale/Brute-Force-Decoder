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

/** 
 * @param this the queue to loop through
 * @param f the function to execute per value
 * void f(int i, void* data)
 *	@param i the current index of the data
 *	@param data the data in the current node
 */
void queue_forEach(struct queue* this, void (*f)(int i, void* data)){
	int i=0;
	for(
		struct node* cur=this->front->next;
		cur!=NULL;
		cur=cur->next
	){
		f(i++, cur->data);
	}
}

/** 
 * Creates an itterator for the given queue
 * Automaticaly locks the queue until no nodes are left or queue_temrmenateIttorator is called
 * @param this the queue to create the ittorator for
 * 
 * struct queue* q=queue_init();
 * 
 * //Queue adding/removing stuff
 * 
 * //Make itterator
 * struct queue_ittorator* itt=queue_getIttorator(q);
 * while(queue_hasNext(itt)){
 *		int i=(int)queue_getNext(itt);
 *		printf("%d", i);
 *		if(i<0)break;
 * }
 * //Cleen up
 * queue_temrmenateIttorator(itt);
 */
struct queue_ittorator* queue_getIttorator(struct queue* this){
	assert(this!=NULL);
	struct queue_ittorator* itt=malloc(sizeof(struct queue_ittorator));
	itt->this=this;
	assert(this->front==this->DUMMY);
	queue_lockEnd(this);
	queue_lockFront(this);
	itt->lock=true;
	itt->cur=this->front->next;
	return itt;
}

/**
 * Terminates the lock
 * @param itt the itterator to stop and unlock
 * @return true if it was locked
 * @return false if it is unlocked
 */
bool queue_temrmenateIttorator(struct queue_ittorator* itt){
	if(!itt->lock)return false;
	queue_unlockEnd(itt->this);
	queue_unlockFront(itt->this);
	itt->lock=false;
	return true;
}

/**
 * Does the queue have a next node
 * @param itt the ittrator to check
 * @return true if there is more data
 * @return false if the current is NULL
 */
bool queue_hasNext(struct queue_ittorator* itt){
	assert(itt!=NULL);
	bool n=itt->cur!=NULL;
	if(!n)queue_temrmenateIttorator(itt);
	return n;
}

/**
 * Gets the next data
 * @param itt the itterator to get the next data
 * @return the value of the node
 */
void* queue_getNext(struct queue_ittorator* itt){
	assert(itt!=NULL);
	assert(itt->cur!=NULL);
	void* data=itt->cur->data;
	itt->cur=itt->cur->next;
	return data;
}