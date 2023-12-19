qtest: queuetest.o queue.o
	gcc -o qtest queuetest.o queue.o
queuetest.o: queuetest.c queue.h
	gcc -c queuetest.c
queue.o: queue.c queue.h
	gcc -c queue.c

