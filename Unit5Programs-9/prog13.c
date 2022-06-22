// Fig. 11.2: fig11_02.c
// Creating a sequential file
#include <stdio.h>
#include <stdlib.h>

#define DATAFILE "clients.dat"

int main(void) {
  unsigned int account;  // account number
  char name[30];         // account name
  double balance;        // account balance

  FILE* cfPtr;  // cfPtr = clients.dat file pointer

  // fopen opens file. Exit program if unable to create file
  if ((cfPtr = fopen(DATAFILE, "w")) == NULL) {
    puts("File could not be opened");
    exit(0);
  }  // end if

  puts("Enter the account, name, and balance.");
  puts("Enter EOF to end input.");
  printf("%s", "? ");
  scanf("%d%29s%lf", &account, name, &balance);

  // write account, name and balance into file with fprintf
  while (!feof(stdin)) {
    fprintf(cfPtr, "%3d %-10s %.2f\n", account, name, balance);
    printf("%s", "? ");
    scanf("%d%29s%lf", &account, name, &balance);
  }  // end while
  puts("Done");
  fclose(cfPtr);  // fclose closes file
}  // end main