#include <stdio.h>
#include <stdlib.h>
#define MAX_V 1000
#define MAX_E 500
#define NONE -1234
#define INFINITY 9999999
typedef struct{
	int u,v;
	int w;
}Edge;
typedef struct{
	int n,m;
	Edge edges[1000];
}Graph;

void init_graph(Graph *G, int n)
{
	G->n = n;
	G->m = 0;
}

void add_edge(Graph *G, int u, int v, int w)
{
	G->edges[G->m].u = u;
	G->edges[G->m].v = v;
	G->edges[G->m].w = w;
	G->m++;
}
int mark[MAX_V], pi[MAX_V], p[MAX_V];
void bellmanford(Graph *G, int x)
{
	int i, j, it, k;
	for(i=1; i<=G->n; i++){
		pi[i]=INFINITY;
		p[i] = NONE;
	}
	pi[x]=0;
	p[x]=-1;
	for(it=1; it<G->n; it++)
	{
		for(k=0; k<G->m; k++)
		{
			int u = G->edges[k].u;
			int v = G->edges[k].v;
			int w = G->edges[k].w;
			if(pi[u] + w < pi[v])
			{
				pi[v] = pi[u] + w;
				p[v] = u;
			}
		}
	}
	
	/*for(k = 0; k < G->m; k++)
	{
		int u = G->edges[k].u;
		int v = G->edges[k].v;
		int w = G->edges[k].w;
		if(pi[v] > pi[u] + w)
		{
			printf("negative cycle");
			return;
		}
	}
	printf("ok");*/
}
void findstreet(Graph *G, int c, int old)
{
	if(c!= -1)
	{
		int tempt = c;
		c = p[c];
		findstreet(G,c,old);
		printf("%d",tempt);
		if(c != old) printf(" -> ");
	}
	else return;
}

int main(){
	int i,j,n,m,w,u,v,e;
	freopen("dothi.txt","rt",stdin);
	Graph G;
	scanf("%d%d",&n,&m);
	init_graph(&G,n);
	for(e = 1; e <= m; e++)
	{
		scanf("%d%d%d",&u,&v,&w);
		add_edge(&G,u,v,w);
	}
	bellmanford(&G,1);
	printf("%d",pi[G.n]);
	return 0;
}
