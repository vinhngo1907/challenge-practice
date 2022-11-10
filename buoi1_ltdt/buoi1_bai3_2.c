#include <stdio.h>

#define MAX_V 101
#define MAX_E 101

typedef struct{
	int n, m; // n: so dinh, m: so cung
	
	//Bang luu quan de lien thuoc dinh cung
	int A[MAX_V][MAX_E];
}Graph;

/*	Khai bao ham	*/
void init_graph(Graph*, int, int);
void add_edge(Graph*, int ,int, int);
int adjacent(Graph, int, int);
int degree(Graph, int);

int main(char argc, char* argv[]){
	
	if(argc<2){
		printf("\n Hay nhap: %s <ten-file>\n", argv[0]);
		return 1;
	}
	
	Graph G;
	int n, m, e, u, v;
	
	FILE* f = fopen( argv[1], "r");
	fscanf(f, "%d%d", &n, &m);	
	init_graph(&G, n, m);
	
	for(e=1;e<=m;++e){
		fscanf(f, "%d%d", &u, &v);
		add_edge(&G, e, u, v);
	}
	
	for (v = 1; v <= n; v++)
	printf("deg(%d) = %d\n", v, degree(G, v));
	return 0;
}

void init_graph(Graph* g, int n, int m){
	g->m = m; g->n= n;
	
	int i, j;
	for(i=1;i<=n;++i){
		for(j=1;j<=m;++j){
			g->A[i][j]= 0;
		}
	}
}

void add_edge(Graph* g, int e,int x, int y){
	g->A[x][e] = 1;
	g->A[y][e] = 1;
}

int adjacent(Graph g, int x, int y){
	int e;
	for(e=1;e<=g.m;++e){
		if(g.A[x][e] && g.A[y][e]) return 1;
	}
	return 0;
}

int degree(Graph g, int x){
	int e, deg= 0;
	for(e=1;e<=g.m;++e){
		if(g.A[x][e]) ++deg;
	}
	return deg;
}
