#include <stdio.h>
#include <pthread.h>
#include "pm_heap.h"

// Define the number of threads and allocations
#define NUM_THREADS 4
#define NUM_ALLOCS 10

// Global variable to keep track of the total number of allocated bytes
size_t total_allocated_bytes = 0;

// Thread function to allocate memory and write to it
void* thread_func(void* data) {
    int *number = (int*) data;
    int* ptrs[NUM_ALLOCS];
    for (int i = 0; i < NUM_ALLOCS; i++) {
        ptrs[i] = (int*) pm_malloc(sizeof(int));
        if (ptrs[i]) {
            *ptrs[i] = i;
            total_allocated_bytes += sizeof(int);
        }
       printf("Thread : %d Allocation pointer: %p Total allocated bytes:  %zu\n", number, ptrs[i], total_allocated_bytes);
    }
    for (int i = 0; i < NUM_ALLOCS; i++) {
        if (ptrs[i]) {
            pm_free(ptrs[i]);
            total_allocated_bytes -= sizeof(int);
        }
       printf("Thread: %d Free pointer: %p Total allocated bytes: %zu\n", number, ptrs[i], total_allocated_bytes);
    }
    return NULL;
}

int main() {
    pm_heap_init();

    // Create the threads
    pthread_t threads[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, thread_func, i+1);
    }

    // Wait for the threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Total allocated bytes: %zu\n", total_allocated_bytes);

    return 0;
}
