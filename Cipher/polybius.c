#include "polybius.h"
#include<stdio.h>
#include<string.h>
#include<ctype.h>

// encode function for converting the plaintext to numbers
void pbEncode(const char *plaintext, struct polybius table){

	
  int i, row, col;
  for(i = 0; plaintext[i] != '\0'; i++){
		
    // conevrting to uppercase
    char letter = toupper(plaintext[i]);
		
    // searching in the table for the letter and charchters
		
    for(row = 0; row < 7; row++){
      for(col = 0; col < 5; col++){
        if(table.chartable[row][col] == letter){
	  // printing the row and column numbers
	  printf("%d%d", row+1, col+1);
	}
      }
    }
  }
}

// Decoding function for converting numbers to charchters(including special)
void pbDecode(const char *encodedtext, struct polybius table){


  int i;
  // iterating and taking two charchters at a time
  for(i = 0; encodedtext[i] != '\0'; i += 2){
    int row = encodedtext[i] - '0' - 1;
    int col = encodedtext[i+1] - '0' - 1;
    printf("%c", table.chartable[row][col]);
  }
}



