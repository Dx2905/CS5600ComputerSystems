#include <stdio.h>
#include "pm_heap.h"

int main() {
    pm_heap_init();

    // Allocate some memory and use it
    int* ptr1 = (int*) pm_malloc(sizeof(int));
    if (ptr1) {
        *ptr1 = 42;
        printf("Value of ptr1: %d\n", *ptr1);
    } else {
        printf("Error: out of memory\n");
    }

    int* ptr2 = (int*) pm_malloc(2 * sizeof(int));
    if (ptr2) {
        ptr2[0] = 1;
        ptr2[1] = 2;
        printf("Values of ptr2: %d, %d\n", ptr2[0], ptr2[1]);
    } else {
        printf("Error: out of memory\n");
    }

    // Free the memory allocated by ptr1
    pm_free(ptr1);
    printf("Free the memory of ptr1\n");

    // Allocate some more memory
    int* ptr3 = (int*) pm_malloc(sizeof(int));
    if (ptr3) {
        *ptr3 = 13;
        printf("Value of ptr3: %d\n", *ptr3);
         printf("Value of ptr1: %d\n", *ptr1);
    } else {
        printf("Error: out of memory\n");
    }

    // Free the memory allocated by ptr2
    pm_free(ptr2);
    printf("freeing the memory of ptr2\n");
    // Allocate some more memory and use it
    int* ptr4 = (int*) pm_malloc(4 * sizeof(int));
    if (ptr4) {
        ptr4[0] = 4;
        ptr4[1] = 5;
        ptr4[2] = 6;
	ptr4[3] = 8;
        printf("Values of ptr4: %d, %d, %d, %d\n", ptr4[0], ptr4[1], ptr4[2], ptr4[3]);
    } else {
        printf("Error: out of memory\n");
    }

    // Free the memory allocated by ptr3
    pm_free(ptr3);
    printf("Free the memory of ptr3\n");

    return 0;
}

