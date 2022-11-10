#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENTS 100
typedef int ElementType;
typedef struct{
	ElementType data[MAX_ELEMENTS];
	int size;
}List;

void makenull_List(List *L)
{
	L->size = 0;
}

void pushback(List *L, int x)
{
	L->data[L->size] = x;
	L->size++;
}

ElementType element_at(List *L, int i)
{
	return L->data[i-1]; 
}
int count_list(List *L)
{
	return L->size;
}

typedef struct{
	int data[MAX_ELEMENTS];
	int size;
}Stack;

void makeNull_stack(Stack *S)
{
	S->size = 0;
}
int empty_stack(Stack *S)
{
	return S->size == 0;
}
void push_stack(Stack *S, int x)
{
	S->data[S->size] = x;
	S->size++;
}

int top_Stack(Stack *S)
{
	return S->data[S->size-1];	
}

void pop_Stack(Stack *S)
{
	S->size--;
}
typedef struct{
	int data[MAX_ELEMENTS];
	int front, rear;
}Queue;

void makeNull_queue(Queue *Q)
{
	Q->front = 0;
	Q->rear = -1;
}

int empty_queue(Queue *Q)
{
	return (Q->front > Q->rear);
}

void push_queue(Queue *Q, int x)
{
	Q->rear++;
	Q->data[Q->rear] = x;
}
int top_queue(Queue *Q)
{
	return Q->data[Q->front];
}
void pop_queue(Queue *Q)
{
	Q->front++;
}

