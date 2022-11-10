#include "CTDL.h"
#define INF 999
#define NO_EDGE -1
typedef struct{
	int n;
	int A[Max_V][Max_V];
}Graph;

void init_graph(Graph *G, int n)
{
	G->n = n;
	int i, j;
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
	//G->A[v][u] = w; Neu vo huong them dong cuoi
}

int adjacent(Graph *G, int u, int v)
{
	return G->A[u][v] != NO_EDGE;
}
int mark[Max_V], pi[Max_V], p[Max_V];
void DijKtra(Graph *G ,int s)
{
	int i,j,it, min_pi;
	for(i = 1; i <= G->n; i++)
	{
		pi[i] = INF;
		mark[i] = 0;
	}
	pi[s] = 0;
	p[s] = -1;
	for(it = 1; it <= G->n; it++)
	{
		min_pi = INF;
		for(j = 1; j <= G->n; j++)
		{
			if(!mark[j] && min_pi > pi[j])
			{
				min_pi = pi[j];
				i = j;
			}
		}
		mark[i] = 1;
		for(j = 1; j <= G->n; j++)
		{
			if(adjacent(G,i,j) && !mark[j])
			{
				if(pi[j] > pi[i]+G->A[i][j])
				{
					pi[j] = pi[i] + G->A[i][j];
					p[j] = i;
				}
			}
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
int main(){
	freopen("dijktra.txt","rt",stdin);
	Graph G;
	int n,m,i,j,e,w,u,v;
	scanf("%d%d",&n,&m);
	init_graph(&G,n);
	for(e = 1; e <= m; e++)
	{
		scanf("%d%d%d",&u,&v,&w);
		add_edge(&G,u,v,w);
	}
	DijKtra(&G,1);
	for(i = 1; i <= G.n; i++)
	{
		printf("pi[%d] = %d | p[%d] =  %d\n",i,pi[i],i,p[i]);
	}
	if(pi[G.n] == INF) printf("-1\n");
	else printf("%d\n",pi[G.n]);
	FindStreet(G.n, G.n);
	return 0;
}
