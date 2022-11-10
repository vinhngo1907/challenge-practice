#include <stdio.h>
#include <stdlib.h>
#include "list.h"

#define MAX_V 101

typedef struct {
	int n;	//	so dinh
	int A[MAX_V][MAX_V];
}Graph;		//cau truc dinh - dinh

//	Khai bao ham
void init_graph(Graph*, int);
void add_edge(Graph*, int, int);
int adjacent(Graph, int, int);
int degree(Graph, int);
List neighbors(Graph, int);
void duyetdequy(Graph, int);

int* mark;
void init_mark(int* m, int n){
	int i;	
	for(i=1;i<=n;++i){
		m[i] = 0;
	}
}

Graph readFile(char* fileName){
	Graph g;
	int m, n, i, x, y;
	
	FILE* f = fopen(fileName, "r");
	
	fscanf(f, "%d%d", &n,&m);
	mark= (int*) malloc((n+1)*sizeof(int));
	init_mark(mark, n);
	init_graph(&g, n);
	
	for(i=1;i<=m;++i){
		fscanf(f, "%d%d", &x, &y);
		add_edge(&g, x, y);
	}	
	fclose(f);
	return g;
}

void init_graph(Graph *g, int n){
	int i, j;
	
	g->n = n;
	for(i=1;i<=n;++i){
		for(j=1;j<=n;++j){
			g->A[i][j] = 0;
		}
	}
}

void add_edge(Graph *g, int x, int y){
	g->A[x][y] += 1; 
	//g->A[y][x] += 1;
}

int adjacent(Graph g, int x, int y){
	return 0!=g.A[x][y];
}

int degree(Graph g, int x){
	int i, degree = 0;
	
	for(i=1; i<=g.n;++i){
		if(adjacent(g, x, i)){
			++degree;
		}
	}
	return degree;
}

List neighbors(Graph g, int x){
	List l; make_null(&l);
	int i;
	
	for(i=1;i<=g.n;++i){
		if(adjacent(g, x, i)){
			push_back(&l, i);
		}
	}
	return l;
}

void duyetdequy(Graph g, int x){
	if(mark[x]) return;
	else{
		mark[x] = 1;
		
		printf ("%4d", x);
		List l; make_null(&l);
		l= neighbors(g, x);
		int i;
		for(i=1; i<=l.size;++i){
			duyetdequy(g, element_at(&l, i));
		}
	}
}
