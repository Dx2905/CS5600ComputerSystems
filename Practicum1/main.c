//#include "pm_heap.h"
//#include <stdio.h>
//#include <string.h>
//int main() {
//  // Allocate memory on the persistent memory heap.
//  // char* str1 = pm_malloc(10);
//  // char* str2 = pm_malloc(20);
//
//  char* str1 = pm_malloc(5 * 1024 * 1024);
//  char* str2 = pm_malloc(5 * 1024 * 1024);
//
//  if (str1 == NULL || str2 == NULL) {
//    printf("Error1: Failed to allocate memory.\n");
//    return 1;
//  }
//
//  // Write to the allocated memory.
//  strcpy(str1, "Hello");
//  strcpy(str2, " world!");
//
//  // Concatenate the two strings and print the result.
//  // char* str3 = pm_malloc(30);
//   char* str3 = pm_malloc(4);
//  if (str3 == NULL) {
//    printf("Error3: Failed to allocate memory.\n");
//    return 1;
//  }
//  strcpy(str3, str1);
//  strcat(str3, str2);
//  printf("%s\n", str3);
//
//  // Free the allocated memory.
//  pm_free(str1);
//  pm_free(str3);
//  char* str4 = pm_malloc(4 * 1024 * 1024);
//  if (str4 == NULL) {
//    printf("Error4: Failed to allocate memory.\n");
//    return 1;
//  }
//  // pm_free(str2);
//  // pm_free(str3);
//
//    pm_cleanup();
//
//  return 0;
//}

// working

#include <stdio.h>
#include "pm_heap.h"

int main() {
  pm_init();

  // Allocate memory for 10 pointers
  void* pointers[11];

  // Allocate more memory than available in physical memory
  // PM_HEAP_SIZE / PM_PAGE_SIZE must be less than or equal to 10 for this test
  for (int i = 0; i < 9; ++i) {
    pointers[i] = pm_malloc(PM_PAGE_SIZE);
    printf("Allocated memory for pointer %d: %p\n", i, pointers[i]);
    
  }
  // Access the memory, triggering page replacement if necessary
  for (int i = 0; i < 9; ++i) {
    int* accessed_ptr = (int*) pm_access(pointers[i]);
    *accessed_ptr = i;
      printf("memory of pointer %p\n", pointers[i]);
      printf("Accessed and wrote to pointer %d: %d\n", i, *accessed_ptr);
      print(i);

  }
pointers[9] = pm_malloc(PM_PAGE_SIZE);
printf("Allocated memory for pointer %d: %p\n", 9, pointers[9]);
pointers[10] = pm_malloc(PM_PAGE_SIZE);
printf("Allocated memory for pointer %d: %p\n", 10, pointers[10]);

int* accessed_ptr = (int*) pm_access(pointers[9]);
    *accessed_ptr = 9;
      printf("memory of pointer %p\n", pointers[9]);
      printf("Accessed and wrote to pointer %d: %d\n", 9, *accessed_ptr);


   accessed_ptr = pm_access(pointers[10]);
   *accessed_ptr = 10;
      printf("memory of pointer %p\n", pointers[10]);
      printf("Accessed and wrote to pointer %d: %d\n", 10, *accessed_ptr);
    for (int i = 0; i < 11; ++i) {
       int* accessed_ptr = (int*) pm_access(pointers[i]);
        printf("memory of pointer %p\n", pointers[i]);
       printf("Accessed pointer %d: %d\n", i, *accessed_ptr);
     }
  // Free the allocated memory
  for (int i = 0; i < 11; ++i) {
    pm_free(pointers[i]);
    // printf("Freed memory for pointer %d\n", i);
  }

  pm_cleanup();

  return 0;
}

//#include "pm_heap.h"
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//#define NUM_ALLOCS 10
////#define PAGE_SIZE 64
//
//int main() {
//  pm_init();
//
//  // Allocate more memory than the size of the persistent memory heap.
//  // This will trigger overcommitment.
//  char* strs[NUM_ALLOCS];
//  for (int i = 0; i < NUM_ALLOCS; i++) {
//    strs[i] = (char*)pm_malloc(PM_PAGE_SIZE * (i + 1));
//    if (!strs[i]) {
//      printf("Failed to allocate memory\n");
//      return EXIT_FAILURE;
//    }
//    // Write a string to the allocated memory.
//    char* str = "Hello, world!";
//    strcpy(strs[i], str);
//  }
//
//  // Free some memory.
//  pm_free(strs[0]);
//  pm_free(strs[1]);
//
//  // Access some memory to ensure it's still valid.
//  printf("%s\n", strs[2]);
//
//  // Allocate some more memory to trigger replacement of evicted pages.
//  char* new_str = (char*)pm_malloc(PM_PAGE_SIZE * 2);
//  if (!new_str) {
//    printf("Failed to allocate memory\n");
//    return EXIT_FAILURE;
//  }
//  // Write a string to the new allocated memory.
//  char* str = "Goodbye, world!";
//  strcpy(new_str, str);
//
//  // Access some of the previously evicted memory to ensure it's still valid.
//  printf("%s\n", strs[0]);
//
//  pm_cleanup();
//
//  return EXIT_SUCCESS;
//}


// for virtualmem2

//#include "pm_heap.h"
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//int main() {
//    // Initialize the page table
//    init_page_table();
//
//    // Open the backing store file
//    backing_store = fopen("backing_store.bin", "rb");
//    if (backing_store == NULL) {
//        fprintf(stderr, "Failed to open backing store file\n");
//        return 1;
//    }
//
//    // Allocate some memory from the program-managed heap with overcommitment
//    char *ptrs[10];
//    for (int i = 0; i < 10; i++) {
//        ptrs[i] = pm_malloc(PAGE_SIZE);
//        sprintf(ptrs[i], "This is pointer %d\n", i);
//    }
//
//    // Read and print the data from the allocated memory
//    for (int i = 0; i < 10; i++) {
//        printf("%s", ptrs[i]);
//    }
//
//    // Free the memory from the program-managed heap
//    for (int i = 0; i < 10; i++) {
//        pm_free(ptrs[i]);
//    }
//
//    // Close the backing store file
//    fclose(backing_store);
//
//    return 0;
//}

