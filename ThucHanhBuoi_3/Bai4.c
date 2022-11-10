#include <stdio.h>
#define MAX_V 100
#define MAX_E 500
#define NO_EDGE -1
#define INFINITY 999999

typedef struct{
	int n,m;
	int A[MAX_V][MAX_E];
}Graph;

void init_graph(Graph *G, int n)
{
	int i,j;
	G->n = n;
//	G->m = m;
	for(i = 1; i <= n;i++)
	{
		for(j = 1; j <= n; j++)
		{
			G->A[i][j] = NO_EDGE;
		}
	}
}
void add_edge(Graph *G ,int u, int v, int w)
{
	G->A[u][v] = w;
	G->A[v][u] = w;
}
int mark[MAX_V], pi[MAX_V], p[MAX_V];
void dijktra(Graph *G ,int s)
{
	int i,j,it, min_pi;
	for(i = 1; i <= G->n; i++)
	{
		pi[i] = INFINITY;
		mark[i] = 0;
	}
	pi[s] = 0;
	p[s] = -1;
	for(it = 1; it <= G->n; it++)
	{
		min_pi = INFINITY;
		for(j = 1; j <= G->n; j++)
		{
			if(!mark[j] && pi[j] < min_pi)
			{
				min_pi = pi[j];
				i = j;
			}
		}
		mark[i] = 1;
		for(j = 1; j <= G->n; j++)
		{
			if(!mark[j] && G->A[i][j] != NO_EDGE && pi[j] > pi[i] + G->A[i][j])
			{
				pi[j] = pi[i] + G->A[i][j];
				p[j] = i;
			}
		}
	}
}
int main(){
	Graph G;
	int e,v,n,m,u,w, bd,kt;
	freopen("dothi.txt","rt",stdin);
	scanf("%d%d",&n,&m);
	init_graph(&G,n);
	for(e = 1; e <= m; e++)
	{
		scanf("%d%d%d",&u,&v,&w);
		add_edge(&G,u,v,w);
	}
	scanf("%d%d", &bd, &kt);
	dijktra(&G,bd);
	printf("%d",pi[kt]);
	return 0;
}
