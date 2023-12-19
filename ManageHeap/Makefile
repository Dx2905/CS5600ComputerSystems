all: heap test
test: pm_heap.o test.o
	gcc -o test pm_heap.o test.o
heap: pm_heap.o main.o  
	gcc -o heap pm_heap.o main.o
pm_heap.o: pm_heap.c pm_heap.h 
	gcc -c pm_heap.c
main.o: main.c pm_heap.h
	gcc -c main.c
test.o: test.c pm_heap.h
	gcc -c test.c


