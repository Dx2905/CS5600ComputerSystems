#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    queue_t* queue = (queue_t*)malloc(sizeof(queue_t));
    queue->head = NULL;
    queue->tail = NULL;

    //Creating process
    process_t* process1 = (process_t*)malloc(sizeof(process_t));
    process1->id = 1;
    process1->priority = 2;
    process1->name = "Process 1";

    process_t* process2 = (process_t*)malloc(sizeof(process_t));
    process2->id = 2;
    process2->priority = 3;
    process2->name = "Process 2";

    process_t* process3 = (process_t*)malloc(sizeof(process_t));
    process3->id = 3;
    process3->priority = 7;
    process3->name = "Process 3";

    process_t* process4 = (process_t*)malloc(sizeof(process_t));
    process4->id = 4;
    process4->priority = 4;
    process4->name = "Process 4";

    process_t* process5 = (process_t*)malloc(sizeof(process_t));
    process5->id = 5;
    process5->priority = 6;
    process5->name = "Process 5";

    process_t* process6 = (process_t*)malloc(sizeof(process_t));
    process6->id = 6;
    process6->priority = 1;
    process6->name = "Process 6";

    process_t* process7 = (process_t*)malloc(sizeof(process_t));
    process7->id = 7;
    process7->priority = 5;
    process7->name = "Process 7";
    
    // Adding the processes to the queue
    printf("Enqueueing Process1, Process2, Process3, Process4, Process5, Process6 and Process7 \n");
    enqueue(queue, process1);
    enqueue(queue, process2);
    enqueue(queue, process3);
    enqueue(queue, process4);
    enqueue(queue, process5);
    enqueue(queue, process6);
    enqueue(queue, process7);
    // Print the queue
    printf("Queue: \n");
    queuenode_t* current_node = queue->head;
    while(current_node){
      printf("%s (priority %d) (ID: %d) \n", ((process_t*)current_node->element)->name, ((process_t*)current_node->element)->priority,((process_t*)current_node->element)->id);
      current_node = current_node->next;
    }
    printf("\n");

    // Dequeue the highest priority process
    printf("dequeueProcess for dequeueing highest priority process\n");
    process_t* highest_priority_process = dequeueProcess(queue);
    printf("Dequeued process: %s (priority %d)\n", highest_priority_process->name, highest_priority_process->priority);

    // Print the queue after dequeueing highest priority process
    printf("The queue after dequeueing highest priority process \n");
    printf("Queue: \n");
    current_node = queue->head;
    while (current_node) {
      printf("%s (priority %d) (ID: %d )\n", ((process_t*)current_node->element)->name, ((process_t*)current_node->element)->priority,((process_t*)current_node->element)->id);
      current_node = current_node->next;
    }
    printf("\n");

    //Print the size of the queue
    printf("Size of the queue: %d\n", qsize(queue));
    printf("Dequeueing \n");   
    process_t* dequeued_process = dequeue(queue);
    printf("Dequeued process: %s (priority %d) (ID: %d )\n", dequeued_process->name, dequeued_process->priority,dequeued_process->id);
    printf("Printing the queue after dequeueing \n");
    printf("Queue: \n");
    current_node = queue->head;
    while (current_node) {
      printf("%s (priority %d) (ID: %d )\n", ((process_t*)current_node->element)->name, ((process_t*)current_node->element)->priority,((process_t*)current_node->element)->id);
    current_node = current_node->next;
    }
    printf("\n");
    //Print the size of the queue
    printf("Size of the queue: %d\n", qsize(queue));
  return 0;
}

