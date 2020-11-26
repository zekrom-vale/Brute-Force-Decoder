#include "queue.h"
//This is private
void queue_inversionLock(struct queue* this);

/** 
 * front -> DUMMY -> [x] -> [x] -> [x] -> [x] <- end
 * front -> DUMMY <- end
 * front -> DUMMY <- end
 * front -> DUMMY -> [x] <- end
 * front -> DUMMY -> [x] -> [x] <- end
 * front -> DUMMY -> [x] <- end
 * front -> DUMMY <- end
 */

/*********************************
 *           LOCKS
 *********************************/

/**
 * Locks the end of the queue
 * @param this the queue to lock
 */
void queue_lockEnd(struct queue* this){
	assert(this);
	assert(!pthread_mutex_lock(&(this->endLock)));
}

/**
* Locks the front of the queue
* @param this the queue to lock
*/
void queue_lockFront(struct queue* this){
	assert(this);
	assert(!pthread_mutex_lock(&(this->frontLock)));
}

/**
* Locks the queue, helps prevent deadlock
* @param this the queue to lock
*/
void queue_lock(struct queue* this){
#if INVERSION_LOCK
	queue_inversionLock(this);
#else
	queue_lockFront(this);
	queue_lockEnd(this);
#endif
}

/**
 * EXPEREMENTAL
 * Swapps the given varable pointer with the other
 * WARNING Assumes that types are the same
 * 
 * ```
 * char* a;
 * char* b;
 * Ex: swap(&a, &&b);
 * ```
 * 
 * @param A The first pointer to swap
 * @param B The second pointer to swap
 */
void swap(void** A, void** B){
	void** T=B;
	*A=*B;
	*B=*T;
}

/**
 * Tries to aquire both locks, if it cannt it will wait in the locked queue without holding the other lock
 * This uses preemption, where others have priority
 * @param this the queue to aquire the lock for
 */
void queue_inversionLock(struct queue* this){
	assert(this);
	pthread_mutex_t* toLock=&(this->frontLock);
	pthread_mutex_t* locked=&(this->endLock);
	while(true){
		//Try to aquire the first lock
		assert(!pthread_mutex_lock(locked));
		//Try to aquire the other lock
		if(!pthread_mutex_trylock(toLock))return; //Aquired both locks return
		//Failed so unlock as we do not need it
		assert(!pthread_mutex_unlock(locked));
		//Swap the locks
		pthread_mutex_t* temp=toLock;
		toLock=locked;
		locked=temp;
		//Loop around to wait in the locked queue
	}
}

/**
* Unlocks the end of the queue
* @param this the queue to unlock
*/
void queue_unlockEnd(struct queue* this){
	assert(this);
	assert(!pthread_mutex_unlock(&(this->endLock)));
}

/**
* Unlocks the start of the queue
* @param this the queue to unlock
*/
void queue_unlockFront(struct queue* this){
	assert(this);
	assert(!pthread_mutex_unlock(&(this->frontLock)));
}

/**
* Unlocks the queue, helps prevent deadlock (well, not this one)
* @param this the queue to unlock
*/
void queue_unlock(struct queue* this){
	queue_unlockFront(this);
	queue_unlockEnd(this);
}

/*********************************
*             CORE
*********************************/

/**
 * Adds an item to the queue
 * Must be a pointer from `malloc` or `static`
 * @param  this the queue to add to
 * @param data the value to add
 */
void queue_push(struct queue* this, void* data){
	assert(this);
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
	assert(this);
	assert(this->front==this->DUMMY);
	//Is there any data?
	if(this->front->next==NULL)return NULL;
	queue_lockFront(this);
	struct node* start=this->front->next;
	//Set the first node to the next one
	this->front->next=start->next;

	//If the node to remove is at the end
	//Set the flag and run it later
	bool end=start->next==NULL;
	queue_unlockFront(this);
	if(end){
		//Lock the other side
		queue_lockEnd(this);
		//Update the end
		this->end=this->DUMMY;
		queue_unlockEnd(this);
	}
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
	//No need to lock as nothing else has access to the queue
	struct queue* q=malloc(sizeof(struct queue*));
	q->DUMMY=malloc(sizeof(struct node));
	q->DUMMY->data=NULL;
	q->DUMMY->next=NULL;
	//Set the front and end to the dummy
	q->front=q->DUMMY;
	q->end=q->DUMMY;
	//Create the locks
	mutext_init(&(q->frontLock));
	mutext_init(&(q->endLock));
	return q;
}

/**
 * Destroys the queue
 * @param this the queue to destroy
 */
void queue_destroy(struct queue* this){
	assert(this);
	queue_lock(this);
	//Loop through everything including the dummy node
	for(struct node* cur=this->front; cur!=NULL;){
		struct node* next=cur->next;
		//Free current
		free(cur);
		cur=next;
	}
	this->front=NULL;
	this->end=NULL;
	queue_unlock(this);
	//Destroy the locks
	pthread_mutex_destroy(&(this->endLock));
	pthread_mutex_destroy(&(this->frontLock));
	//free
	free(this);
}

/*********************************
*            LOOPS
*********************************/

/** 
 * @param this the queue to loop through
 * @param f the function to execute per value
 * void f(int i, void* data)
 *		@param i the current index of the data
 *		@param data the data in the current node
 *		@return true to continue
 *		@return false to stop
 */
void queue_forEach(struct queue* this, bool (*f)(int i, void* data)){
	assert(this);
	int i=0;
	queue_lockFront(this);
	struct node* cur=this->front->next;
	//The flag to keep track if it stoped
	bool flag=false;
	if(cur!=NULL){
		//While the next node is not null
		while(cur->next!=NULL){
			//Call the function then check the return value
			if(!f(i++, cur->data)){
				//If false exit
				flag=true;
				break;
			}
			//Continue to the next
			cur=cur->next;
		}
	}
	queue_unlockFront(this);
	if(flag)return;

	//Lock the end
	//Do it this way to only require one lock at a time
	queue_lockEnd(this);
	f(i, cur->data);
	queue_unlockEnd(this);
}

/*********************************
*       EXTRA ITTERATOR
*********************************/

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
	assert(this);
	struct queue_ittorator* itt=malloc(sizeof(struct queue_ittorator));
	itt->this=this;
	assert(this->front==this->DUMMY);
	queue_lock(this);
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
	assert(itt);
	if(!itt->lock)return false;
	queue_unlock(itt->this);
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
	assert(itt);
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
	assert(itt);
	assert(itt->cur);
	void* data=itt->cur->data;
	itt->cur=itt->cur->next;
	return data;
}