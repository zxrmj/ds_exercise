#include <stdio.h> 
#include <stdlib.h>

#define MAX_SIZE 100

int sum(int[], int);

void main(void)
{
	int input[MAX_SIZE], answer;
	int i;
	for (i = 0; i<MAX_SIZE; i++)
		input[i] = i;
	answer = sum(input, MAX_SIZE);
	printf("The sum is :%d\n", answer);

	system("pause");
}

int sum(int list[], int n)
{
	int i;
	int itemsum = 0;
	for (i = 0; i<n; i++)
		itemsum += list[i];
	return itemsum;
}