#include <stdio.h>
#include <stdlib.h>
#define Max_N 100
#define Max_V 101
#define Max 100
//Danh sach
typedef int ElementType;
typedef struct{
	ElementType Data[Max_N];
	int size;
}List;

void makenull_list(List *L)
{
	L->size = 0;
}

int empty_list(List *L)
{
	return (L->size == 0);
}

void push_back(List *L, int x)
{
	L->size++;
	L->Data[L->size] = x;
}

ElementType element_at(List *L, int i)
{
	return L->Data[i];
}

int count_list(List *L)
{
	return L->size;
}

typedef struct{
	int top_idx;
	int A[Max];
}Stack;

void makenull_stack(Stack *S)
{
	S->top_idx = Max;
}
int empty_stack(Stack *S)
{
	return (S->top_idx == Max);
}
void push_stack(Stack *S, int x)
{
	S->top_idx--;
	S->A[S->top_idx] = x;
}
int top_stack(Stack *S)
{
	return S->A[S->top_idx];
}

void pop_stack (Stack *S)
{
	S->top_idx++;
}

typedef struct{
	int F,R;
	int Data[Max];
}Queue;

void makenull_queue(Queue *Q)
{
	Q->F = 0;
	Q->R = -1;
}
int empty_queue(Queue *Q)
{
	return (Q->F > Q->R);
}
void push_queue(Queue *Q, int x)
{
	Q->R++;
	Q->Data[Q->R] = x;
}
int top_queue(Queue *Q)
{
	return Q->Data[Q->F];
}

void pop_queue(Queue *Q)
{
	Q->F++;
}
