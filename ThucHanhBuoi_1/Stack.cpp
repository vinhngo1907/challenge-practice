#include <stdio.h>
#include <conio.h>
#define Max_Element 100

typedef struct{
	int data[Max_Element];
	int size;
}Stack;

void MakeNull_Stack(Stack *S)
{
	S->size = 0;
}
int Empty_Stack(Stack *S)
{
	return S->size == 0;
}
void Push_Stack(Stack *S, int x)
{
	S->data[S->size] = x;
	S->size++;
}

int Top_Stack(Stack *S)
{
	return S->data[S->size-1];	
}

void Pop_Stack(Stack *S)
{
	S->size--;
}
