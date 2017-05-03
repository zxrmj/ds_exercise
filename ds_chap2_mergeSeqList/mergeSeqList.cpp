#include <stdio.h>
#include <stdlib.h>

#define LIST_INIT_SIZE 100 // Maximun size of list
#define LISTINCREMENT  10  // Increment of size 
#define STATUS int
#define OK 1
#define ERROR 0

typedef int Element;

typedef struct {
	Element   *elem;     //base address
	int    Length;       //length of the list
	int    ListSize;     //allocated length 
}SqList;

// Initialization
STATUS InitList(SqList &L)
{

	//Construct an empty list
	L.elem = (Element*)malloc(LIST_INIT_SIZE * sizeof(Element));

	if (!L.elem)
	{
		printf("Overflow!"); //Exception Handling
		return ERROR;
	}
	L.Length = 0;
	L.ListSize = LIST_INIT_SIZE;
	return OK;
};

// Insert an element at position i
STATUS Insert(SqList &L, int i, Element e)
{
	if (i < 0 || i > L.Length)
		// i is illegal position
	{
		printf("%d is illegal position\n", i + 1);
		return ERROR;
	}


	if (L.Length >= L.ListSize)
		//need more space
	{
		Element* newbase = (Element *)realloc(L.elem,
			(L.ListSize + LISTINCREMENT) * sizeof(Element));
		if (!newbase)
		{
			printf("Overflow!"); //Exception Handling
			return ERROR;
		}
		L.elem = newbase;   // new Base
		L.ListSize += LISTINCREMENT; // new Maximum value
	}

	Element* q = &(L.elem[i]);// position of insertion

	for (Element* p = &(L.elem[L.Length - 1]); p >= q; --p)
		// move backward
	{
		*(p + 1) = *p;
	}

	*q = e;
	L.Length++;
	return OK;
}

STATUS Get(SqList &L, int i, Element &e)
{
	if (i < 0 || i > L.Length || L.Length == 0)
		// i is illegal position
	{
		printf("%d is illegal position\n", i + 1);
		return ERROR;
	}
	Element* p = &(L.elem[i]);      // find ith element
	e = *p;                           //save value to e
	return OK;
}

void Show_All_Elements(SqList &list)
{
	Element elem;
	if (list.Length > 0)
	{
		printf("\n\===============================================\n");
		printf("Information:\n");
		printf("\tThe length of list is %d\n", list.Length);
		printf("===============================================\n");
		printf("All of elements in the list:\n");
		printf("-----------------------------------------------\n");
		printf("\tPos\tValue\n");
		printf("-----------------------------------------------\n");
		for (int i = 0; i < list.Length; i++)
		{
			Get(list, i, elem);
			printf("\t%d\t%d\n", i + 1, elem);
		}
		printf("===============================================\n");
	}
	else
	{
		printf("\n\===============================================\n");
		printf("\Information:\n");
		printf("\tThe length of list is %d\n", list.Length);
		printf("\tSqlist is empty.\n");
		printf("===============================================\n");
	}
}

STATUS Merge_List_Sq(SqList &La, SqList &Lb, SqList &Lc)
{
	// Pointers pa and pb point to the frist element of list A and B.
	Element* pa = La.elem;
	Element* pb = Lb.elem;

	// Initialize List C.
	Lc.Length = Lc.ListSize = La.Length + Lb.Length;
	Lc.elem = (Element*)malloc(Lc.ListSize * sizeof(Element));
	// Pointer pc points the frist element of list C.
	Element* pc = Lc.elem;

	// if Lc points to null , means memory overflow.
	if (!Lc.elem)
	{
		printf("Overflow!");
		return ERROR;
	}

	// Pointers point last element of list A and B.
	Element* pa_last = La.elem + La.Length - 1;
	Element* pb_last = Lb.elem + Lb.Length - 1;

	// Merge elements from List A and B to C,and make sure list C in order.
	// until pointer pa point to the last element of list A ,or pb point to  the last element of list B.
	while (pa <= pa_last && pb <= pb_last)
	{
		// dereference pa and pb,compare two values,
		// the lesser one will be copied to pc's current address,
		// and move pointer pa or pb to next element,
		// then move pointer pc to next element.
		if (*pa <= *pb)
		{
			*pc++ = *pa++;
		}
		else
		{
			*pc++ = *pb++;
		}

	}

	// copy the remaining elements of listA and listB to listC.
	while (pa <= pa_last)
		*pc++ = *pa++;
	while (pb <= pb_last)
		*pc++ = *pb++;
	// finished
	return OK;
}

int main()
{
	// Create three list.
	SqList listA, listB, listC;

	// Initialize list A and B.
	InitList(listA);
	InitList(listB);

	// Insert some elements into A and B.
	// A and B are both orderd list.
	// A:1,3,5,7....19
	// B:2,4,9,11...20
	for (int i = 1; i <= 10; i++)
	{
		Insert(listA, i - 1, i * 2 - 1);
		Insert(listB, i - 1, i * 2);
	}

	// now merge list A and B to a new list C!
	Merge_List_Sq(listA, listB, listC);

	// show list C.
	Show_All_Elements(listC);


	system("pause");
	// end.
}
