#include <stdio.h>

#define DATAFILE "prog11.txt"

int main() {
	FILE *fp;
	char ch;
	// open a text file for writing into it
	fp = fopen (DATAFILE, "w");
	printf("Enter data\n");
	while( (ch = getchar()) != EOF) {
		putc(ch, fp);
	}
	fclose(fp);
	// open a text file for reading from it 
	puts("--READING FROM FILE");
	fp = fopen(DATAFILE, "r");
	while( (ch = getc(fp)) != EOF)
		printf("%c", ch);
	fclose(fp);
}