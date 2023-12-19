#include <stdio.h>
#include "pm_heap.h"

int main() {

   pm_heap_init();
void* p1 = pm_malloc(2*1024*1024);
   if (p1) {
    printf("Allocated block of 2MB memory\n");
     }
  void* p2 = pm_malloc(3*1024*1024);
  if (p2) {
    printf("Allocated block of 3MB memory\n");
     }
  void* p3 = pm_malloc(3*1024*1024);
  if (p3) {
    printf("Allocated block of 3MB memory\n");
     }
 pm_free(p1);
   printf("Freeing 2MB memory block\n");
void* p6 = pm_malloc(3*1024*1024);
  if (!p6) {
    printf("Allocoting 3MB memory error: allocated block is larger than largest free block\n");
  } 
  else{
    printf("For 3MB allocation: Succesfully allocated\n");
  }
void* p7 = pm_malloc(2*1024*1024);
  if (!p7) {
    printf("Allocoting 2MB memory error(same size as largest free block): allocated block is larger than largest free block\n");
  }
  else{
    printf("For 2MB allocation(same size as largest free block): Succesfully allocated\n");
  }
void* p8 = pm_malloc(1*1024*1024);
  if (!p8) {
    printf("Allocoting 1MB memory error (smaller than the largest free block): allocated block is larger than largest free block\n");
  }
  else{
    printf("For 1MB allocation (smaller than the largest free block): Succesfully allocated\n");
  }

  return 0;
}
