#include<stdio.h>
//#include<conio.h>

#define DATAFILE "prog12.txt"
struct employee
{
	char name[10];
	int age;
};

void main(){
	struct employee e;
	FILE *p, *q;
	p = fopen(DATAFILE, "a");
	q = fopen(DATAFILE, "r");
	printf("Enter Name and Age\n");
	scanf("%s %d", e.name, &e.age);
	fprintf(p,"%s %d\n", e.name, e.age);
	fclose(p);
	puts("--READING FROM FILE");
	do
	{
	    fscanf(q,"%s %d", e.name, &e.age);
	    printf("%s %d\n", e.name, e.age);
	} while(!feof(q));
	//getch();
}