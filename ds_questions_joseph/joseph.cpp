#include <stdio.h>
#include <stdlib.h>

#define N 30
#define K 6

struct Round
{
	int* base;
	int length;
	int current;
};

void Init(Round &r, int l, int e)
{
	r.base = (int*)malloc(l * sizeof(int));
	r.length = l;
	r.current = 0;
	for (int i = 0; i < l; i++)
		*(r.base + i) = e;
	return;
}

int& Current(Round &r)
{
	return *(r.base + r.current);
}

int& Next(Round &r)
{
	r.current = (r.current + 1) % r.length;
	return *(r.base + r.current);
}

int& At(Round &r, int idx)
{
	return *(r.base + idx);
}


int main()
{
	Round round;
	Init(round, N, 0);
	for (int i = 1; i <= N; i++)
	{
		int k = 0;
		while (true)
		{
			if (Current(round) == 0)
				k++;
			if (k < K)
				Next(round);
			else
				break;
		}
		Current(round) = i;
		printf("Round %3d:", i);
		for (int i = 0; i < N; i++)
		{
			printf("%3d", At(round, i));
		}
		printf("\n");
	}

	system("pause");
}