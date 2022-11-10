#include<stdio.h>
#define Max_Vertexs 100
#define Max_Edges 500

typedef struct{
	int n,m;
	int A[Max_Vertexs][Max_Edges];	
}Graph;

void init_graph(Graph *G, int n, int m)
{
	int i,j;
	G->n = n;
	G->m = m;
	for(i = 1; i <= n; i++)
	{
		for(j = 1; j <= m; j++)
		{
			G->A[i][j] = 0;
		}
	}
}

void add_edge(Graph *G, int e, int x, int y)
{
	G->A[x][e] = 1;
	G->A[y][e] = 1;
}

int Adjacent(Graph *G, int x, int y)
{
	int e;
	for(e = 1; e <= G->m; e++)
	{
		if(G->A[x][e] == 1 && G->A[y][e] == 1) return 1;
	}
	return 0;
}

int degree(Graph *G, int x)
{
	int e,deg = 0;
	for(e = 1; e <= G->m; e++)
	{
		if(G->A[x][e] == 1) deg++;
	}
	return deg;
}
void deg_vertexs(Graph *G)
{
	printf("\n\t\tBac Cua Cac Dinh\t\t\n");
	int v;
	for(v = 1; v <= G->n; v++)
	{
		printf("Deg[%d] = %d\n",v,degree(G,v));
	}
}

int BacLonNhat(Graph *G,int n) {
	int max = 0,Bac,i,j;
	for(i = 0; i<n; i++) 
	{
		Bac = 0;
		for(j = 0; j<n; j++)
		if(G->A[i][j]>0)
		{
			Bac++;
			if(Bac > max) max = Bac;
		}
	}	
	return max;
}
void DinhBacLonNhat(Graph *G, int n){
	int max = 0, Bac,x,y,i,j;
	for(x = 1 ; x <= n; x++)
	{
		Bac = degree(G,x);
		if(Bac > max) max = Bac;
	}
	int bac1 = 0, bac2 = 0;
	for(i = 1; i <= n; i++)
	{
		bac1 = degree(G,i);
		for(j = 1; j <= n; j++)
		{
			bac2 = degree(G,j);
			if(bac1 == max && bac2 == max)
			{
				if(i < j) printf("Dinh : %d, bac %d\n",i,max);
				else
				{
					printf("Dinh : %d, bac %d\n",j,max);
				}
			}
		}
	}
}

int main(){
	freopen("dothi.txt", "rt", stdin);
	Graph G;
	int n, m, u, v, i,j, e,w, max = 0, Bac,x,y;
	scanf("%d%d", &n, &m);
	init_graph(&G, n, m);
	
	for (e = 1; e <= m; e++) {
		scanf("%d%d", &u, &v);
		add_edge(&G,e, u, v);
	}
	for(x = 1 ; x <= n; x++)
	{
		Bac = degree(&G,x);
		if(Bac > max) max = Bac;
	}
	int bac1 = 0, bac2 = 0;
	for(i = 1; i <= n; i++)
	{
		bac1 = degree(&G,i);
		for(j = 1; j <= n; j++)
		{
			bac2 = degree(&G,j);
			if(bac1 == max && bac2 == max)
			{
				if(i < j) printf("%d%d\n",i,max);
				else
				{
					printf("%d%d\n",j,max);
				}
			}
		}
	}
	/*
	for(w = 1; w <= n; w++)
	{
		printf("Deg[%d] = %d\n",w,degree(&G,w));
	}*/
//	DinhBacLonNhat(&G,n);
	return 0;
}
