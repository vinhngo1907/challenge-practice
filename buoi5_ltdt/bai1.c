#include <stdio.h>

#define MAX_E 101

typedef struct{
	int u, v, w;
}Edge;

typedef struct{
	int m, n;
	Edge edge[MAX_E];
}Graph;

void init_graph(Graph* g, int n, int m){
	g->n = n;
	g->m = 0;
	int i;
	
	for(i=1;i<=m;++i){
		g->edge[i].u = 0;
		g->edge[i].v = 0;
		g->edge[i].w = 0;
	}
}

void add_edge(Graph* g, int u, int v, int w){
	int e= ++(g->m);
	
	g->edge[e].u = u;
	g->edge[e].v = v;
	g->edge[e].w = w;
}

void sortEdge(Graph* g){
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

int parent[MAX_E];
int findRoot(int v){
	if(parent[v] == v) return v;
	else return findRoot(parent[v]);
}

int Krusal(Graph g, Graph* T){
	int e, i, sum_w = 0;
	
	for(i=1;i<=g.n;++i){
		parent[i] = i;
	}
	
	for(e=1;e<=g.m;++e){
		int u = g.edge[e].u;
		int v = g.edge[e].v;
		int w = g.edge[e].w;
		
		int root_u = findRoot(u);
		int root_v = findRoot(v);
		
		if(root_u != root_v){
			add_edge(T, u, v, w);
			parent[root_v] = root_u;
			sum_w += w;
		}
	}
	
	return sum_w;
}

int main(){
	freopen("data.txt", "r", stdin);
	
	Graph g, T;
	int i, u, v, w, n, m;
	scanf ("%d%d", &n,&m);
	
	init_graph(&g, n, m);
	init_graph(&T, n, m);
	
	for(i=1;i<=m;++i){
		scanf ("%d%d%d", &u, &v, &w);
		add_edge(&g, u,v,w);
	}
	
	printf ("\n Do thi da nhap: \n");
	for(i=1;i<=m;++i){
		printf("(%d, %d): %d\n", g.edge[i].u,g.edge[i].v,g.edge[i].w);
	}
	
	sortEdge(&g);
	printf ("\n Do thi da sap xep: \n");
	for(i=1;i<=m;++i){
		printf("(%d, %d): %d\n", g.edge[i].u,g.edge[i].v,g.edge[i].w);
	}
	
	printf ("\n Tong duong di ngan nhat la: %d\n", Krusal(g, &T));
	for(i=1;i<=T.m;++i){
		printf ("(%d, %d): %d\n", T.edge[i].u,T.edge[i].v,T.edge[i].w);
	}
	
	return 0;
}
