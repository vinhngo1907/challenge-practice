#include <stdio.h>
#define MAX_V 101
#define MAX_E 501
#define NO_EDGE 0

typedef struct{
	int u,v,w;
}Edge;

typedef struct{
	int n,m;
	Edge edge[1000];
}Graph;

void init_graph(Graph *G ,int n)
{
	G->n = n;
	G->m = 0;
}

void add_edge(Graph *G ,int u, int v, int w)
{
	G->edge[G->m].u = u;
	G->edge[G->m].v = v;
	G->edge[G->m].w = w;
	G->m++;
}
#define INFINITY 999999
int pi[MAX_V], p[MAX_V]; 
void bellman_ford(Graph *G ,int x)
{
	int i,j,k,it;
	for(i = 1; i <= G->n; i++)
	{
		pi[i] = INFINITY;
	}
	pi[x] = 0;
	p[x] = -1;
	for(it = 1; it <= G->n; it++)
	{
		for(k = 0; k< G->m; k++)
		{
			int u = G->edge[k].u;
			int v = G->edge[k].v;
			int w = G->edge[k].w;
			if(pi[v] > pi[u] + w)
			{
				pi[v] = pi[u] + w;
				p[v] = u;
			}
		}
	}
	for(k= 0; k < G->m; k++)
	{
		int u = G->edge[k].u;
		int v = G->edge[k].v;
		int w = G->edge[k].w;
		if(pi[v] > pi[u] + w)
		{
			printf("negative cycle\n");
			return;
		}
	}
	printf("ok\n");
}


int main(){
	freopen("dothi.txt","rt",stdin);
	int n,m,u,v,e,i,w,start,end;
	Graph G;
	scanf("%d%d",&n,&m);
	init_graph(&G,n);
	for(e = 1 ; e <= m; e++)
	{
		scanf("%d%d%d",&u,&v,&w);
		add_edge(&G,u,v,w);
	}

	bellman_ford(&G,1);
	for(i = 1 ; i<= n; i++)
	{
		printf("pi[%d] = %d, p[%d] = %d\n",i,pi[i],i,p[i]);
	}

	return 0;
}
