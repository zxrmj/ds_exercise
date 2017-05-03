#include <stdio.h>
#include <stdlib.h>

typedef char TElement;
struct TNode
{
	TElement data;
	TNode *parent;
	TNode *lchild;
	TNode *rchild;
};
typedef TNode* BinaryTree;
typedef void(*VisitMethod)(void*);
//initialize a binaryTree
void InitBiTree(BinaryTree &T)
{
	// memory allocation of root node
	T = (TNode*)malloc(sizeof(TNode));
	if (!T)
	{
		printf("overflow!");
		exit(EXIT_FAILURE);
	}
	T->lchild = T->rchild = T->parent = NULL;
	return;
}

// insert one node as T'child.
bool InsertNode(BinaryTree &T,TElement e)
{
	TNode* node;
	node = (TNode*)malloc(sizeof(TNode));
	if (!node)
	{
		printf("overflow!");
		exit(EXIT_FAILURE);
	}
	node->lchild = node->rchild = node->parent = NULL;
	// if T has no children,insert into left child,
	// else if has left child ,insert into right child.
	if (!T->lchild)
	{
		T->lchild = node;
		node->data = e;
		node->parent = T;
		return true;
	}
	else if (!T->rchild)
	{
		T->rchild = node;
		node->data = e;
		node->parent = T;
		return true;
	}
	// else ,T has two children,insert failed.
	else
	{
		printf("ÒÑÓÐÁ½º¢×Ó½Úµã");
		free(node);
		return false;
	}
}

TNode* FindBiTree(BinaryTree &T, TElement e)
{
	if (T->data == e)
	{
		return T;
	}
	else
	{
		TNode* temp = NULL;
		if (T->lchild)
			temp = FindBiTree(T->lchild, e);
		if (T->rchild)
			temp = FindBiTree(T->rchild, e);
		if (temp)
			return temp;
	}
	
}

TNode* GetRoot(BinaryTree T)
{
	while (T->parent)
		T = T->parent;
	return T;
}

void GetChar(void* node)
{
	printf("%4c", ((TNode*)node)->data);
}

// if root node didn't initialized,return true.
bool IsEmpty(BinaryTree &T)
{
	return !T;
}

// delete one node ,return its parent.
TNode* DeleteNode(BinaryTree &T, TElement &e)
{
	TNode *p = T->parent;
	e = T->data;
	free(T);
	T = NULL;
	return p;
}


void PreOrderTraverse(BinaryTree &T, VisitMethod visit)
{
	if (!T)
		return;
	visit(T);
	PreOrderTraverse(T->lchild, visit);
	PreOrderTraverse(T->rchild, visit);
}

void InOrderTraverse(BinaryTree &T, VisitMethod visit)
{
	if (!T)
		return;
	InOrderTraverse(T->lchild, visit);
	visit(T);
	InOrderTraverse(T->rchild, visit);
}

void PostOrderTraverse(BinaryTree &T, VisitMethod visit)
{
	if (!T)
		return;
	PostOrderTraverse(T->lchild, visit);
	PostOrderTraverse(T->rchild, visit);
	visit(T);
}

void LevelOrderTraverse(BinaryTree &T, VisitMethod visit)
{
	if (!T)
		return;
	TNode* queue[20];
	queue[0] = T;
	int front = 0, back = 1;
	while (front != back)
	{
		visit(queue[front]);
		if (queue[front]->lchild)
			queue[back++] = queue[front]->lchild;
		if (queue[front]->rchild)
			queue[back++] = queue[front]->rchild;
		front++;
	}
}


// destory a binary tree
void DestroyBiTree(BinaryTree &T)
{
	PostOrderTraverse(T, free);
	T = NULL;
	return;
}

int main()
{
	BinaryTree tree = NULL;
	InitBiTree(tree);
	char ch = 'A';
	tree->data = ch;
	TNode* queue[20];
	queue[0] = tree;
	int front = 0, back = 1;
	while (ch != 'G')
	{
		
		if(queue[front]->lchild && queue[front]->rchild)
		{
			queue[back++] = queue[front]->lchild;
			queue[back++] = queue[front]->rchild;
			++front;
		}
		else
		{
			InsertNode(queue[front], ++ch);
			InsertNode(queue[front], ++ch);
		}
	}

	/*  Binary Tree:  
	*       A
	*      / \
	*     B   C
	*    / \ / \
	*   D  E F  G
	*/

	printf("Preorder Traverse:\n");
	PreOrderTraverse(tree, GetChar);
	printf("\nInorder Traverse:\n");
	InOrderTraverse(tree, GetChar);
	printf("\nPostorder Traverse:\n");
	PostOrderTraverse(tree, GetChar);
	printf("\nLevelOrder Traverse:\n");
	LevelOrderTraverse(tree, GetChar);
	printf("\n");
	DestroyBiTree(tree);
	system("pause");
}
