#include <stdio.h>
#include "stack.h"
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
void depth_first_search(Graph*);

int main(){
	Graph G;
	int n, m, e, u, v;
	
	FILE* f = fopen("dothi.txt", "r");
	fscanf(f, "%d%d", &n, &m);	
	init_graph(&G, n);
	
	for(e=1;e<=m;++e){
		fscanf(f, "%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	
	for (v = 1; v <= n; v++)
	printf("deg(%d) = %d\n", v, degree(G, v));
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

/* Duyet do thi theo chieu sau */
void depth_first_search(Graph* G) {
	Stack frontier;
	int mark[MAX_V];
	
	make_null_stack(&frontier);
	/* Khoi tao mark, chua dinh nao duoc xet */
	int j;
	for (j = 1; j <= G->n; j++){
		mark[j] = 0;
	}
	
	/* Dua 1 vào frontier vi ta de duyet tu 1 nen danh dau la no da duyet roi*/
	push(&frontier, 1);
	mark[1] = 1;
	
	/* Vong lap chinh dung de duyet */
	while (!empty(&frontier)) {
		/* Lay phan tu dau tien trong frontier ra */
		int x = top(&frontier); pop(&frontier);
		printf("Duyet %d\n", x);
		/* Lay cac dinh ke cua no */
		List list = neighbors(G, x);
		/* Xet cac dinh ke cua no */
		for (j = 1; j <= list.size; j++) {
			int y = element_at(&list, j);
			if (mark[y] == 0) {
				mark[y] = 1;
				push(&frontier, y);
			}
		}
	}
}
