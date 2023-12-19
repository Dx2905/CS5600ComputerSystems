#ifndef QUEUE_H
#define QUEUE_H
typedef struct process {
  int id;
  char* name;
  int priority;
}process_t;

typedef struct queuenode {
  void* element;
  struct queuenode* next;
}queuenode_t;

typedef struct queue {
  queuenode_t* head;
  queuenode_t* tail;
}queue_t;

void enqueue(queue_t* queue, void* element);

void* dequeue(queue_t* queue);

process_t* dequeueProcess(queue_t* queue);

int qsize(queue_t* queue);

#endif
