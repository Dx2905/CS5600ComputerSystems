Gaurav 
CS5600 spring 2023
Assignment : Managing heap

The .tar file contains pm_heap.h ,pm_heap.c, main.c, test.c and readme.txt

Header file: pm_heap.h
Code managing heap: pm_heap.c
Implementation part: main.c
Testing for fragmentation: test.c

pm_heap.h: Defining heap size as 10MB
	   Static memory allocation to pm_heap	

pm_heap.c:  pm_heap_init()-> Initializing the pm_heap by creating initial free block
	    pm_malloc()-> Allocating memory for the required block of size from the static pm_heap
	    pm_free()-> Freeing the block of memory

main.c:   Implementation of the heap by allocating some memory and checking the working.
          Freeing the memory of ptr1 and then accessing ptr1 to check whether it's freed.

test.c:   For testing the code for fragmentation. 
	  First allocating 2MB, 3MB and 3MB block of memory, then freeing the 2MB block. Now trying 	  to allocate the 3MB block which is greater than largest free block of 2MB, the allocate 2MB 	  block which is equal to largest block, and then 1MB block which is less than largest block 	  size. 

For running the code: Run the Makefile: $make
                      For running the implementation run: $./heap
		      For testing part run: $./test				

