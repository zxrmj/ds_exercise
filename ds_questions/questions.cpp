#include <iostream>
using namespace std;

struct Node
{
	int data;
	Node* next;
};

void Insert(Node* &l, int e)
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->next = nullptr;
	node->data = e;
	l->next = node;
	l = node;
}

void Print(Node* l)
{
	while (l)
	{
		cout << l->data << endl;
		l = l->next;
	}
}

void Insert(Node* l, int i, int e)
{
	Node *p = l->next;
	int j = 0;
	Node *s;
	while (p && (j < i - 1))
	{
		p = p->next;
		j++;
	}
	if (!p || j > i)
		return;
	s = (Node*)malloc(sizeof(Node));
	s->data = e;
	s->next = p->next;
	p->next = s;
}

int Min(Node* l)
{
	int x = INT_MAX;
	Node *p = l->next;
	while (p)
	{
		if (p->data < x)
		{
			x = p->data;
		}
		p = p->next;
	}
	return x;
		
}

void Reverse(Node* l)
{
	Node* p, *q, *s;
	p = l->next;
	q = p->next;
	s = q->next;
	while (q)
	{
		q->next = p;
		p = q;
		q = s;
		if(s)
			s = s->next;
	}
	l->next->next = NULL;
	l->next = p;
	return;
}

Node* Reverse_Without(Node* l)
{
	Node* p, *q, *s;
	p = l;
	q = p->next;
	s = q->next;
	while (q)
	{
		q->next = p;
		p = q;
		q = s;
		if (s)
			s = s->next;
	}
	l->next = NULL;
	return p;
}

void DeleteNegativeNodes(Node* l)
{
	while (l)
	{
		if (l->next && l->next->data < 0)
		{
			Node *n = l->next;
			l->next = n->next;
			free(n);
		}
		else
		{
			l = l->next;
		}
	}
}

int main()
{
	Node* h = (Node*)malloc(sizeof(Node));
	Node* p = h;
	for (int i = 0; i < 5; i++)
	{
		Insert(p, rand()&1023 - 700);
	}
	cout << "Print.." << endl;
	Print(h->next);
	system("pause");
	DeleteNegativeNodes(h);
	cout << "Print again..." << endl;
	Print(h->next);
	system("pause");
}
