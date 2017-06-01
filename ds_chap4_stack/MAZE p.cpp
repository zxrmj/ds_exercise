//#include <iostream>
#include <stdio.h>
#include <stdlib.h>
//using namespace std; 


#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define Status signed int
#define OK 0
#define ERROR -1
#define OVERFLOW -2

typedef int SElemType;

typedef struct

{
	SElemType *base;
	SElemType *top;
	int stacksize;
}SqStack;

Status InitStack(SqStack &S)
{
	S.base = (SElemType *)
            malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if (!S.base)
		exit(OVERFLOW);
	S.top = S.base;
	S.stacksize=STACK_INIT_SIZE;
	return OK;
}

Status Push(SqStack &S, SElemType e)
{
	if (S.top - S.base >= S.stacksize)
	{
		S.base = (SElemType *)realloc(S.base,(S.stacksize + STACKINCREMENT) * sizeof(SElemType));
		if (!S.base)
			exit(OVERFLOW);
		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}
	*S.top++ = e;
	return OK;
}

Status Pop(SqStack &S , SElemType &e)
{
	if (S.top == S.base)
		return ERROR;
	e = *--S.top;
	return OK;
}
Status GetTop(SqStack &S,SElemType &e)
{
	if(S.top== S.base)
		return ERROR;
	e= *(S.top -1);
	return OK;
}

void main()
{
	SqStack new_s;
	int element,i;
	if (InitStack(new_s) == OVERFLOW)
		exit(OVERFLOW);
	for(i=0;1 < 10;i++)
		Push(new_s,i);
	while(GetTop(new_s,element) ==OK)
	{
		Pop(new_s,element);
		printf("%3d",element);
	}
	printf("\n");
	system("pause");
	return;
}