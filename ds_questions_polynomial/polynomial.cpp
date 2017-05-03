#define _CRT_SECURE_NO_WARNINGS // if using Visual Studio ,need this definition.

#include <stdio.h>
#include <stdlib.h>

/* Defination of Link List with head node  */

typedef struct PolyNode * Polynomial;  //Pointer point to node.
struct PolyNode          //Struct of a node.
{
    int coef;            // coefficient.
    int expon;           // exponent.
    Polynomial next;     // pointer point to next node.
};

/* Declaration of functions. */
Polynomial ReadPoly();
void Attach(int c,int e,Polynomial *pRear);
Polynomial Add(Polynomial P1,Polynomial P2);
void PrintPoly(Polynomial P);

// Main Function.
int main()
{
	Polynomial P1, P2, PS;

    P1 = ReadPoly();
	PrintPoly(P1);
    P2 = ReadPoly();
	PrintPoly(P2);
	printf("The result is...\n");
    PS = Add(P1,P2);
    PrintPoly(PS);
	system("pause");
    return 0;
	
}
// Read Polynomial to link list.
// First input value is number of terms.
// And input term(coefficient and exponent) one by one.
// Return the first term node of link list.
Polynomial ReadPoly()    
{
	printf("Read Poly:\n");
    Polynomial first,rear,t;
    int N,c,e;    
    scanf("%d",&N);

	first = (PolyNode*)malloc(sizeof(PolyNode));// Temporary head node.
    first->next = NULL;
    rear = first;
	scanf("%d %d",&c,&e);
    Attach(c,e,&rear);
	N--;
    while (N--)
    {
		scanf("%d %d",&c,&e);
		t = first;
		while(t->next)
		{
			if(t->next->expon < e)
				break;
			else
				t = t->next;
		}
        // Attach current term After node which expondent is greater then e and Before the node which expondent is lesser than e.
        Attach(c,e,&t);   
    }
    t = first;
	first = first->next;
	free(t);//Delete temp head node.
    return first;

}


void Attach(int c,int e,Polynomial *pRear)
{
    Polynomial P,N;
	N = (*pRear)->next;      // Save 
    P = (PolyNode*)malloc(sizeof(PolyNode));        // Memory Allocation for new node.
    P->coef = c;
    P->expon = e;
    P->next = N;
    (*pRear)->next = P;      //Link new node.
    *pRear = P;              
}

Polynomial Add(Polynomial P1,Polynomial P2)//Addition of two polynomials.
{
    Polynomial first,rear,t;
    int sum;
    first = (PolyNode*)malloc(sizeof(PolyNode));    // Temporary head node.
    first->next = NULL;
    rear = first;
    while(P1&&P2)
    {
        if (P1->expon == P2->expon)// Two expondents are equal.
        {
            sum = P1->coef + P2->coef;
            if(sum)    
				Attach(sum,P1->expon,&rear); //if sum equal to 0,neednot insert.
            P1 = P1->next;
            P2 = P2->next;
        }
        else if (P1->expon > P2->expon)      //else if expondent of P1 is greater.
        {
            Attach(P1->coef,P1->expon,&rear);//Attach node P1 to result polynomial.
            P1 = P1->next;
        }
        else
        {
            Attach(P2->coef,P2->expon,&rear);// else(expondent of P2 is greater)
            P2 = P2->next; //Attach node P2 to result polynomial.
        }

    }
	
    /* Copy  remaining nodes to result polynomial */
    for(;P1;P1=P1->next)    Attach(P1->coef,P1->expon,&rear);
    for(;P2;P2=P2->next)    Attach(P2->coef,P2->expon,&rear);

    t = first; 
	first = first->next; 
	free(t);//Delete temporary head node.
    return first;
}

// Print polynomial.
void PrintPoly(Polynomial P)    
{
    int flag=0;        // Flag to check is or is not the frist term.
    if(!P)
	{ 
		printf("0 0\n"); 
		return;
	}  //Empty polynomial.

    while(P)
    {
        if(!flag)    
			flag=1;  //Frist term,donot print space.
        else   
			printf(" ");   //print prepose space.
	    int coef = P->coef;
		int expon = P->expon;
		if(expon > 1)
			printf("%dx^%d ",P->coef,P->expon);
		else if(expon == 1)
			printf("%dx ",P->coef);
		else
			printf("%d ",P->coef);
        
		if(P->next)
			printf("+");
        P = P->next;
    }
    printf("\n");
     
}