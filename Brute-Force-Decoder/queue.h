#ifndef LOCKED_QUEUE_H
#define LOCKED_QUEUE_H
#include <pthread.h>
#include <stdlib.h> 
#include <assert.h>
#include <stdbool.h>

struct node{
	struct node* next;
	void* data;
};

struct queue{
	struct node* DUMMY;
	struct node* front;
	pthread_mutex_t frontLock;
	struct node* end;
	pthread_mutex_t endLock;
};

struct sizeWrapper{
	size_t size;
	void* arr;
};

void queue_push(struct queue* this, void* data);
void* queue_pop(struct queue* this);
struct queue* queue_init();

struct queue_ittorator{
	bool lock;
	struct queue* this;
	struct node* cur;
};

struct queue_ittorator* queue_getIttorator(struct queue* this);
bool queue_temrmenateIttorator(struct queue_ittorator* itt);
bool queue_hasNext(struct queue_ittorator* itt);
void* queue_getNext(struct queue_ittorator* itt);

#endif
