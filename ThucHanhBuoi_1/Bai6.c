#include <stdio.h>
#define Max_Vertexs 100
#define Max_Edges 500
typedef struct{
	int n;
	int A[Max_Vertexs][Max_Vertexs];
}Graph;

void Init_Graph(Graph *G, int n)
{
	int i,j;
	G->n = n;
	for(i = 1 ; i <= n; i++)
	{
		for(j =1 ; j <= n; j++)
		{
			G->A[i][j] = 0;
		}
	}
}
void Add_Edge(Graph *G, int x, int y)
{
	G->A[x][y] = 1;
	G->A[y][x]  =1;
}

int Adjacent(Graph *G, int x, int y)
{
	return G->A[x][y] != 0;
}

int Degree(Graph *G, int x)
{
	int y,deg = 0;
	for(y = 1; y <= G->n; y++)
	{
		if(G->A[x][y] > 0) deg++;
	}
	return deg;
}

int main(){
	freopen("dt1.txt", "r", stdin); //Khi n?p bài nh? b? dòng này.
	Graph G;
	int n, m, u, v, e,i,j;
	scanf("%d%d", &n, &m);
	Init_Graph(&G, n);
	
	for (e = 1; e <= m; e++) {
		scanf("%d%d", &u, &v);
		Add_Edge(&G, u, v);
	}
	for(i = 1; i <= n; i++)
	{
		for(j = 1; j <= m; j++)
		{
			printf("%d ",G.A[i][j]);
		}
		printf("\n");
	}
	
	return 0;
}
