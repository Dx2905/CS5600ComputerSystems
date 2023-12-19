#include "polybius.h"
#include<stdio.h>
#include<string.h>
#include<ctype.h>

int main(int argc, char *argv[]){
	
  struct polybius t1;
  strcpy(t1.chartable[0], "ABCDE");
  strcpy(t1.chartable[1], "FGHIJ");
  strcpy(t1.chartable[2], "KLMNO");
  strcpy(t1.chartable[3], "PQRST");
  strcpy(t1.chartable[4], "UVWXY");
  strcpy(t1.chartable[5], "Z!@#$");
  strcpy(t1.chartable[6], ",<&.?");
  //checking for number of arguments
 // if(argc != 3){
 //   printf("Pls enter in the format: -d/-e text");
 //   return 1;
 // }
  //encoding an decoding depending on the input
  if(strcmp(argv[1], "-e") == 0){
    printf("Encoded Message : ");
   // char sentence[5000];
   // strcpy(
    pbEncode(argv[2], t1);
  } else if(strcmp(argv[1], "-d") == 0){
	   printf("Decoded Message : ");
	   pbDecode(argv[2], t1);
         }
return 0;
}
