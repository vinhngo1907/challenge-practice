#include <stdio.h>
#include "list.h"

#define MAX_V 101
#define NO_EDGE -1

typedef struct{
	int m, n;
	int edge[MAX_V][MAX_V];
}Graph;

void init_graph(Graph* g, int n, int m){
	g->n = n;
	g->m = m;
	int i, j;
	
	for(i=1;i<=n;++i){
		for(j=1;j<=n;++j){
			g->edge[i][j] = NO_EDGE;
		}
	}
}

void add_edge(Graph* g, int u, int v, int w){
	g->edge[u][v] = w;
	g->edge[v][u] = w;
}

int distangeFrom(int u, List *S, Graph g){
	int min_dis = 9999;
	int v, i, min_v= -1;
	
	for(i=1;i<=S->size;++i){
		v= element_at(S, i);
		if(g.edge[u][v] != NO_EDGE && min_dis > g.edge[u][v]){
			min_dis = g.edge[u][v];
			min_v= v;
		}
	}
	return min_v;
}

int mark[MAX_V];
int Prim(Graph g, Graph *T){
	init_graph(T, g.n, g.m);
	
	List S; make_null(&S);
	int i,u;
	
	for( i=1;i <= g.n; ++i){
		mark[i] = 0;
	}
	
	push_back(&S, 1);
	mark[1] = 1;
	
	int sum= 0;
	for(i=1;i<g.n;++i){	//	them vao n -1 dinh con lai
		int min_dis= 99999, min_u, min_v;
		for(u=1;u<=g.n;++u){		// 		quet lai tat ca cac dinh
			if(!mark[u]){
				int v= distangeFrom(u, &S, g);
				if(v != -1 && min_dis > g.edge[u][v]){
					min_dis = g.edge[u][v];
					min_u= u;
					min_v= v;
				}
			}
		}
		
		//	dua vao S
		mark[min_u] = 1;
		push_back(&S, min_u);
		
		sum += min_dis;
		add_edge(T, min_u, min_v, min_dis);
	}
	return sum;
}

int pi[MAX_V], p[MAX_V];

int Prim2(Graph g, Graph* T){
	init_graph(T, g.n, g.m);
	
	int i, j;
	for(i=1;i<=g.n;++i){
		pi[i] = 9999;
	}
	
	pi[1] = 0;
	
	for(i=1;i<=g.n;++i){	//	gan khoi tao cho dinh 1
		if(g.edge[1][i] != NO_EDGE){
			pi[i] = g.edge[1][i];
			p[i] = 1;
		}
	}
	
	for(i=1;i<=g.n;++i){
		mark[i] = 0;
	}
	mark[1] = 1;
	
	int sum = 0, u;
	for(i=1;i < g.n ; ++i){
		int min_dis = 9999, min_u;
		for(u= 1; u <= g.n ; ++u){
			if(!mark[u] && pi[u] < min_dis){
				min_dis = pi[u];
				min_u = u;
			}
		}
		
		u = min_u;
		
		mark[min_u] = 1;
		sum += min_dis;
		add_edge(T, min_u, p[min_u],min_dis);
		
		// cap nhat lai pi va p cua cac dinh ke cua u
		for(j= 1; j<=g.n;++j){
			if(g.edge[u][j] != NO_EDGE && !mark[j]){
				if(pi[j] > g.edge[u][j]){
					pi[j] = g.edge[u][j];
					p[j] = u;
				}
			}
		}
	}
	
	return sum;
}

int main(){
	freopen("data.txt", "r", stdin);
	
	Graph g, T;
	int i, u, v, w, n, m, j;
	scanf ("%d%d", &n,&m);
	
	init_graph(&g, n, m);
	init_graph(&T, n, m);
	
	for(i=1;i<=m;++i){
		scanf ("%d%d%d", &u, &v, &w);
		add_edge(&g, u,v,w);
	}
	
	printf ("\n Do thi da nhap: \n");
	for(j=1;j<=n;++j){
		for(i=1;i<=n;++i){
			if(g.edge[j][i] != NO_EDGE)printf("(%d, %d): %d\n", j, i,g.edge[j][i]);
		}
	}
	
	printf ("\n Tong duong di ngan nhat la: %d\n", Prim(g, &T));
	for(j=1;j<=n;++j){
		for(i=1;i<=n;++i){
			if(T.edge[j][i] != NO_EDGE)printf("(%d, %d): %d\n", j, i,T.edge[j][i]);
		}
	}
	
	printf ("\n PRIM 2 \nTong duong di ngan nhat la: %d\n", Prim2(g, &T));
	for(j=1;j<=n;++j){
		for(i=1;i<=n;++i){
			if(T.edge[j][i] != NO_EDGE)printf("(%d, %d): %d\n", j, i,T.edge[j][i]);
		}
	}
	
	return 0;
}
