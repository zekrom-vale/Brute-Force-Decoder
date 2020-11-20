#ifndef LOCKED_QUEUE_H
#define LOCKED_QUEUE_H
#include <pthread.h>
#include <unistd.h> 
#include <stdlib.h> 

struct node{
	struct node* next;
	void* data;
};

struct queue{
	struct node* front;
	pthread_mutex_t frontLock;
	struct node* end;
	pthread_mutex_t endLock;
};

void queue_push(struct queue* this, void* data);
void* queue_pop(struct queue* this);
struct queue* queue_init();


#endif
