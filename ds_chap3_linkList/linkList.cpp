#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

// node structure
struct LNode
{
	ElemType data;
	LNode *next;

};

typedef LNode* LinkList;

// return type
#define STATUS bool
#define OK 0
#define ERROR 1

// link list initialization
STATUS CreateList(LinkList &L)
{
	// head node 's memory allocation
	L = (LinkList)malloc(sizeof(LNode));
	if (!L)
	{
		printf("overflow.");
		return ERROR;
	}
	L->next = NULL;
	return OK;
}

// returns list is empty or not
bool IsEmpty(LinkList &L)
{
	return !L->next;
}


//insert a node with data equal e before i¡¯th element into list L with header

STATUS InsertList(LinkList &L ,int i ,ElemType e)
{
	LinkList p = L; //point to head node
	int j = 0; // index of list.
	while (p && j < i - 1)
	{
		p = p->next;
		j++;
	}
	if (!p || j > i - 1)
	{
		return ERROR;
	}
	//memory allocation for insert element
	LinkList s = (LinkList)malloc(sizeof(LNode));
	if (!s)
	{
		printf("out of space.");
		return ERROR;
	}
	s->data = e;
	s->next = p->next;
	p->next = s;
}

LinkList find_previous(ElemType x, LinkList L)
{
	LinkList p;
	p = L;
	while ((p->next != NULL) && (p->next->data != x))
		p = p->next;
	return p;
}

// delete a node
STATUS DeleteList_L(LinkList &L, ElemType e)
{
	LinkList p = find_previous(e, L), q;
	if (p->next)
	{
		q = p->next;
		p->next = q->next;
		free(q);
	}
	printf("delete%2d\n", e);
	return OK;
}

// delete a node
STATUS DeleteList(LinkList &L, int i, ElemType &e)
{
	LinkList p = L;
	int j = 0;
	while (p->next && j < i - 1)
	{
		p = p->next;
		j++;
	}
	if (!p || j > i - 1)
	{
		return ERROR;
	}
	LinkList q = p->next;
	p->next = q->next;
	e = q->data;
	free(q);
	printf("delete%2d", e);
	return OK;
}


// traverse a linked list 
void DisplayList(LinkList &L)
{
	LinkList p = L->next;
	printf("link list:");
	if (!p)
	{
		printf("is empty");
	}
	while (p)
	{
		printf("%4d", p->data);
		p = p->next;
	}
	printf("\n");
	return;
}


STATUS GetElem(LinkList &L, int i, ElemType &e)
{ //L is a list with header
  //if the i¡¯th node is existent, get its value into e, return OK
  //otherwise return ERROR
	LinkList p = L->next; 
	int j = 0;
	while (p && j< i - 1)
	{
		p = p->next;
		++j;
	}
	if (!p || j > i - 1)
		return ERROR;
	e = p->data;
	return OK;
}

void DestroyList(LinkList &L)
{
	LinkList p, q;
	p = L->next;
	while (p)
	{
		q = p;
		p = p->next;
		free(q);
	}
	return;
}

void PrintLots(LinkList &L, LinkList &P) 
{
	int Counter; 
	LinkList Lpos, Ppos;
	Lpos = L->next;
	Ppos = P->next;
	Counter = 1; 
	while (Lpos != NULL && Ppos != NULL) 
	{
		if (Ppos->data == Counter++) 
		{ 
			printf("element %d at position %d in listL\n", Lpos->data, Ppos->data);
			Ppos = Ppos->next;
		} 
		Lpos = Lpos->next;
	}
}


int main()
{
	LinkList listL,listP;
	CreateList(listL);
	CreateList(listP);
	for (int i = 0; i < 10; i++)
	{
		InsertList(listL, i + 1, i);
	}
	InsertList(listP, 1, 1);
	InsertList(listP, 2, 3);
	InsertList(listP, 3, 4);
	InsertList(listP, 4, 6);
	DisplayList(listL);
	DisplayList(listP);
	printf("call function \"PrintLots\"\n");
	PrintLots(listL, listP);
	system("pause");
}


