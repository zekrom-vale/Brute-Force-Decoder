#ifndef LOCKED_QUEUE_H
#define LOCKED_QUEUE_H
#include <pthread.h>

struct node{
  struct node* next;
  void* data;
};

static struct Stack* this;
static struct queue* _this(struct queue* that);

struct queue{
	struct queue (*_this)(struct Stack *);
	struct node* front;
	pthread_mutex_t frontLock;
	struct node* end;
	pthread_mutex_t endLock;
	void (*push)(void* data);
	void* (*pop)();
}

#endif
