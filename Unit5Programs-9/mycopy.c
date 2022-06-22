/* Program to copy contents from one file to
 * another using command line arguments
 *
 * Usage: mycopy file1.dat file2.dat
 *
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  FILE *inFilePtr;  // input file pointer
  FILE *outFilePtr; // output file pointer
  int c;            // to hold characters read from the source file

  // check number of command-line arguments
  if (argc != 3) {
    puts("Usage: mycopy infile outfile");
    exit(-1);
  }
  // if input file cannot be opened
  if ((inFilePtr = fopen(argv[1], "r")) == NULL) {
    printf("File \"%s\" could not be opened\n", argv[1]);
    exit(-1);
  }
  // if output file can be opened
  if ((outFilePtr = fopen(argv[2], "w")) == NULL) {
    printf("File \"%s\" could not be opened\n", argv[2]);
    exit(-1);
  }
  // read and output characters
  while ((c = fgetc(inFilePtr)) != EOF)
    fputc(c, outFilePtr);

  fclose(outFilePtr); // close the output file
  fclose(inFilePtr);  // close the input file
} // end of main