#include <stdio.h>
#include "list.h"

#define MAX_V 101
typedef struct{
	int n;
	int A[MAX_V][MAX_V];
}Graph;

void init_graph(Graph* G, int n){
	G->n = n;
	
	int i, j;
	for(i=1;i<=n;++i){
		for(j=1;j<=n;++j){
			G->A[i][j]= 0;
		}
	}
}

void add_edge(Graph* g, int x, int y){
	g->A[x][y] = 1;
}

int d[MAX_V];

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
	ranking(&g);
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
	
	return L;
}

int main(){
	//	1. doc do thi
	freopen("tochucthicong.txt","r", stdin);
	
	Graph g;
	int n, i, j, x;
	scanf("%d", &n);
	init_graph(&g, n+2);
	d[n+1]= d[n+2] = 0;
	
	int out[n];
	for(i=1;i<=n;++i){
		out[i] = 0;
	}
	for(i=1;i<=n;++i){
		scanf("%d", &d[i]);
		int inp=0;
		
		do{
			scanf("%d", &x);
			if(x>0){
				add_edge(&g, x, i);
				inp=1;
				out[x] = 1;
			}
		}while(x>0);
		
		if(!inp){
			printf ("\n Dinh co hang vao bang 0: %d\n", i);
		}
	}
	printf ("\n Dinh co dau ra bang 0: ");
	for(i=1;i<=n;++i){
		if(!out[i]) printf("%d", i);
	}
	printf ("\n");
	
	//	2. them cung noi alpha voi cac dinh co bac vao bang 0
	for(i=1;i<=n;++i){
		int deg_inp=0;
		for(j=1;j<=n;++j){
			if(g.A[j][i] != 0) ++deg_inp;
		}
		
		if(0==deg_inp){
			add_edge(&g, n+1, i);
		}
	}	
	
	//	3. them cung noi beta voi cac dinh co bac ra bang 0
	for(i=1;i<=n;++i){
		int deg_out=0;
		for(j=1;j<=n;++j){
			if(g.A[i][j] != 0) ++deg_out;
		}
		
		if(0==deg_out){
			add_edge(&g, i, n+2);
		}
	}
	
	//	4. Topo - sort va luu vao L
	List L = topo(g);
	
	//	5. Tinh t[u] - thoi gian som nhat
	int t[n+3], T[n+3];
	
	for(i=1;i<=n+2;++i){
		t[i] = -1;// vo cung
		T[i] = 9999;
	}
	
	t[n+1] = 0;
	for(j=1;j<=L.size;++j){
		x= element_at(&L, j);
//		t[x] = 9999;//	vo cung
		for(i=1;i<=g.n;++i){
			if(g.A[i][x] != 0){
				t[x] = (t[x] > t[i] + d[i])?t[x]:(t[i]+ d[i]);
			}
		}
	}
	
	//	6. Tinh T[u] - thoi gian cham nhat
	T[n+2] = t[n+2];
	for(i= L.size-1;i>0;--i){
		x = element_at(&L, i);
//		T[x] = -1;
		for(j=1;j<=g.n;++j){
			if(g.A[x][j] > 0){
				T[x] = (T[x]  < T[j] - d[x])?T[x]:(T[j] - d[x]);
			}
		}
	}
	
	for(i=1;i<=n+2;++i){
		printf ("t[%d] = %d | T[%d] = %d\n", i, t[i],i, T[i]);
	}
	
	//	tim duong Grant
	int maxGrant=1, grant[n+3];
	for(i=1;i<=n;++i){
		if(t[i] == T[i]){
			grant[maxGrant++] = i;
		}
	}
	grant[0] = 11;
	grant[maxGrant++] = 12;
	
	printf("\n -> Grant Line: ");
	for(i=1;i<=maxGrant;++i){
		printf("%d", grant[i-1]);
		if(i!=maxGrant) printf("->");
	}
	
	return 1;
}
