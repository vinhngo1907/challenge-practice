#include <stdio.h>
#define Max_Vertexs 100
#define MAX_ELEMENTS 100
typedef int ElementType;
typedef struct{
	ElementType data[MAX_ELEMENTS];
	int size;
}List;

void MakeNull_List(List *L)
{
	L->size = 0;
}

void PushBack(List *L, int x)
{
	L->data[L->size] = x;
	L->size++;
}

ElementType Element_at(List *L, int i)
{
	return L->data[i-1]; 
}

typedef struct{
	int data[100];
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
typedef struct{
	int n,m;
	int A[Max_Vertexs][Max_Vertexs];
}Graph;

void init_graph(Graph *G, int n)
{
	int i,j;
	G->n = n;
	for(i = 1; i <= n; i++)
	{
		for(j = 1; j <= n; j++)
		{
			G->A[i][j] = 0;
		}
	}
}

void add_edge(Graph *G, int x, int y)
{
	G->A[x][y] = 1;
	G->A[y][x] = 1;
}

int adjacent(Graph *G, int x, int y)
{
	return G->A[x][y] != 0;
} 
List neighbors(Graph *G, int x)
{
	List L; MakeNull_List(&L);
	int y;
	for(y = 1; y <= G->n; y++)
	{
		if(y != x && adjacent(G,x,y)) PushBack(&L,y);
	}
	return L;
}
int mark[Max_Vertexs];
int BFS(Graph *G, int x)
{
	int j;
	Queue frontier; 
	MakeNull_Queue(&frontier);
	for(j = 1; j <= G->n; j++)
	{
		mark[j] = 0;
	}
	Push_Queue(&frontier,x);
	while(!Empty_Queue(&frontier))
	{
		x = Top_Queue(&frontier); Pop_Queue(&frontier);
		if(mark[x] == 1) continue;
		printf("%d\n",x); mark[x] =1 ;
		List list ; MakeNull_List(&list); 
		list = neighbors(G,x);
		for(j =1; j <= list.size; j++)
		{
			int y = Element_at(&list,j);
			Push_Queue(&frontier,y);
		}
	}
}

int main(){
	freopen("dothi.txt", "rt", stdin);
	Graph G; int n,m,u,v,x,y,e,i,j;
	scanf("%d%d",&n,&m);
	init_graph(&G,n);
	for(e = 1; e <= m; e++)
	{
		scanf("%d%d",&u,&v);
		add_edge(&G,u,v);
	}
	BFS(&G,1);
	for(i = 1; i <= n; i++)
	{	
		if(!mark[i])
		{
			BFS(&G,i);
			break; 
		} 
	}	
	return 0;
}
