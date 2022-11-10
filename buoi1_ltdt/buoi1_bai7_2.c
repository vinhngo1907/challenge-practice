#include <stdio.h>
#include "list.h"

#define MAX_VERTICES 100

typedef struct {
	int n; /* n: so dinh */
	/* mang danh sach cac dinh ke */
	List adj[MAX_VERTICES];
} Graph;

/*	Khai bao cac ham	*/
void init_graph(Graph*, int);
void add_edge(Graph*, int, int);
int adjacent(Graph*, int, int);
int degree(Graph*, int);

int main(){
	Graph G;
	int n, m, e, u, v, y;
	
	FILE* f = fopen("dothi.txt", "r");
	fscanf(f, "%d%d", &n, &m);	
	init_graph(&G, n);
	
	for(e=1;e<=m;++e){
		fscanf(f, "%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	
	for (v = 1; v <= n; v++){
		printf("deg(%d) = %d\n", v, degree(&G, v));
	}
	
	return 0;
}

/* Khoi tao do thi G co n dinh */
void init_graph(Graph* G, int n) {
	int i, j;
	G->n = n;
	for (i = 1; i <= n; i++){
		make_null(&G->adj[i]);
	}
}

/* Them cung e = (x, y) vao do thi G */
void add_edge(Graph* G, int x, int y) {
	push_back(&G->adj[x], y); //y ke v?i x
	push_back(&G->adj[y], x); //x ke voi y
}

/* Kiem tra y co ke voi x khong */
int adjacent(Graph* G, int x, int y) {
	int j;
	for (j = 1; j <= G->adj[x].size; j++){
		if (element_at(&G->adj[x], j) == y){
			return 1;
		}
	}
	return 0;
}

/* Tinh bac cua dinh x: deg(x) */
int degree(Graph* G, int x) {
	return G->adj[x].size;
}
