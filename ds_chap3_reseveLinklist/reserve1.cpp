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
	// Ԫ��ʼ�ղ��뵽r��next
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
	// h�ǵ�ǰ���һ��Ԫ�أ�Ҳ�ǵ��ú�ĵ�һ��Ԫ��
	h = p;
	while (true)
	{
		p = q;
		// ���pΪ���һ��Ԫ�ؽ���ѭ��
		if (!p->next)
		{
			break;
		}
		// Ѱ���������ڶ���Ԫ��
		while (p->next && p->next->next)
		{
			p = p->next;
		}
		
		
		LinkList temp;
		// tempָ�����һ��Ԫ��
		temp = p->next;
		// �����ڶ���Ԫ��nextָ����Ϊ��
		p->next = NULL;
		// p �����һ��Ԫ��
		p = temp; 
		r->next = p;
		// r�ƶ����ղ����Ԫ��
		r = p;
	}
	// pָ��תǰ�ڶ����ڵ㣬����ת�����ڶ����ڵ�
	r->next = p;
	// list�ڵ��ǵ�����һ���ڵ�
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