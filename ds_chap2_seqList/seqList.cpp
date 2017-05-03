//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define LIST_INIT_SIZE 100   //Maximun size of list
#define LISTINCREMENT  10    // Increment of size 

#define STATUS bool
#define OK 1
#define ERROR 0


typedef struct ElemType {
	int value;
	// double value;
	// float value;
	// long value;
	// ....could use other types replace type "int"


	bool operator==(const ElemType& elem)
	{
		return this->value == elem.value;
	}

	bool operator!=(const ElemType& elem)
	{
		return this->value != elem.value;
	}

}Element;


typedef struct {
	Element *elem;     // base address  
	int Length;        // length of the list 
	int ListSize;      // allocated length 
}SqList;

// Initialization
STATUS InitList(SqList &L) {

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

// Delete an element at position i
STATUS  Delete(SqList &L, int i, Element &e)
{
	if (i < 0 || i > L.Length || L.Length == 0)
		// i is illegal position
	{
		printf("%d is illegal position\n", i);
		return ERROR;
	}

	Element* p = &(L.elem[i - 1]);      // to be deleted 
	e = *p;                                  //save value to e
	Element* q = &(L.elem[L.Length - 1]);  //end of list 
	for (++p; p <= q; ++p)
		// move forward 
	{
		*(p - 1) = *p;
	}
	L.Length--; //decrease the length
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

// Find an element in SqList
int Find(SqList& L, Element& e)
{
	int i = 0;
	while (i < L.Length && L.elem[i] != e)
		i++;
	if (i < L.Length)
		return i + 1;   //find element e ,array index is always 1 less than position number						  
	else return 0;		//not find element e
}

// Find elements in SqList and print them to screen
void Find_Elements(SqList& L, Element& e)
{
	int i = 0;
	int n = 0; // number of elements equals to e

	while (i < L.Length)
	{
		if (L.elem[i] == e)
		{
			n++;
			if (n == 1)
			{
				printf("Elements equal to %d are stored in : \n", e.value);
			}
			printf(" % 4d\n", i + 1);

		}
		i++;
	}
	if (n > 0)
	{
		printf("There are %d elements equal to %d\n", n, e);
	}
	else
	{
		printf("There is no element equal to %d\n", e);
	}

}

void Show_All_Elements(SqList &list)
{
	Element elem;
	if (list.Length > 0)
	{
		printf("\n\===============================================\n");
		printf("\Information:\n");
		printf("\tThe length of list is %d\n", list.Length);
		printf("\n\tAll of elements in the list:\n");
		printf("-----------------------------------------------\n");
		printf("\tPos\tValue\n");
		for (int i = 0; i < list.Length; i++)
		{
			Get(list, i, elem);
			printf("\t%d\t%d\n", i + 1, elem.value);
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

void main()
{
	STATUS state;

	printf("This is a Sequence List(Sqlist) Testing Program.\n");
	printf("Press any key to create an empty Sqlist\n");
	system("pause");

	// Create a new SqList
	SqList list;
	Element elem;

	// Initialize the list
	state = InitList(list);
	if (state == ERROR)
		printf("Init Error.\n");
	else
		printf("\nInitialization is OK ,an empty Sqlist has created.\n");
	printf("The length of list is %d\n", list.Length);

	int count = 0;

	while (true)
	{
		printf("\n==================\n");
		printf("Choose function.\n\n");
		printf("1.Insert Element.\n");
		printf("2.Delete Element.\n");
		printf("3.Get Element.\n");
		printf("4.Find Element.\n");
		printf("5.Find Elements.\n");
		printf("6.Show All of Elements.\n");
		if (count == 63)
		{
			printf("9.Insert Random Elements.\n");
		}
		printf("0.Exit.\n");
		printf("==================\n");
		int func;
		printf("Enter:");
		scanf("%d", &func);
		getchar();
		switch (func)
		{

		case 1:
			// Try to Insert element :
		{


			fflush(stdin);
			system("cls");
			printf("Try to Insert an element into list\n");

			Show_All_Elements(list);

			printf("Enter value of the element you want to insert:");
			scanf("%d", &elem.value);
			printf("Enter which position you want to input this element:");
			int pos;
			scanf("%d", &pos);
			state = Insert(list, pos - 1, elem);
			if (state == OK)
			{
				printf("Element has inserted.The length of list now is %d\n", list.Length);
				count = (count | (1 << 0));
				break;
			}
			else
			{
				printf("Insertion failed.");
				break;
			}

		}
		case 2:
			// Try to Delete element:
		{


			fflush(stdin);
			system("cls");
			printf("Try to Delete an element in list\n");

			Show_All_Elements(list);

			printf("Enter which position you want to delete:");
			int pos;
			scanf("%d", &pos);
			state = Delete(list, pos, elem);
			if (state == OK)
			{
				printf("Element(Value is %d) has deleted.The length of list now is %d\n", elem.value, list.Length);
				count = (count | (1 << 1));
				break;
			}
			else
			{
				printf("Deletion failed.");
				break;
			}
		}
		case 3:
			// Try to Get element:
		{


			fflush(stdin);
			system("cls");
			printf("Try to Get an element in list\n");

			Show_All_Elements(list);

			printf("Enter which position you want to get:");
			int pos;
			scanf("%d", &pos);
			state = Get(list, pos - 1, elem);
			if (state == OK)
			{
				printf("Got element at position %d,its value is %d\n", pos, elem.value);
				count = (count | (1 << 2));
				break;
			}
			else
			{
				printf("Failed to get.\n");
				break;
			}
		}

		case 4:
			// Try to find element
		{


			fflush(stdin);
			system("cls");
			printf("Try to Find an element in list\n");

			Show_All_Elements(list);

			printf("Enter the value of element you want to find:");
			scanf("%d", &elem.value);
			state = Find(list, elem);
			if (state == OK)
			{
				printf("Element has founded.\n");
				count = (count | (1 << 3));
				break;
			}
			else
			{
				printf("Failed to find.");
				break;
			}
		}

		case 5:
			// Try to find elements
		{


			fflush(stdin);
			system("cls");
			printf("Try to Find elements in list\n");

			Show_All_Elements(list);

			printf("Enter the value of element you want to find:");
			count = (count | (1 << 4));
			scanf("%d", &elem.value);
			Find_Elements(list, elem);
			break;
		}

		case 6:
			// Show All of Elements.
		{
			count = (count | (1 << 5));
			fflush(stdin);
			system("cls");
			Show_All_Elements(list);
			break;
		}

		case 9:
			// Random insert.
		{

			if (count != 63)
			{
				srand(time(0));
				fflush(stdin);
				system("cls");
				printf("Building...\n");
				break;
			}
			else
			{
				srand(time(0));
				fflush(stdin);
				system("cls");
				printf("Insert some random elements (value from 1 to 20) into list\n");
				int n = 0;
				printf("Enter how many random element you want to insert(1-50):");
				scanf("%d", &n);
				if (n < 1 || n>50)
				{
					printf("%d is illegal number\n", n);
					break;
				}
				int l = list.Length;
				for (int i = l; i < l + n; i++)
				{
					elem.value = rand() % 20 + 1;
					Insert(list, i, elem);
				}

				Show_All_Elements(list);
				break;
			}


		}

		case 0:
		{
			return;
		}
		default:
			fflush(stdin);
			system("cls");
			printf("No such function.\n");
			break;
		}
		printf("Press any key to continue.\n");
		system("pause");
		fflush(stdin);
		system("cls");
	}
}








