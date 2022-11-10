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

/* Bien ho tro */
int mark[Max_Vertexs];
/* Duyet de quy dinh x */
void traversal(Graph* G, int x) 
{
/* Neu dinh x da duyet, khong lam gi ca */
	if (mark[x] == 1)	return;
	
	/* Nguoc lai, duyet no */
	printf("%d\n", x);
	mark[x]= 1;
	/* Lay cac dinh ke cua no va duyet cac dinh ke */
	List list = neighbors(G, x);
	int j;
	for (j = 1; j <= list.size; j++) 
	{
		int y = Element_at(&list, j);
		traversal(G, y);
	}
}
void depth_first_search_dequy(Graph* G) {
/* Khoi tao mark, chua dinh nao duoc xet */
	int j;
	for (j = 1; j <= G->n; j++)
		mark[j] = 0;
	traversal(G, 1);
	for(j = 1; j <= G->n; j++)
	{
		if(mark[j] == 0) traversal(G,j);
	}
}

int main(){
	Graph G; int n,m,u,v,i,j,e;
	scanf("%d%d",&n,&m);
	init_graph(&G,n);
	for(e = 1; e <= m; e++)
	{
		scanf("%d%d",&u,&v);
		add_edge(&G,u,v);
	}
	depth_first_search_dequy(&G);
	return 0;
}
