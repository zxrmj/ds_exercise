#include <stdio.h>
#include <stdlib.h>

#define Rows 5

// define function.
void print1d(int *ptr, int rows);


void main()
{
	int one[] = { 5,1,2,3,4 }; // init array by a list;
	print1d(&one[0], Rows); // call function we write.
	system("pause");
}

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
	for (i = 0; i < rows; i++) // i is a value for controlling loop
		printf("%8u%8d\n", assumedAddress + i, *(ptr + i)); // Print real address.
	    // printf("%8u%8d\n", assumedAddress + i, *(ptr + i)); // Print assumed address.

	return;
}
