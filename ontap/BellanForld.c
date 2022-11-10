#include "CTDL.h"
#define INF 999
#define NONE -1234

typedef struct{
	int u,v;
	int w;
}Edge;
typedef struct{
	int n,m;
	Edge edge[1000];
}Graph;

void init_graph(Graph *G, int n)
{
	G->m = 0;
	G->n = n;
}

void add_edge(Graph *G, int u, int v, int w)
{
	G->edge[G->m].u = u;
	G->edge[G->m].v = v;
	G->edge[G->m].w = w;
	G->m++;
}

int mark[Max_V], pi[Max_V], p[Max_V];
int negativecycle = 0;
void BellManFord(Graph *G ,int s)
{
	int i,j,it,k,u,v,w;
	for(i = 1; i <= G->n; i++)
	{
		pi[i] = INF;
//		mark[i] = 0;
		p[i] = NONE;
	}
	pi[s] = 0;
	p[s] = -1;
	for(it = 1; it <= G->n; it++)
	{
		for(k = 0; k < G->m; k++)
		{
			int u = G->edge[k].u;
			int v = G->edge[k].v;
			int w =	G->edge[k].w;
			if(pi[v] > pi[u] + w)
			{
				pi[v] = pi[u] + w;
				p[v] = u;
			}
		}
	}
	for(k = 0; k < G->m; k++)
	{
		int u = G->edge[k].u;
		int	v = G->edge[k].v;
		int	w =	G->edge[k].w;
		if(pi[v] > pi[u] + w)
		{
//			printf("negative cycle\n");
//			return;	
			negativecycle = 1; return;
		}
	}
}
void FindStreet(int c, int old)
{
	if(c != -1)
	{
		int tempt = c;
		c = p[c];
		FindStreet(c,old);
		printf("%d",tempt);
		if(old != tempt) printf(" -> ");
	} 
	else return;
}
int MinusCycle(Graph *G)
{
	int it,k,u,v,w;
	for(it = 1; it <= G->n; it++)
	{
		for(k = 0; k < G->m; k++)
		{
			u = G->edge[k].u;
			v = G->edge[k].v;
			w =	G->edge[k].w;
			if(pi[v] > pi[u] + w)
			{
				return 1;
			}
		}
	}
	return 0;
}
void LietKeCycle(Graph *G)
{
	int it,k,u,v,w, cycle;
	for(it = 1; it <= G->n; it++)
	{
		for(k = 0; k < G->m; k++)
		{
			u = G->edge[k].u;
			v = G->edge[k].v;
			w =	G->edge[k].w;
			if(pi[v] > pi[u] + w)
			{
				cycle = u;
			}
		}
	}
	printf("Liet ke cac dinh am [");
	if(cycle)
	{
		printf(" %d ",cycle);
		int tempt = p[u];
		while(tempt != u)
		{
			printf(" %d ",tempt);
			char c;
			tempt = p[tempt];
		}
	}
	printf("]\n");
}
int main(){
	freopen("bellmanford.txt","rt",stdin);
	Graph G;
	int n,m,i,j,e,w,u,v;
	scanf("%d%d",&n,&m);
	init_graph(&G,n);
	for(e = 1; e <= m; e++)
	{
		scanf("%d%d%d",&u,&v,&w);
		add_edge(&G,u,v,w);
	}
	BellManFord(&G,1);
	if(negativecycle) printf("negative cycle\n");
	else printf("OK\n");
	for(i = 1; i <= G.n; i++)
	{
		printf("pi[%d] = %d | p[%d] = %d\n",i,pi[i],i,p[i]);
	}
	if(MinusCycle(&G))
	{
		printf("\nYES\n");
		LietKeCycle(&G);
	}
	else
	{
		printf("\nNO\n");
		printf("Duong di ngan nhat: ");
		FindStreet(G.n,G.n);
	}
	return 0;
}
