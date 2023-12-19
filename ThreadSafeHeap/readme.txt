Gaurav 
CS5600 spring 2023
Assignment : thread safe heap

The .tar file contains pm_heap.h ,pm_heap.c, main.c and readme.txt

Header file: pm_heap.h
Code managing heap: pm_heap.c
Implementation part: main.c


pm_heap.h: Defining heap size as 10MB
	   Static memory allocation to pm_heap	

pm_heap.c:  pm_heap_init()-> Initializing the pm_heap by creating initial free block
	    pm_malloc()-> Allocating memory for the required block of size from the static pm_heap.
		          Use of mutex in critical section to make it thread safe.
	    pm_free()-> Freeing the block of memory. Use of mutex in the critical section to make it thread safe.
	

main.c:   Implementation of the heap by creating some threads. In thread we are allocating some memory to some pointers then freeing them of memory.
          Counter total_allocated_bytes that will keep track of the total allocated bytes in the process. Printing the thread and the pointer in that thread to whom memory is being allocated or the they are being free of memory and printing total bytes allocated till now. 



For running the code: Run the Makefile: $make
                      For running the implementation run: $./threadheap
		      				

