#include <stdio.h>
#include <conio.h>
#define Max_Elements 100
typedef struct{
	int data[Max_Elements];
	int front, rear;
}Queue;

void MakeNull_Queue(Queue *Q)
{
	Q->front = 0;
	Q->rear = -1;
}

int Empty_Queue(Queue *Q)
{
	return (Q->front > Q->rear);
}

void Push_Queue(Queue *Q, int x)
{
	Q->rear++;
	Q->data[Q->rear] = x;
}
int Top_Queue(Queue *Q)
{
	return Q->data[Q->front];
}
void Pop_Queue(Queue *Q)
{
	Q->front++;
}
