#include <stdio.h>
#define INFINITY 9999999
#define NO_EDGE 0

int pi[100][100];
int p[100][100];
int next[100][100];
typedef struct
{
	int n;
	int L[100][100];
} Graph;

void init_graph(Graph *G, int n) {
	int A[100][100];
	G->n = n;
	int i, j;
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++) {
			G->L[i][j] == NO_EDGE;
		}
	}
}
void add_edge (Graph *G, int u, int v, int w) {
	G->L[u][v] = w;
}
void Floyd_Warshall (Graph *G) {
	int i, j, k;
	for (i = 1; i <= G->n; i++) {
		for (j = 1; j <= G->n; j++) {
			pi[i][j] = INFINITY;
			next[i][j] = -1;
		}
	}
	for (i = 1; i <= G->n; i++)
		pi[i][i] = 0;
	for (i = 1; i <= G->n; i++)
		for (j = 1; j <= G->n; j++)
		{
			if (G->L[i][j] != NO_EDGE) {
				pi[i][j] = G->L[i][j];
				next[i][j] = j;
			}
		}
	for (k = 1; k <= G->n; k++)
		for (i = 1; i <= G->n; i++)
			for (j = 1; j <= G->n; j++)
				if (pi[i][k] + pi[k][j] < pi[i][j] && pi[i][k] != INFINITY && pi[k][j] != INFINITY) {
					pi[i][j] = pi[i][k] + pi[k][j];
					next[i][j] = next[i][k];
				}
	for (i = 1; i <= G->n; i++)
		for (j = 1; j <= G->n; j++){
			if (pi[i][j] == INFINITY)
				printf ("%d -> %d: oo\n", i, j);
			else printf ("%d -> %d: %d\n", i, j, pi[i][j]);
		}
}
int main() {
	freopen("dothi.txt", "r", stdin);
	Graph G;
	int n, m, u, v, w, i;
	scanf ("%d%d", &n, &m);
	init_graph(&G, n);
	for (i = 1; i <= m; i++){
		scanf ("%d%d%d", &u, &v, &w);
		add_edge(&G, u, v, w);
	}
	Floyd_Warshall(&G);
}

