#include <stdio.h>
#define MAX_EDGES 500

typedef struct  {
	int x, y;
} Edge;

typedef struct {
	int n, m;
	Edge edges[MAX_EDGES];
} Graph;

void init_graph(Graph* G, int n, int m)
{
	G->n = n;
	G->m = 0;
}

void add_edge(Graph* G, int x, int y) 
{
	if(x < 1 || y > G->n) return;
	else
	{
		G->edges[x] = 1;
		G->edges[y] = 1;
	}
}
