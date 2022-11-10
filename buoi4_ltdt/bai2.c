#include <stdio.h>
#include "list.h"

#define MAX_V 101

typedef struct {
	int n;
	int A[MAX_V][MAX_V];
}Graph;

int rank[MAX_V];

void ranking(Graph *G){
	int d[MAX_V], x, u, i;
	List S1, S2;
	
	//	khoi tao
	for(i=1;i<=G->n;++i){
		d[i] = 0;
	}
	
	for(u=1;u<=G->n;++u){
		for(x=1;x<=G->n;++x){
			if(G->A[u][x] != 0){
				++d[x];
			}
		}
	}
	
	make_null(&S1);
	for(i=1;i<=G->n;++i){
		if(d[i]==0){
			push_back(&S1, i);
		}
	}
	
	//	tim hang
	int k=1;
	while(S1.size!=0){
		make_null(&S2);
		
		for(i=1;i<=S1.size;++i){
			u= element_at(&S1, i);
			rank[u] = k;
			
			for(x=1;x<=G->n;++x){
				if(G->A[u][x] != 0){
					--d[x];
					
					if(0==d[x]){
						push_back(&S2, x);
					}
				}
			}
		}
		++k;
		copy_list(&S2, &S1);
	}
}

List topo(Graph g){
	List L;
	make_null(&L);
	
	int maxidx=1, i, j;
	for(i=1;i<=g.n;++i){
		if(rank[i]>maxidx) maxidx= rank[i];
	}
	
	for(i=1;i<=maxidx;++i){
		for(j=1;j<=g.n;++j){
			if(rank[j]==i) push_back(&L, j);
		}
	}
	
	printf ("\n Thu tu Topo: ");
	for(i=1;i<=L.size;++i){
		printf ("%d ", element_at(&L, i));
	}
}

void init_graph(Graph* G, int n){
	G->n = n;
	int i,j;
	for(i=1;i<=n;++i){
		for(j=1;j<=n;++j){
			G->A[i][j] = 0;
		}
	}
}

int main(){
	freopen("data.txt", "r", stdin);
	
	Graph G;
	int n, m, i, x, y;
	
	scanf("%d%d", &n, &m);
	
	init_graph(&G, n);
	for(i=1;i<=m;++i){
		scanf("%d%d", &x, &y);
		G.A[x][y] = 1;
	}
	
	ranking(&G);
	topo(G);
	
	return 1;
}
