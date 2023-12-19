Gaurav 
CS5600 spring 2023
Assignment : Practicum1

The .tar file contains pm_heap.h , virtualmem5.c, main.c and readme.txt

Header file: pm_heap.h
Code managing heap: virtualmem5.c
Implementation part: main.c


pm_heap.h: Defining heap size as 9 * page size that is 4kb
	   
pm_heap.c:  
	    pm_malloc()-> Allocating memory for the required block of size from the static pm_heap. Page replacement FIFO is applied if no free physical memory.
		          
	    pm_free()-> Freeing the block of memory. 
	    pm_access() -> accessing the memory. Page replacement if the page is on disk. 
            
main.c:   Implementation of memory management by allocating 9 pointers first and then assigning  value. After that allocating two more pointers as the physical memory is full so accordingly page replacement will happen and memory will be allocated. Then we are again accessing all the pointers again which will do page replacement accordingly if the page is in disk. 


For running the code: Run the Makefile: $make
                      For running the implementation run: $./heap
		      				


