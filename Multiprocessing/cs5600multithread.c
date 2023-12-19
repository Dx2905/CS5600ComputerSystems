#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_SENTENCES 100
#define MAX_LENGTH 10000

char sentences[MAX_SENTENCES][MAX_LENGTH];
int sentence_count = 0;

void *encrypt_sentence(void *arg) {
  int sentence_index = *((int *) arg);
  char command[MAX_LENGTH];
  sprintf(command, "./cipher -e %s > encryptthread_%d.txt", sentences[sentence_index], sentence_index + 1);
 
  system(command);
  return NULL;
}

int main(int argc, char *argv[]) {
  // Read the text file into the sentences array
  char filename[100];
  strcpy(filename, argv[1]);
  FILE *fp = fopen(filename, "r");
  if (fp == NULL)
{
    printf("Error: Unable to open file\n");
    return 1;
}

// Read the file and store each sentence
char sentence[MAX_LENGTH];
char c;
int d = 0;
  
char *k=fgets(sentence,MAX_LENGTH, fp);
      if(k == NULL){
      printf("No sentences in the file \n");  
      return 1;
       }
     char *p = strtok(sentence, ".!?");
    if (p == NULL) {
      printf("Error: No Termination markers found in the file.\n");
      return 1;
    }
    
   
    while (p != NULL) {
      strcpy(sentences[sentence_count], p);
      sentences[sentence_count][strlen(sentences[sentence_count]) - 1] = '\0';
      sentence_count++;
      p = strtok(NULL, ".!?");

     }


  fclose(fp);

  // Encrypt each sentence concurrently using separate threads
  pthread_t threads[MAX_SENTENCES];
  int sentence_indices[MAX_SENTENCES];
  for (int i = 0; i < sentence_count-1; i++) {
    sentence_indices[i] = i;
    pthread_create(&threads[i], NULL, encrypt_sentence, &sentence_indices[i]);
  }

  // Wait for all threads to finish
  for (int i = 0; i < sentence_count; i++) {
    pthread_join(threads[i], NULL);
  }

  return 0;
}

