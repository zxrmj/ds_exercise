#include <stdio.h>
#include <stdlib.h>

/*
type define: element type of binary tree.
*/
typedef char TElement;
/*
a binary tree's node needs four members.
data:holds element data.
parent :point to parent node.
lchild :point to left child node.
rchild :point to right child node.
*/
struct TNode
{
	TElement data;
	TNode *parent;
	TNode *lchild;
	TNode *rchild;
};
/*
@type define : pointer of a node
*/
typedef TNode* BinaryTree;
/*
@type define : pointer of visit method function,
receive one void type void type and return void.
*/
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

// insert one node as T's child.
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
		printf("Already have two children");
		free(node);
		return false;
	}
}

// receive a root node,and an element,
// if find node'data equals to element,return it,
// else return NULL.
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

// Find root node.
TNode* GetRoot(BinaryTree T)
{
	while (T->parent)
		T = T->parent;
	return T;
}

// A visit method of tree traversal:
// print  char that the node held.
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
	// if empty
	if (!T)
		return;
	// print left child node (or subtree),and add left bracket before it.
	if (T->lchild)
	{
		printf("(");
		PrintExpTree(T->lchild);
	}
	// print operator.
	printf("%c", T->data);
	// print right child node (or subtree),and add right bracket after.
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

// create an algorithm expression tree(or subtree)
// by using method of inorder traverse
BinaryTree CreateExpTree(char* c, int &idx)
{
	// print expression of current function process
	int bg = idx; // begin index of expression
	int ed = idx; // end index of expression
	int cnt = 0;
	// find end.
	do
	{
		if (c[ed] == '(')
			cnt++;
		else if (c[ed] == ')')
			cnt--;
		else
			;
		ed++;
	} while (cnt != 0);
	
	printf("create a tree through (sub)expreesion:");
	for (int i = bg; i < ed; i++)
	{
		printf("%c", c[i]);
	}
	printf("\n");
	
	BinaryTree T;
	InitBiTree(T); // init tree

	// expression begin with left bracket
	if (c[idx] == '(')
	{
		printf("%3d%3c :find a left bracket,expression begin\n", idx, c[idx]);
		idx++; // ignore frist left bracket
	}
	else
	{
		exit(EXIT_FAILURE); // if the expression is not begin with left bracket,error
	}

	// insert left child (left operand or left expression)
	if (c[idx] == '(') // if current character is left bracket,recursive call "CreateExpTree" to create a new subtree as left child.
	{
		printf("%3d%3c :find another left bracket, call function\"CreateExpTree\" ,the node returns as left child.\n", idx, c[idx]);
		T->lchild = CreateExpTree(c, idx);
		T->lchild->parent = T;
	}
	else if (c[idx] >= '0' && c[idx] <= '9') // if current char is numeric,insert it into left child.
	{
		printf("%3d%3c :find left operand ,insert into left child.\n", idx, c[idx]);
		InsertNode(T, c[idx++]);
	}
	else // if current character is a letter ,need assignment for it.
	{
		int tmp = 0;
		printf("Enter the value of %c(less than 10):", c[idx++]);
		scanf_s("%d", &tmp);
		InsertNode(T, tmp + '0');
		printf("%3d%3c :find variate %c,and enter value: %d\n", idx - 1, c[idx - 1], c[idx - 1], tmp);
	}

	// insert operator
	printf("%3d%3c : find operator\n", idx, c[idx]);
	T->data = c[idx++];

	// insert right child
	if (c[idx] == '(') // if current character is left bracket,recursive call "CreateExpTree" to create a new subtree as right child.
	{
		printf("%3d%3c :find another left bracket, call function\"CreateExpTree\" ,the node returns as right child.\n", idx, c[idx]);
		T->rchild = CreateExpTree(c, idx);
		T->rchild->parent= T;
	}
	else if (c[idx] >= '0' && c[idx] <= '9') // if current char is numeric,insert it into right child.
	{
		printf("%3d%3c : find right operand ,insert into right child.\n", idx, c[idx]);
		InsertNode(T, c[idx++]);
	}
	else  // if current character is a letter ,need assignment for it.
	{
		int tmp = 0;
		printf("Enter the value of %c(less than 10):", c[idx++]);
		scanf_s("%d", &tmp);
		InsertNode(T, tmp + '0');
		printf("%3d%3c :find variate %c,and enter value: %d\n", idx - 1, c[idx - 1], c[idx - 1], tmp);
	}

	// expression end with right bracket
	if (c[idx++] == ')')
	{
		printf("%3d%3c : find a right bracket,expression ends,function return\n", idx - 1, c[idx - 1]);
		return T;
	}
	else
	{
		exit(EXIT_FAILURE); // if the expression is not end with right bracket,error
	}

}

// calculate the result of expresion tree
// by using method of postorder traverse
int CalculateExpTree(BinaryTree &T)
{
	int left = 0;
	int right = 0;
	// get left operand
	if (T->lchild)
	{
		// if current node's data is numeric,convert it to integer , and assign to left operand.
		if (T->lchild->data >= '0' && T->lchild->data <= '9')
		{
			left = T->lchild->data - '0';
		}
		// if current node's data is an operator,recursive call "CalculateExpTree" solve the subtree,result returned as left operand.
		else
		{
			
			left = CalculateExpTree(T->lchild);
			PrintExpTree(T->lchild);
			printf("= %d\n", left);
		}
	}
	// get right operand
	if (T->rchild)
	{
		// if current node's data is numeric,convert it to integer , and assign to right operand.
		if (T->rchild->data >= '0' && T->rchild->data <= '9')
		{
			right = T->rchild->data - '0';
		}
		// if current node's data is an operator,recursive call "CalculateExpTree" solve the subtree,result returned as right operand.
		else
		{
			right = CalculateExpTree(T->rchild);
			PrintExpTree(T->rchild);
			printf("= %d\n", right);
		}
	}
	// According to operator ，compute result.
	switch (T->data)
	{
	case '+':
		return left + right;
	case '-':
		return left - right;
	case '*':
		return left*right;
	case '/':
		// check of nonzero divisor.
		if (right == 0)
			exit(EXIT_FAILURE);
		else
			return (double)left / right;
	default:
		exit(EXIT_FAILURE);
	}

}

/*
给定一个算数表达式（例如 ((2*(a-1))+(3*b)) ），包含数字，变量和二元操作符，完成以下目标。
（1）创建用于表示表达式的二叉树，分支结点（有至少一个孩子的结点）包含操作数，并且叶子节点包含数字和变量。
（2）使用遍历算法计算二叉树所表示算式的结果(变量需要赋值）。
（3）将树重新序列化为串。
表达式:((2*(a-1))+(3*b))
二叉树:
        +
      /   \
     *      *
    / \     / \
   2   -   3   b
	  / \
	 a   1
*/

/*
Given an algorithm expression(e.g. ((2*(a-1))+(3*b)) ),contains numbers,vairiables,and binary operators,Complete the following goals.
1.Create binary tree to represent the expression that the operators are contained in the branch nodes(node has least one child),with the numbers and variables
in leaf nodes.
2.Calculate result of expression the binary tree represented by using traversal-algorithm(variables need assignment).
3.Serialize the tree back to a string.

expression:((2*(a-1))+(3*b))
bitree:
        +
      /   \
     *      *
    / \     / \
   2   -   3   b
	  / \
	 a   1
 
*/
int main()
{
	BinaryTree tree = NULL;
	char expression[] = "((2*(a-1))+(3*b))";  // use yourself expression instead of it.
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
