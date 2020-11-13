#ifndef LOCKED_QUEUE_H
#define LOCKED_QUEUE_H

struct node{
  struct node* next;
  void* data;
};

struct queue{
  struct node* front;
  struct node* end;
};

#endif
