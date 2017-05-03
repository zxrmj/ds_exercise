#include <stdio.h>
#include <stdlib.h>

#define Rows 5

/*
print out a one-dimensional array using a pointer
this funciton need two parameters,frist one is the base address of array want to print,
and the second is number of rows want to print.
*/
void print1d(int *ptr, int rows)
{
	int i;

	// Assume base address of array is 200
	int assumedAddress = 200;
	printf("   Address   Contents:\n");
	for (i = 0; i<rows; i++)
		printf("%8u%8d\n", ptr + i, *(ptr + i));
	return;
}

void main()
{
	int one[] = { 5,1,2,3,4 };
	print1d(&one[0], Rows);
	system("pause");
}