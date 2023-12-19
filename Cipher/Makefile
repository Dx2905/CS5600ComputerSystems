cipher: cipher.o polybius.o
	gcc -o cipher cipher.o polybius.o
cipher.o: cipher.c polybius.h 
	gcc -c cipher.c
polybius.o: polybius.c polybius.h
	gcc -c polybius.c

