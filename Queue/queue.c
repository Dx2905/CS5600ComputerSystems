#include "queue.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void enqueue(queue_t* queue, void* element) {
    queuenode_t* new_node = (queuenode_t*)malloc(sizeof(queuenode_t));
    new_node->element = element;
    new_node->next = NULL;

    //Adding the new node
    if(queue->tail){
      queue->tail->next = new_node;
    }
    queue->tail = new_node;

    //If the queue is empty, update the head pointer
    if(!queue->head){
      queue->head = new_node;
    }
}
void* dequeue(queue_t* queue) {
    //Check if the queue is empty
    if(!queue->head){
      return NULL;
    }
    //Get the element from the front of the queue
    void* element = queue->head->element;
    queuenode_t* old_head = queue->head;
    queue->head = old_head->next;
    free(old_head);
    //If the queue is empty, update the tail
    if(!queue->head){
      queue->tail = NULL;
    }
    return element;
}



process_t* dequeueProcess(queue_t* queue) {
    // Check if the queue is empty
    if(!queue->head){
      return NULL;
    }
    //Find the process with the highest priority
    queuenode_t* current_node = queue->head;
    queuenode_t* highest_priority_node = current_node;
    while(current_node){
      if(((process_t*)current_node->element)->priority > ((process_t*)highest_priority_node->element)->priority){
        highest_priority_node = current_node;
        }
      current_node = current_node->next;
    }
    //Remove the highest priority process from the queue
    process_t* highest_priority_process = highest_priority_node->element;
    if(highest_priority_node == queue->head) {
        queue->head = highest_priority_node->next;
    }else{
        queuenode_t* current_node = queue->head;
        while(current_node->next != highest_priority_node){
            current_node = current_node->next;
        }
        current_node->next = highest_priority_node->next;
     }
    if(highest_priority_node == queue->tail){
      queue->tail = current_node;
    }
    free(highest_priority_node);
    return highest_priority_process;
}

int qsize(queue_t* queue){
    int count = 0;
    queuenode_t* current = queue->head;
    while (current) {
      count++;
      current = current->next;
    }
    return count;
}

