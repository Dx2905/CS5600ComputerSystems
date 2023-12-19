all: cipher multithread multiprocess

cipher: cipher.o polybius.o
	gcc -o cipher cipher.o polybius.o
cipher.o: cipher.c polybius.h 
	gcc -c cipher.c
polybius.o: polybius.c polybius.h
	gcc -c polybius.c
multithread: cs5600multithread.o 
	gcc -o multithread cs5600multithread.o
cs5600multithread.o: cs5600multithread.c  
	gcc -c cs5600multithread.c
multiprocess: cs5600multiprocess.o 
	gcc -o multiprocess cs5600multiprocess.o
cs5600multiprocess.o: cs5600multiprocess.c  
	gcc -c cs5600multiprocess.c

