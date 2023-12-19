The directory contains:
Components of cipher code: cipher.c  polybius.c polybius.h

For multiple thread execution: cs5600multithread.c

For multiple process execution: cs5600multiprocess.c

For sentences text file: sentences.txt

For test case no sentence text file: No_sentences.txt

For makefile for all the codes: Makefile 

After running code we get .txt files in the directory with encrypted msg.

For multiple thread we will get .txt files in the format of: encryptthread_[sentencenumber].txt

For multiple process we will get .txt files in the format of: encryptedprocess_[sentencenumber].txt

Running instruction:

Run the makefile: $make

For multiple thread execution: $./multithread  [filename] 
                 In this case: $./multithread  sentences.txt

For multiple process execution: $./multiprocess  [filename] 
                 In this case: $./multiprocess  sentences.txt

In the cs5600multiprocess.c sentences are stored in an array and then are executed in new processes by creating child process using fork(). Cipher code is compiled in the code itself.

In the cs5600multithrread.c sentences are stored in an array and then executed where each sentence is encrypted using different thread. Cipher code is compiled in the code itself.








