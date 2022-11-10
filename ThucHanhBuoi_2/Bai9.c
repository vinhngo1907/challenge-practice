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
int min(int x, int y){
	return (x<y)?x:y;
}

int num[MAX_V], min_num[MAX_V], on_stack[MAX_V], idx= -1,yes = 0;
Stack s;
void strong_connect(Graph g, int x){
	num[x]= min_num[x]= idx++;
	Push_Stack(&s, x);
	on_stack[x]= 1;
	
	List l; MakeNull_List(&l);
	l=neighbors(&g, x);
	int i, y;
	for(i=1;i<=l.size;++i){
		y= Element_at(&l, i);
		if(!num[y]){
			strong_connect(g, y);
			min_num[x] = min(min_num[x], min_num[y]);
		}else if(on_stack[y]){
			min_num[x] = min(min_num[x], num[y]);
		}
	}
	//printf("\n num[%d]: %d - min_num[%d]: %d", x, num[x], x, min_num[x]);
	
	if(num[x]==min_num[x]){
		//printf ("\n %d la khop [", x);
		int w, nlt= 0;
		do{
			w= Top_Stack(&s); Pop_Stack(&s);
			//printf ("%4d ", w);
			on_stack[w]= 0;
			++nlt;
		}while(w!=x);
		if(nlt==g.n) yes= 1;
	}
}

void listCycle(Graph G)
{
	int i;
	idx= 1;
	MakeNull_Stack(&s);
	for (i=1;i<=G.n;++i){
		if(!num[i]){
			strong_connect(G, i);
		}
	}
	if(yes) printf("strong connected");
	else printf ("unconnected");
}
int mark[100];
int duyetdequy(Graph *G, int x)
{
	if(mark[x] == 1) return 0;
	else
	{
		int n = 1,i;
		mark[x] = 1;
		List list; MakeNull_List(&list) ;list = neighbors(G,x);
		for(i = 1 ;i <= G->n; i++)
		{
			n+=duyetdequy(G,Element_at(&list,i));
		}
		return n;
	}
}
int main(){

	int n,m,u,v,x,y,i,j,e;	
	freopen("dothi.txt", "rt", stdin);
	Graph G;
	scanf("%d%d",&n,&m);
	init_graph(&G,n);
	for(e = 1; e <= m; e++)
	{
		scanf("%d%d",&u,&v);
		add_edge(&G,u,v);
	}
//	duyetdequy(&G, 1);
	listCycle(G);
	return 0;
}
