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
	if (!list->next)
	{
		// empty
		return;
	}
	LinkList p, q, r, h;
	// 元素始终插入到r的next
	r = list;
	p = q = list->next;
	if (!p)
	{
		// only one element.
		return;
	}
	while (p->next)
	{
		p = p->next;
	}
	// h是当前最后一个元素，也是倒置后的第一个元素
	h = p;
	while (true)
	{
		p = q;
		// 如果p为最后一个元素结束循环
		if (!p->next)
		{
			break;
		}
		// 寻找链表倒数第二个元素
		while (p->next && p->next->next)
		{
			p = p->next;
		}
		
		
		LinkList temp;
		// temp指向最后一个元素
		temp = p->next;
		// 倒数第二个元素next指针置为空
		p->next = NULL;
		// p 是最后一个元素
		p = temp; 
		r->next = p;
		// r移动到刚插入的元素
		r = p;
	}
	// p指向反转前第二个节点，即翻转后倒数第二个节点
	r->next = p;
	// list节点是倒数第一个节点
	p->next = list;
	list->next = NULL;
	list = h;
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