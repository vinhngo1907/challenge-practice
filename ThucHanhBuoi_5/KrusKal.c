#include <stdio.h>
#include <stdlib.h>
#define Max_E 101

typedef struct{
	int u,v;
	int w;
}Edge;
typedef struct{
	int n,m;
	Edge edge[Max_E];
}Graph;

void init_graph(Graph *G ,int n, int m)
{
	G->n = n;
	G->m = 0;
	int i;
	for(i = 1; i <= m; i++)
	{
		G->edge[i].u = 0;
		G->edge[i].v = 0;
		G->edge[i].w = 0;
	}
}

void add_edge(Graph *G, int u, int v, int w)
{
	int e= ++(G->m);
	G->edge[e].u = u;
	G->edge[e].v = v;
	G->edge[e].w = w;
	
}
void sortedge(Graph *g)
{
	int m= g->m, i, j;
	for(i=1;i<=m;++i){
		for(j=1;j<=m-i;++j){
			if(g->edge[j].w > g->edge[j+1].w){
				Edge temp = g->edge[j];
				g->edge[j] = g->edge[j+1];
				g->edge[j+1] = temp;
			}
		}
	}
}
int parent[Max_E];
int findroot(int v)
{
	if(parent[v] == v)
		return v;
	else return findroot(parent[v]);	
}

int kruskal(Graph *g, Graph *T)
{
	sortedge(g);
	int e, i, sum_w = 0;
	for(i=1;i<=g->n;++i){
		parent[i] = i;
	}
	for(e=1;e<=g->m;++e){
		int u = g->edge[e].u;
		int v = g->edge[e].v;
		int w = g->edge[e].w;
		int root_u = findroot(u);
		int root_v = findroot(v);
		if(root_u != root_v){
			add_edge(T, u, v, w);
			parent[root_v] = root_u;
			sum_w += w;
		}
	}
	return sum_w;
}
void swap(Edge *x, Edge *y){
	Edge temp= *x;
	*x = *y;
	*y = temp;
}
void sortList(Graph* g){
	int i,j;
	for(i = 1; i <= g->m; ++i){
		for(j = 1;j < g->m; ++j){
			if(g->edge[j].w > g->edge[j+1].w){
				swap(&g->edge[j], &g->edge[j+1]);
			}else if(g->edge[j].w == g->edge[j+1].w && g->edge[j].u > g->edge[j+1].u){
				swap(&g->edge[j], &g->edge[j+1]);
			}else if((g->edge[j].w == g->edge[j+1].w) && (g->edge[j].u == g->edge[j+1].u) && (g->edge[j].v > g->edge[j+1].v)){
				swap(&g->edge[j], &g->edge[j+1]);
			}
		}
	}
}
int main(){
	freopen("kruskal.txt","rt",stdin);
	Graph G,T;
	int n,m,u,v,i,w;
	scanf("%d%d",&n,&m);
	init_graph(&G,n,m);
	init_graph(&T, n, m);
	for(i = 1; i <= m; ++i)
	{
		scanf("%d%d%d",&u,&v,&w);
		add_edge(&G,u,v,w);
	}
	printf ("%d\n", kruskal(&G, &T));
	sortList(&T);
	for(i=1; i<=T.m; ++i){
		int x = T.edge[i].u, y= T.edge[i].v;
		if(x>y){
			int temp= x;
			x= y;
			y= temp;
		}
		printf ("%d %d %d\n", x, y,T.edge[i].w);
	}
	int e;
	for (i = 1; i <= T.m; ++i)
	printf("(%d, %d): %d\n", T.edge[i].u, T.edge[i].u, T.edge[i].w);
	
	return 0;
}
