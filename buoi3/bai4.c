#include <stdio.h>

#define INFINITE 999999
#define NONE -1234

typedef struct{
	int x, y;
	int w;
}Edge;

typedef struct{
	int n,m;
	Edge edge[1000];
}Graph;

int pi[101], p[101], mark[101];

void init_graph(Graph *g, int n){
	g->m = 0;
	g->n = n;
}

void add_edge(Graph *g, int x, int y, int w){
	++(g->m);
	g->edge[g->m].x = x;
	g->edge[g->m].y = y;
	g->edge[g->m].w = w;
}

Graph readFromFile(char* filename){
	Graph g;
	int i, n, m, x, y, w;
	
	FILE* f= fopen(filename, "r");
	
	fscanf(f,"%d%d", &n, &m);
	init_graph(&g, n);
	
	for(i=1;i<=m;++i){
		fscanf(f,"%d%d%d", &x, &y, &w);
		add_edge(&g, x, y, w);
	}
	
	fclose(f);
	
	return g;
}

void bellman_ford(Graph g, int s){
	int i, j, x, y, w, n=g.n;
	
	for(i=1;i<=n;++i){
		pi[i]= INFINITE;
		p[i] = NONE;
	}
	
	pi[s]= 0;
	p[s] = -1;
	
	for(i=1;i<n;++i){
		//	xet lan luot qua CAC CUNG
		for(j=1;j<=g.m;++j){
			x= g.edge[j].x;
			y= g.edge[j].y;
			w= g.edge[j].w;
			
			if(pi[x] + w < pi[y]){
				pi[y]= pi[x] + w;
				p[y] = x;
			}
		}
	}
}

void findStreet(int c, int old){
	if(c!=-1){
		int temp= c;
		c= p[c];
		findStreet(c, old);
		printf("%d", temp);
		if(old!=temp) printf(" -> ");
	}
}

int main(){
	Graph g= readFromFile("dothicotrongso_bai4.txt");
	int i, start= 1, end= 8;
	
	bellman_ford(g, 1);
	
	for(i=1;i<=g.n;++i){
		printf ("pi[%d] = %4d | p[%d] = %4d\n", i, pi[i], i, p[i]);
	}
	
	findStreet(end, end);
	
	return 0;
}
