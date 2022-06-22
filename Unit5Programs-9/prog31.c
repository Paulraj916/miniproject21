/* Simple program to illustrate 
 * how command line arguments are available 
 * to the C program through argc and argv
 */

#include <stdio.h>

int main(int argc, char *argv[]) {
  printf("%s: ", argv[0]);
  if(argc == 2)
    printf("The argument supplied is %s\n", argv[1]);
  else if(argc > 2)
    printf("Too many arguments supplied.\n");
  else
    printf("One argument expected.\n");
  
  printf("%s: '%s' is the last argument!\n",argv[0], argv[argc-1]);
  return 0;
}


