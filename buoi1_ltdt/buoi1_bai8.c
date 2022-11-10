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
List neighbors(Graph* , int);

int main(){
	Graph G;
	int n = 4, v, y;
	init_graph(&G, n);
	add_edge(&G, 1, 2);
	add_edge(&G, 1, 3);
	add_edge(&G, 1, 3);
	add_edge(&G, 3, 4);
	add_edge(&G, 1, 4);
	
	/* Liet ke danh sach ke cua cac dinh */
	for (v = 1; v <= n; v++) {
		List list = neighbors(&G, v);
		printf("Cac dinh ke cua %d: [", v);
		for (y = 1; y <= list.size; y++){
			printf("%d ", element_at(&list, y));
		}
		printf("]\n");
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

/* Tim cac dinh ke cua dinh x */
List neighbors(Graph* G, int x) {
	//Graph G;
	int y;
	List list;
	
	make_null(&list);
	for (y = 1; y <= G->n; y++){
		if (adjacent(G, x, y)){
			push_back(&list, y);
		}
	}
	
	return list;
}
