/* Program to read from the data file
 * and find the average of the numbers 
 */ 

#include <stdio.h>
#include <stdlib.h> 

#define DATAFILE "prog15.dat"

int main() {
  FILE* fp;
  int n[50], i = 0;
  float sum = 0;
  if ((fp = fopen(DATAFILE, "r")) == NULL) {
    printf("Unable to open %s...\n", DATAFILE);
    exit(0);
  }
  printf("Reading numbers from %s\n", DATAFILE);
  while (!feof(fp)) {
    fscanf(fp, "%d ", &n[i]);
    printf("%d %d\n", i, n[i]);
    sum += n[i];
    i++;
  }
  fclose(fp);

  // if no data is available in the file
  if (i == 0)
    printf("No data available in %s", DATAFILE);
  
  float average = sum / i;
  printf("The average is %.3f for %d numbers\n", average, i);

  return 0;
}
