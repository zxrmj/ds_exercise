#define _CRT_SECURE_NO_WARNINGS // if using Visual Studio ,need this definition.

#include <stdio.h>
#include <stdlib.h>

/* Defination of Link List with head node  */
typedef struct Node * LinkedList;  //Pointer point to node.
struct Node          //Struct of a node.
{
	int data;
	LinkedList next;     // pointer point to next node.
};

/* Declaration of functions. */
LinkedList ReadLink();
void Attach(int e, LinkedList *pRear);
LinkedList Merge(LinkedList P1, LinkedList P2);
void PrintList(LinkedList P);

// Main Function.
int main()
{
	LinkedList L1, L2, LM;

	L1 = ReadLink();
	PrintList(L1);
	L2 = ReadLink();
	PrintList(L2);
	printf("The result is...\n");
	LM = Merge(L1, L2);
	PrintList(LM);
	system("pause");
	return 0;

}

// Read Data to link list.
// First input int is number of nodes.
// And input node's data one by one.
// Return head node of link list.
LinkedList ReadLink()
{
	printf("Read List:\n");
	LinkedList first, rear, t;
	int N, e;
	scanf("%d", &N); // input how many nodes want to insert.
	first = (Node*)malloc(sizeof(Node));// Temporary head node.
	first->next = NULL;
	rear = first;
	while (N--)
	{
		scanf("%d", &e);
		// Attach current node.
		Attach(e, &rear);
	}
	t = first;
	first = first->next;
	free(t);//Delete temp head node.
	return first;

}

//Attach node to rear.
void Attach(int e, LinkedList *pRear)
{
	LinkedList P;
	P = (Node*)malloc(sizeof(Node));        // Memory Allocation for new node.
	P->data = e;
	P->next = NULL;
	(*pRear)->next = P;      //Link new node.
	*pRear = P;
}

LinkedList Merge(LinkedList P1, LinkedList P2)//Merge two linked list.assume both list are stored in order.
{
	LinkedList first, rear, t;
	first = (Node*)malloc(sizeof(Node));    // Temporary head node.
	first->next = NULL;
	rear = first;
	while (P1&&P2)
	{
		if (P1->data < P2->data)  // P1's data is lesser.
		{
			Attach(P1->data, &rear);//Attach P1's node .
			P1 = P1->next;
		}
		else
		{
			Attach(P2->data, &rear);//Attach P1's node .
			P2 = P2->next; 
		}

	}

	/* Copy  remaining nodes to result polynomial */
	for (; P1; P1 = P1->next)    
		Attach(P1->data, &rear);
	for (; P2; P2 = P2->next)    
		Attach(P2->data, &rear);

	t = first;
	first = first->next;
	free(t);//Delete temporary head node.
	return first;
}

// Print polynomial.
void PrintList(LinkedList P)
{
	int flag = 0;        //Flag for checking is or is not the frist node.
	if (!P)
	{
		printf("0 0\n");
		return;
	}  //Empty List.

	while (P)
	{
		if (!flag)
			flag = 1;  //Frist node,do not print space.
		else
			printf(" ");   //print prepose space.
		printf("%d", P->data);
		P = P->next;
	}
	printf("\n");

}