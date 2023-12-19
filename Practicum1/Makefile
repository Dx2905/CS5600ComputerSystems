all: heap
heap: virtualmem5.o main.o
	gcc -o heap virtualmem5.o main.o
virtualmem5.o: virtualmem5.c pm_heap.h
	gcc -c virtualmem5.c
main.o: main.c pm_heap.h
	gcc -c main.c
clean:
	rm -f *.o heap
