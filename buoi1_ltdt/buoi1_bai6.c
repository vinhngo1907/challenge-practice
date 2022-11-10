#include <stdio.h>
#include "list.h"

#define MAX_V 101

typedef struct{
	int n;//	so dinh
	int A[MAX_V][MAX_V];	//	ma tran dinh ke
}Graph;

/*	Khai bao ham	*/
void init_graph(Graph*, int);
void add_edge(Graph*, int, int);
int adjacent(Graph*, int, int);
List neighbors(Graph*, int);

int main(){
	Graph G;
	int n = 4, v, y;
	init_graph(&G, n);
	add_edge(&G, 1, 2);
	add_edge(&G, 1, 3);
	add_edge(&G, 1, 3);
	add_edge(&G, 3, 4);
	add_edge(&G, 1, 4);
	
	for (v = 1; v <= n; v++){
		printf("deg(%d) = %d\n", v, degree(&G, v));
	}
	
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
	for(i = 1; i <= n; i++){
		for (j = 1; j <= n; j++){
			G->A[i][j] = 0;
		}
	}
}

/* Them cung e = (x, y) vao do thi G */
void add_edge(Graph* G, int x, int y) {
	G->A[x][y] += 1; //y ke voi x
	G->A[y][x] += 1; //x ke voi y
}

/* Kiem tra y co ke voi x khong */
int adjacent(Graph* G, int x, int y) {
	return G->A[x][y] != 0;
}

/* Tinh bac cua dinh x: deg(x), truong hop da cung */
int degree(Graph* G, int x) {
	int y, deg = 0;
	for (y = 1; y <= G->n; y++){
		deg += G->A[x][y];
	}
	return deg;
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
