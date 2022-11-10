#include <stdio.h>
#include <stdlib.h>
#define INFINITY 9999999
#define MAX_V 10
#define MAX_E 50
#define NO_EDGE -1

typedef struct{
	int n,m;
	int A[MAX_V][MAX_E];
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
			G->A[i][j] = NO_EDGE;
		}
	}
}
void add_edge(Graph *G, int x, int y,int w)
{
//	G->A[x][y] += 1;
//	G->A[y][x] = 1;
	G->A[x][y] = w;	// truong hop do thi CO HUONG
	G->A[y][x] = w;  // neu VO HUONG thi them dong nay
}

int adjacent(Graph *G, int x, int y)
{
	return G->A[x][y] != 0;
} 
int mark[MAX_V], pi[MAX_V], p[MAX_V];

void dijktra(Graph *G, int s)
{
	int i, j, it;
	for (i = 1; i <= G->n; i++) {
		pi[i] = INFINITY;
		mark[i] = 0;
	}
	pi[s] = 0;
	p[s] = -1; //truoc dinh s không có dinh nào ca
	// lap n hoac n-1 lan deu duoc
	for (it = 1; it <= G->n; it++) 
	{
		//1. Tìm i có mark[i] == 0 va có pi[i] nho nhat
		int min_pi = INFINITY;
		for (j = 1; j <= G->n; j++)
		if (mark[j] == 0 && pi[j] < min_pi) 
		{
			min_pi = pi[j];
			i = j;
		}
		//Ðánh dau i dã xét
		mark[i] = 1;
		//2. Cap nhat pi và p cua các dinh ke cua i (neu thoa)
		for (j = 1; j <= G->n; j++)
		{
			if (G->A[i][j] != NO_EDGE && mark[j] == 0) 
			{
				if (pi[i] + G->A[i][j] < pi[j]) 
				{
					pi[j] = pi[i] + G->A[i][j];
					p[j] = i;
				}
			}
		}	
	}
}
void timduong(Graph *G,int c, int old){
	if(c!=-1)
	{
		int temp= c;
		c = p[c];
		timduong(G,c, old);
		printf("%d", temp);
		if(old!=temp) printf(" -> ");
	}
	else return;
	
}
int findstreet(Graph *G){
	int sum = 0;
	int path[MAX_V]; // luu cac dinh tren duong di
	int k = 0; // So dinh cua duong di
	int current = G->n;
	while (current != -1) {
	path[k] = current; k++;
	current = p[current];
	}
	int i;
	for (i = k-1; i >=0; i--)
	{
		printf(" %d ", path[i]);
	}		
	return G->n;
}
int main(){
	int i, e, n, m, x, y, w,u,v;
	
	freopen("dothi.txt","rt",stdin);
	Graph G;
	scanf("%d%d", &n, &m);
	init_graph(&G, n,m);
	
	for(e = 1; e <= m ; ++e){
		scanf("%d%d%d", &u, &v, &w);
		add_edge(&G,u,v,w);
	}
//	int start = 1, end = G.n;
	dijktra(&G, 1);
	if(pi[n] > 0) 
		printf ("%d", pi[n]);
	else printf("-1");
	for(i = 1; i <=G.n; i++)
	{
		printf("\n\tpi[%d] = %d, p[%d] = %d",i,pi[i],i,p[i]);
	}
	printf("\nDuong di: ");
	timduong(&G,G.n,G.n);
	return 0;
}

