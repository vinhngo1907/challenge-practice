#define white 0
#define black 1
#define gray 2
#define MAX_VERTICES 1000
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
int color[MAX_VERTICES];
int cycle;


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
	G->A[x][y] += 1;
	G->A[y][x] += 1;
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

void findCycle(Graph *G, int x, int parent){
	color[x]= gray;
	List l; MakeNull_List(&l);
	l= neighbors(G, x);
	int i, y;
	for(i=1;i<=l.size;++i){
		y= Element_at(&l, i);
		if(parent == y) continue;
		if(color[y] == gray){
			cycle = 1;	/* T.n t.i chu tr.nh */
			return;
		}
		if(color[y] == white){
			findCycle(G, y, x);
		}
	}
	color[x]= black;
}

int contain_cycle(Graph G){
	int i;
	for(i=1;i<=G.n;++i){
		if(color[i]==white){
			findCycle(&G, i, 0);
		}
	}
	return cycle;
}
int mark[MAX_VERTICES];
int duyetdequy(Graph *G, int x)
{
	if(mark[x] == 1) return 0;
	else
	{
		int n=1,j;
		mark[x] = 1;
		List list = neighbors(G,x);
		for(j =1 ; j <= list.size; j++)
		{
			n+=duyetdequy(G,Element_at(&list,j));
		}
		return n;
	}
}
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
	duyetdequy(&G, 1);
	if(contain_cycle(G)){
		printf("YES");
	}else{
		printf("NO");
	}
	
}
