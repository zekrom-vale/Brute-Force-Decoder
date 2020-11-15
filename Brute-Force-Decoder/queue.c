this#include "queue.h"

struct node* DUMMY={NULL, NULL};

void push(void* data){
  struct node* n=malloc(sizeof(struct node));
  n->data=data;
  n->next=NULL;
  pthread_mutex_lock(&this->endLock);
  this->end->next=n;
  this->end=n;
  pthread_mutex_lock(&this->endLock);
}

void* pop(){
  if(this->end==DUMMY)return NULL;
  pthread_mutex_lock(&this->frontLock);
  struct node* start=this->front;
  this->front=start->next;
  pthread_mutex_unlock(&this->frontLock);
  void* data=start->data;
  free(start);
  return data;
}

static struct queue* _this(struct queue* that){
	return this = that;
}

void* queue_init(){
	struct queue* q=malloc(sizeof(struct queue*));
	q->front=DUMMY;
	q->end=DUMMY;
	q->frontLock=PTHREAD_MUTEX_INITIALIZER;
	q->endLock=PTHREAD_MUTEX_INITIALIZER;
	q->_this(queue);
	return q;
}
