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
		printf("已有两孩子节点");
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


// print algorithm expression tree,
void PrintExpTree(BinaryTree &T)
{
	if (!T)
		return;
	if (T->lchild)
	{
		printf("(");
		PrintExpTree(T->lchild);
	}
	printf("%c", T->data);
	if (T->rchild)
	{
		PrintExpTree(T->rchild);
		printf(")");
	}
	
}


// destory a binary tree
void DestroyBiTree(BinaryTree &T)
{
	PostOrderTraverse(T, free);
	T = NULL;
	return;
}


// 创建算数表达式二叉树
BinaryTree CreateExpTree(char* c, int &idx)
{
	BinaryTree T;
	InitBiTree(T); // 初始化树

	// 表达式以左括号开始
	if (c[idx] == '(')
	{
		idx++; // 忽略第一个左括号
	}
	else
	{
		exit(EXIT_FAILURE); // 如果未发现左括号，表达式字符串有误
	}

	// 插入左孩子
	if (c[idx] == '(') // 如果当前字符为左括号，即出现一个子算数表达式，创建一个新子树作为左孩子结点
	{
		T->lchild = CreateExpTree(c, idx);
		T->lchild->parent = T;
	}
	else if (c[idx] >= '0' && c[idx] <= '9') // 如果当前字符为数字，将该数字作为左孩子结点
	{
		InsertNode(T, c[idx++]);
	}
	else // 如当前为其他字符，则需要为该变量赋值
	{
		int tmp = 0;
		printf("Enter the value of %c(less than 10):", c[idx++]);
		scanf_s("%d", &tmp);
		InsertNode(T, tmp + '0');
	}

	// 插入操作符
	T->data = c[idx++];

	// 插入右孩子
	if (c[idx] == '(') // 如果当前字符为左括号，即出现一个子算数表达式，创建一个新子树作为右孩子结点
	{
		T->rchild = CreateExpTree(c, idx);
		T->rchild->parent = T;
	}
	else if (c[idx] >= '0' && c[idx] <= '9') // 如果当前字符为数字，将该数字作为右孩子结点
	{
		InsertNode(T, c[idx++]);
	}
	else  // 如当前为其他字符，则需要为该变量赋值
	{
		int tmp = 0;
		printf("Enter the value of %c(less than 10):", c[idx++]);
		scanf_s("%d", &tmp);
		InsertNode(T, tmp + '0');
	}

	// 表达式以右括号结尾
	if (c[idx++] == ')')
	{
		return T;
	}
	else
	{
		exit(EXIT_FAILURE); // 如果未发现右括号，表达式字符串有误
	}

}

int CalculateExpTree(BinaryTree &T)
{
	int left = 0;
	int right = 0;
	// 取得左孩子运算结果
	if (T->lchild)
	{
		// 如果为一个数字，该数字作为左操作数
		if (T->lchild->data >= '0' && T->lchild->data <= '9')
		{
			left = T->lchild->data - '0';
		}
		// 如果为一个操作符，则递归求得左子树的结果作为左操作数
		else
		{
			
			left = CalculateExpTree(T->lchild);
			PrintExpTree(T->lchild);
			printf("= %d\n", left);
		}
	}
	// 取得右孩子运算结果
	if (T->rchild)
	{
		if (T->rchild->data >= '0' && T->rchild->data <= '9')
		{
			right = T->rchild->data - '0';
		}
		else
		{
			right = CalculateExpTree(T->rchild);
			PrintExpTree(T->rchild);
			printf("= %d\n", right);
		}
	}
	// 根据操作符计算相应结果
	switch (T->data)
	{
	case '+':
		return left + right;
	case '-':
		return left - right;
	case '*':
		return left*right;
	case '/':
		if (right == 0)
			exit(EXIT_FAILURE);
		else
			return (double)left / right;
	default:
		exit(EXIT_FAILURE);
	}

}

int main()
{
	BinaryTree tree = NULL;
	char expression[] = "((2*(a-1))+(3*b))"; 
	printf("\nGiven Algorithm  Expression:\n");
	printf("%s\n", expression);
	int index = 0;
	tree = CreateExpTree(expression, index);
	
	printf("\nResult of Expression:\n");
	int result = CalculateExpTree(tree);
	PrintExpTree(tree);
	printf("=%d", result);
	printf("\n\nPreorder Traverse:\n");
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
