all: threadheap
threadheap: pm_heap.o main.o
	gcc -o threadheap pm_heap.o main.o
pm_heap.o: pm_heap.c pm_heap.h 
	gcc -c pm_heap.c
main.o: main.c pm_heap.h
	gcc -c main.c



