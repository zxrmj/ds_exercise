#include <stdio.h>
#include <stdlib.h>

#define STACK_INIT_SIZE  100  
#define STACKINCREMENT   10   //increment
#define Status signed int
#define OK 1
#define ERROR 0
#define OVERFLOW -1

typedef int SElemType;

typedef struct
{
	SElemType *base;    //base address of stack
	SElemType *top;     //top address
	int stacksize;            //max size of stack 
} SqStack;

Status InitStack(SqStack &S)
{
	S.base = (SElemType *)
		malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if (!S.base)
		exit(OVERFLOW);
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return OK;
}

Status Push(SqStack &S, SElemType e)
{
	if (S.top - S.base >= S.stacksize)
	{
		S.base = (SElemType *)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(SElemType));
		if (!S.base)
			exit(OVERFLOW);
		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}
	*S.top++ = e;
	return OK;
}

Status Pop(SqStack &s, SElemType &e)
{//If Stack s is not empty, return the top element   
 //with e and return OK 
	if (s.top == s.base)     //stack s is empty
		return ERROR;
	e = *--s.top;
	return OK;
}

Status GetTop(SqStack &s, SElemType &e)
{//If stack s isn¡¯t empty£¬get the top element with e       
	if (s.top == s.base)      //If Stack s is empty
		return ERROR;
	e = *(s.top - 1);
	return OK;
}

void main()
{
	SqStack new_s;
	int element, i;
	if (!InitStack(new_s)) 
		exit(EXIT_FAILURE);
	for (i = 0; i < 10; i++)
		Push(new_s, i);
	while (GetTop(new_s, element) == OK)
	{
		Pop(new_s, element);
		printf("%3d", element);
	}
	printf("\n");
	system("pause");
	return;
}
