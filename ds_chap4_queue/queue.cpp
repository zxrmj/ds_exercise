#include <stdio.h>
#include <stdlib.h>

#define MAXQSIZE 100 // Max size
#define Status bool
#define OK true
#define OVERFLOW false
#define ERROR false

typedef int QElemType;
typedef struct
{
	QElemType *base;
	int front;
	int rear;
} SqQueue;

// Constructs an empty queue
Status  InitQueue(SqQueue &Q)
{
	Q.base = (QElemType *)malloc(MAXQSIZE * sizeof(QElemType));
	if (!Q.base)
		exit(OVERFLOW);
	Q.front = Q.rear = 0;
	return OK;
}

//Add an element to the rear of a queue
Status EnQueue(SqQueue &Q, QElemType e)
{
	if (Q.front == (Q.rear + 1) % MAXQSIZE)  //queue q is full
		return ERROR;
	Q.base[Q.rear] = e;                //inserts an element
	Q.rear = (Q.rear + 1) % MAXQSIZE; //move rear index
	return OK;
}

//Delete an element in the front of a queue
Status DeQueue(SqQueue &Q, QElemType &e)
/*if queue Q is not empty,delete an element in front of the queue */ 
{
	if (Q.rear == Q.front)     //if queue Q is empty
		return ERROR;
	e = Q.base[Q.front];
	Q.front = (Q.front + 1) % MAXQSIZE;  
	return OK;
}


//Caculate the length of a queue
int QueueLength(SqQueue Q)
{
	return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
}

bool IsEmpty(SqQueue &Q)
{
	return Q.rear == Q.front;
}

// main function
void main()
{
	int i, e;
	SqQueue new_q;
	InitQueue(new_q);
	for (i = 0; i<10; i++)
		EnQueue(new_q, i);
	while (!IsEmpty(new_q))
	{
		DeQueue(new_q, e);
		printf("%3d", e);
	}
	printf("\n");
	// if environment of visual studio ,the statement be low should be used 
	//otherwise should be comment because compiler will add it automatically.
	system("pause"); 
	return;
}






