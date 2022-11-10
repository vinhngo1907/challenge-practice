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
typedef struct{
	int n;
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
int DFS(Graph *G, int x)
{
	int j;
	Stack frontier; 
	MakeNull_Stack(&frontier);
	for(j = 1; j <= G->n; j++)
	{
		mark[j] = 0;
	}
	Push_Stack(&frontier,x);
	while(!Empty_Stack(&frontier))
	{
		x = Top_Stack(&frontier); Pop_Stack(&frontier);
		if(mark[x] == 1) continue;
		printf("%d\n",x); mark[x] =1 ;
		List list ; MakeNull_List(&list); 
		list = neighbors(G,x);
		for(j =1; j <= list.size; j++)
		{
			int y = Element_at(&list,j);
			Push_Stack(&frontier,y);
		}
	}
}


typedef struct {
    int u;
    int parent;
} ELEMENT_TYPE;

int main(){
	freopen("dothi.txt", "r", stdin);
	Graph G;
	int n, m, u, v, w, e;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	
	for (e = 0; e < m; e++) {
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
}
