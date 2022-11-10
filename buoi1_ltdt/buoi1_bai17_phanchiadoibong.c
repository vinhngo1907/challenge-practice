#include <stdio.h>
#include "list.h"

#define MAX_V 101

/* Mot so bien ho tro */
int mark[MAX_V];
int color[MAX_V];
int fail;

typedef struct{
	int n;//	so dinh
	int A[MAX_V][MAX_V];	//	ma tran dinh ke
}Graph;

/*	Khai bao ham	*/
void init_graph(Graph*, int);
void add_edge(Graph*, int, int);
int adjacent(Graph*, int, int);
List neighbors(Graph*, int);
void colorize(Graph*, int, int);
int is_bigraph(Graph*);
void list_doi_bong(Graph, int*, int);

int main(){
	Graph G;
	int n, m, e, u, v, y;
	
	FILE* f = fopen("doibong.txt", "r");
	fscanf(f, "%d%d", &n, &m);	
	init_graph(&G, n);
	
	for(e=1;e<=m;++e){
		fscanf(f, "%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	
	if(is_bigraph(&G)){
		printf("\n Co the phan chia thanh 2 doi bong nhu sau: \n");
		printf ("\n Doi 1: "); list_doi_bong(G, color, 0);
		printf ("\n Doi 2: "); list_doi_bong(G, color, 1);
	}else{
		printf("\n IMPOSSIBLE");
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
void list_doi_bong(Graph g, int* list,int type){
	int i;
	for(i=1; i<=g.n;++i){
		if(color[i]==type) printf ("%4d", i);
	}
}

/* To mau bang phuong phap de quy */
void colorize(Graph* G, int x, int c) {
	/* Neu dinh a chua co mau thi to no */
	if (color[x] == -1) {
		color[x] = c;
		/* Lay cac dinh ke va to mau cho cac dinh ke bang mau nguoc lai voi c */
		List list = neighbors(G, x);
		int j;
		for (j = 1; j <= list.size; j++) 
		{
			int y = element_at(&list, j);
			colorize(G, y, !c);
		}
	} 
	else /* x da có màu */
	{
		if (color[x] != c) /* 1 dinh bi to mau 2 lan khac chau */
			fail = 1; /* that bai */
	}	
}
//	kiem tra do thi co la do thi phan doi
int is_bigraph(Graph* G) {
	//	khoi tao color, chua dinh nao co mau
	int j;
	for (j = 1; j <= G->n; j++)
		color[j] = -1;
	
	fail = 0;
	colorize(G, 1, 0); /* To mau dinh bang 1 mau den */
	/* Neu khong that bai thi B la do thi phan doi */
	return !fail;
}
