#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define BAD_NUMBER_ARGS 1

/**
 * Parses the command line.
 *
 * argc: the number of items on the command line (and length of the
 *       argv array) including the executable
 * argv: the array of arguments as strings (char* array)
 * bits: the integer value is set to TRUE if bits output indicated
 *       outherwise FALSE for hex output
 *
 * returns the input file pointer (FILE*)
 **/
FILE *parseCommandLine(int argc, char **argv, int *bits) {
  if (argc > 2) {
    printf("Usage: %s [-b|-bits]\n", argv[0]);
    exit(BAD_NUMBER_ARGS);
  }

  if (argc == 2 &&
      (strcmp(argv[1], "-b") == 0 || strcmp(argv[1], "-bits") == 0)) {
    *bits = TRUE;
  } else {
    *bits = FALSE;
  }

  return stdin;
}

/**
 * Writes data to stdout in hexadecimal.
 *
 * See myxxd.md for details.
 *
 * data: an array of no more than 16 characters
 * size: the size of the array
 **/
void printDataAsHex(unsigned char *data, size_t size) {
 int k = 40;
 if(size == 16){
	for(int i = 0; i < size; i++) {
		if(i % 2 ==0) {
	    	 printf(" ");
		}
	printf("%02x", data[i]);
 	}
	k = 0;
 }
 else{
	for(int i = 0; i < size; i++) {
	 if(i % 2 ==0) {
		 printf(" ");
		 k--;
	 }
	 printf("%02x", data[i]);
	 k--;
	 k--;
	}
 }
 while( k > 0){
	printf(" ");
	k--;
 }
}

/**
 * Writes data to stdout as characters.
 *
 * See myxxd.md for details.
 *
 * data: an array of no more than 16 characters
 * size: the size of the array
 **/
void printDataAsChars(unsigned char *data, size_t size) {
	for(int j = 0; j < size; j++){
	 if(data[j] < 32 || data[j] > 126){
	  printf(".");
	 }
	 else{
	  printf("%c", data[j]);
	 }
	}
}
void printDataAsBits(unsigned char *data, size_t size){
	for(int l = 0; l < size; l++){
	 char bitOctet[8];
	 int dataString = data[l];
	 for(int m = 8; m > 0; m--){
	  if((dataString % 2) == 1){
		bitOctet[(m-1)] = '1';
	  }
	  else{
	 	bitOctet[(m-1)] = '0';
	  }
	  dataString = dataString / 2;
 	 }
	 printf(" ");
	 for(int n = 0; n < 8; n++){
	 printf("%c", bitOctet[n]);
	 }
	}
	int p = size;
	while(p < 6){
	 printf("         ");
	 p++;
	}
}
void readAndPrintInputAsHex(FILE *input) {
  unsigned char data[16];
  int numBytesRead = fread(data, 1, 16, input);
  unsigned int offset = 0;
  while (numBytesRead != 0) {
    printf("%08x:", offset);
    offset += numBytesRead;
    printDataAsHex(data, numBytesRead);
    printf("  ");
    printDataAsChars(data, numBytesRead);
    printf("\n");
    numBytesRead = fread(data, 1, 16, input);
  }
}

/**
 * Bits output for xxd.
 *
 * See myxxd.md for details.
 *
 * input: input stream
 **/
void readAndPrintInputAsBits(FILE *input) {
  unsigned char data[6];
  int numBytesRead = fread(data, 1, 6, input);
  int offset = 0;
  while(numBytesRead != 0) {
	printf("%08x:", offset);
	offset += numBytesRead;
	printDataAsBits(data, numBytesRead);
	printf("  ");
	printDataAsChars(data, numBytesRead);
	printf("\n");
	numBytesRead = fread(data, 1, 6, input);
  }
}

int main(int argc, char **argv) {
  int bits = FALSE;
  FILE *input = parseCommandLine(argc, argv, &bits);

  if (bits == FALSE) {
    readAndPrintInputAsHex(input);
  } else {
    readAndPrintInputAsBits(input);
  }
  return 0;
}
