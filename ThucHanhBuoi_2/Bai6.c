#include <stdio.h>
#include <stdlib.h>
#define white 0
#define black 1
#define gray 2
#define MAX_V 101
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
	int A[MAX_V][MAX_V];
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
	G->A[x][y] += 1;
//	G->A[y][x] = 1;
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
//		if(y != x && adjacent(G,x,y)) PushBack(&L,y);
		if(adjacent(G,x,y)) PushBack(&L,y);
	}
	return L;
}

int mark[MAX_V],color[MAX_V], cycle;
void findcycle(Graph *G, int x)
{
	color[x] = gray;
	List list; MakeNull_List(&list);
	list = neighbors(G,x);
	int j,y;
	for(j = 1 ; j <= list.size; ++j)
	{
		y = Element_at(&list,j);
//		if(parent == y) continue;
		if(color[y] == gray) 
		{
			cycle = 1; /*Ton tai chu trinh*/
			return;
		}	
		if(color[y] == white)	findcycle(G,y);
	}
	color[x] = black;
}
int contains_cycle(Graph *G)
{
	int j;
	for(j = 1; j <= G->n; j++)
	{
		color[j] = white;
	}
	cycle = 0;
	for(j = 1; j <= G->n; j++)
	{
		if(color[j] == white) 
			findcycle(G,j);
	}
	return cycle;
}
int duyetdequy_2(Graph *G, int x)
{
	if(mark[x] == 1) return 0;
	else
	{
		int n = 1,i;
//		printf(" %d ",x); 
		mark[x] = 1;
		List list; MakeNull_List(&list); list = neighbors(G,x);
		for(i = 1; i <= list.size; ++i)
		{
			n+=duyetdequy_2(G,Element_at(&list,i));
		}
		return n;
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
	duyetdequy_2(&G,1);
	if(contains_cycle(&G))
	{
		printf("NO");
	}
	else
	{
		printf("YES");
	}
	return 0;
}
