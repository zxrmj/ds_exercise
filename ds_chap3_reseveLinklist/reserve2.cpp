#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

struct LNode
{
	ElemType data;
	LNode* next;
};

typedef LNode* LinkList;

void ReserveList(LinkList &list)
{
	LinkList p = list;
	LinkList pFormer, pNext;
	pFormer = NULL;
	while (p != NULL)
	{
		pNext = p->next;
		p->next = pFormer;
		pFormer = p;
		p = pNext;
	}
	list = pFormer;
}

int main()
{
	LinkList list, p, q;
	list = (LinkList)malloc(sizeof(LNode));
	list->next = NULL;
	list->data = 0;
	p = list;
	for (int i = 1; i < 15; i++)
	{
		q = p;
		p = (LinkList)malloc(sizeof(LNode));
		p->data = i;
		p->next = NULL;
		q->next = p;
	}
	// show the list;
	p = list;
	printf("list before reserve:");
	while (p)
	{
		printf("%3d", p->data);
		p = p->next;
	}
	printf("\n");
	// reserve the list;
	ReserveList(list);

	// show the list after reserve;
	p = list;
	printf("list after  reserve:");
	while (p)
	{
		printf("%3d", p->data);
		p = p->next;
	}
	printf("\n");

	system("pause");


}