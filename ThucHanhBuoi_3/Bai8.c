#include <stdio.h>
#define MAX_V 101
#define MAX_E 500
#define NO_EDGE -1
#define INFINITY 999999

typedef struct{
	int n,m;
	int A[MAX_V][MAX_E];
}Graph;

void init_graph(Graph *G, int n)
{
	G->n = n;
	int i,j;
	for(i = 1; i <= n; i++)
	{
		for(j = 1; j <= n; j++)
		{
			G->A[i][j] = NO_EDGE;
		}
	}
}

void add_edge(Graph *G, int u, int v, int w)
{
	G->A[u][v] = w;
}
int pi[MAX_V][MAX_E], next[MAX_V][MAX_E];
void floyd_wallson(Graph *G)
{
	int i,j,k;
	for(i = 1; i <= G->n; i++)
	{
		for(j = 1; j <= G->n; j++)
		{
			pi[i][j] = INFINITY;
			next[i][j] = -1;
		}
	}
	for(i = 1; i <= G->n; i++)
	{
		pi[i][i] = 0;
	}
	for(i = 1; i <= G->n; i++)
	{
		for(j = 1; j <= G->n; j++)
		{
			if(G->A[i][j] != NO_EDGE)
			{
				pi[i][j] = G->A[i][j];
				next[i][j] = j;
			}
		}
	}
	
	for (k = 1; k <= G->n; k++)
	{
		for (i = 1; i <= G->n; i++)
		{
			for (j = 1; j <= G->n; j++)
			{
				if (pi[i][k] + pi[k][j] < pi[i][j] && pi[i][k] != INFINITY && pi[k][j] != INFINITY) 
				{
					pi[i][j] = pi[i][k] + pi[k][j];
					next[i][j] = next[i][k];
				}
			}
		}
	}

	for(i = 1; i <= G->n; i++)
	{
		for(j = 1; j <= G->n; j++)
		{
			if(pi[i][j] == INFINITY) 
				printf("%d->%d: oo\n"); 
			else printf("%d->%d: %d\n",i,j,pi[i][j]);	
		}
	}
}
void getStreet(int start, int end, int cnt){
	if (cnt && start==end) return;
	int nxt = next[start][end];
	printf ("%d", nxt);
	if(nxt!=end) printf(" -> ");
	getStreet(nxt, end, 1);
}
int main(){
	Graph G;
	int n,m,u,v,w,e,i,j;
	freopen("dothi.txt","rt",stdin);
	scanf("%d%d",&n,&m);
	init_graph(&G,n);
	for(e = 1; e <= m; e++)
	{
		scanf("%d%d%d",&u,&v,&w);
		add_edge(&G,u,v,w);
	}
	floyd_wallson(&G); int cycle = 0;
	
	return 0;
}
