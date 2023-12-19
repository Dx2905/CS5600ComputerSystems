#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_SENTENCES 100
#define MAX_LENGTH 10000

char sentences[MAX_SENTENCES][MAX_LENGTH];
int sentence_count = 0;

int main(int argc, char *argv[]) {
  // Read the text file into the sentences array
  char filename[100];
  strcpy(filename, argv[1]);
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("Error: Unable to open file\n");
    return 1;
  }

  // Read the file and store each sentence
  char sentence[MAX_LENGTH];
  char c;
  int d = 0;

//  fgets(sentence, MAX_LENGTH, fp);
char *k=fgets(sentence,MAX_LENGTH, fp);
    if(k == NULL){
      printf("No sentences in the file \n");
      return 1;
    }
  char *p = strtok(sentence, ".!?");
  while (p != NULL) {
    strcpy(sentences[sentence_count], p);
    sentences[sentence_count][strlen(sentences[sentence_count]) - 1] = '\0';
    sentence_count++;
    p = strtok(NULL, ".!?");
  }

  fclose(fp);

  // Encrypt each sentence concurrently using separate processes
  pid_t pid;
  for (int i = 0; i < sentence_count-1; i++) {
    pid = fork();
    if (pid == 0) {
      // Child process
      char command[MAX_LENGTH];
      sprintf(command, "./cipher -e %s > encryptedprocess_%d.txt", sentences[i], i + 1);
      system(command);
      exit(0);
    } else if (pid > 0) {
      // Parent process
      continue;
    } else {
      // Error creating process
      printf("Error: Unable to create process for sentence %d\n", i + 1);
    }
  }

  // Wait for all child processes to finish
  int status;
  while (wait(&status) > 0) {}

  return 0;
}

