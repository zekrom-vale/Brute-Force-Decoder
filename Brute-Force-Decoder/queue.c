#include "queue.h"

struct queue* QUEUE={NULL, NULL};

void queue_push(void* data){
  struct node* n=malloc(sizeof(struct node));
  n->data=data;
  n->next=NULL;
  if(QUEUE->end==NULL){
    QUEUE->end=n;
    QUEUE->front=n;
  }
  else{
    QUEUE->end->next=n;
    QUEUE->end=n;
  }
}

void* queue_pop(){
  if(QUEUE->end==NULL)return NULL;
  void* data;
  struct node* start=QUEUE->front;
  if(start->next==NULL){
    data=start->data;
    free(start);
    QUEUE->front==NULL;
    QUEUE->end==NULL;
  }
  else{
    QUEUE->front=start->next;
    data=start->data;
    free(start);
  }
  return data;
}
