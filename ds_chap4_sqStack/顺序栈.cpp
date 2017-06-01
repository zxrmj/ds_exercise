#include<stdio.h>
#include<stdlib.h>
#define STACK_SIZE 100
#define OK    1
#define ERROR 0

typedef int ElemType;
struct Stack
{
	ElemType elem[STACK_SIZE];
	int top;
};
typedef Stack SqStack;

int InitStack(SqStack *s)
{
	s = (SqStack*)malloc(sizeof(SqStack));
	if (s == NULL)
	{
		return ERROR;
	}
	s->top = -1;
	return OK;
}

int EmptyStack(SqStack* s)
{
	if (s->top == -1)
	{
		printf("Stack is empty\n");
		return OK;
	}
	else
	{
		printf("Stack is not empty\n");
		return ERROR;
	}
}

int GetTop(SqStack* s, ElemType *e)
{
	if (EmptyStack(s))
	{
		return ERROR;
	}
	else
	{
		*e = s->elem[s->top];
		return OK;
	}
}

int Push(SqStack* s, ElemType e)
{
	if (s->top == STACK_SIZE - 1)
	{
		printf("stack is full!\n");
		return ERROR;
	}
	else
	{
		s->top++;
		s->elem[s->top] = e;
		return OK;
	}
}

int Pop(SqStack* s, int *e)
{
	if (EmptyStack(s))
	{
		return ERROR;
	}
	else
	{
		*e = s->elem[s->top];
		s->top--;
		return OK;
	}
}

int PrintStack(SqStack* s)
{
	for (int i = 0; i < s->top; i++)
	{
		printf("%d ", s->elem[i]);
	}
	printf("\n");
	return OK;
}

int main(int, char**)
{
	int cord, e, x, y;
	SqStack*s = NULL;
	do
	{
		printf("\n Main Menu \n");
		printf("1 Create Stack\n");
		printf("2 Get Top Element\n");
		printf("3 Push\n");
		printf("4 Pop\n");
		printf("5 Print\n");
		printf("6 Exit\n");
		scanf("%d", &cord);
		switch (cord)
		{
		case 1:
		{
			InitStack(s);
			break;
		}
		case 2:
		{
			if (GetTop(s, &y))
			{
				printf("Stack Top  = [ %d ]\n", y);
			}
			break;
		}
		case 3:
		{
			printf("Please input push element.\n");
			scanf("%d", &e);
		}
		case 4:
		{
			if (Pop(s, &x))
			{
				printf("Pop stack = [ %d ]\n", x);
			}
			break;
		}
		case 5:
		{
			PrintStack(s);
			break;
		}
		case 6:
		{
			return 0;
		}
		default:
		{
			printf("Invaild input!\n");
			break;
		}
		}
	} while (1);
	return 0;
}