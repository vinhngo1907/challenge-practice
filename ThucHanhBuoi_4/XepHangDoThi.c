#include <stdio.h>
#include <stdlib.h>
#define MAX_V 100
typedef struct{
	int n;
	int A[MAX_V][MAX_V];
}Graph;

void init_graph(Graph *G, int n)
{
	G->n = n;
	int i,j;
	for(i = 1 ; i <= n; i++)
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
}
int adjacent(Graph *G, int x, int y)
{
	return G->A[x][y] != 0;
}
int degree(Graph *G, int y){
	int i, count=0;
	for (i=1;i<=G->n;i++)
		if (G->A[i][y]==1) count++;
	return count;
}

// Danh sach

typedef struct{
	int Data[MAX_V];
	int size;
}List;

void makenull_list(List *L){
	L->size=0;
}

void push_back(List *L, int x){
	L->size++;
	L->Data[L->size]=x;
}

int element_at(List *L, int i){
	return L->Data[i];
}

void copy_list(List *S1, List *S2){
	int i;
	makenull_list(S1);
	S1->size=S2->size;
	for (i=1;i<=S2->size;i++)
		S1->Data[i]=S2->Data[i];
}

int rank[MAX_V];
void ranking(Graph *G)
{
	int i,j,k;
	int d[G->n];
	List S1, S2;
	makenull_list(&S1);
	for(i = 1; i <= G->n; i++)
	{
		d[i] = degree(G,i);
		if(d[i] == 0) push_back(&S1,i);
	}
	k = 0;
	while(S1.size != 0)
	{
		makenull_list(&S2);
		for(i = 1; i <= S1.size; i++)
		{
			int y = element_at(&S1,i);
			rank[y] = k;
			for(j = 1; j <= G->n; j++)
			{
				if(adjacent(G,y,j))
				{
					d[j]--;
					if(d[j] == 0) push_back(&S2,j);
				}
			}
		}
		k++;
		copy_list(&S1,&S2);
	}
}
int main(){
	freopen("ranking.txt","rt",stdin);
	int i,j,n,m,x,y;
	Graph G;
	scanf("%d%d",&n,&m);
	init_graph(&G,n);
	for(i = 1; i <= m; i++)
	{
		scanf("%d%d",&x,&y);
		add_edge(&G,x,y);
	}
	for(j = 1; j <= n; j++) rank[j] = -1;
	ranking(&G);
	for(i = 1; i <= n; i++)
	{
		printf("%d\n",rank[i]);
	}
}
