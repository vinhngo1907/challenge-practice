#include <stdio.h>
#include <stdlib.h>
#define Max_Elements 100
//Danh sach
typedef int ElementType;
typedef struct{
	ElementType Data[Max_Elements];
	int size;
}List;

void makenull_list(List *L)
{
	L->size = 0;
}

int empty_list(List *L)
{
	return (L->size == 0);
}

void push_back(List *L, int x)
{
	L->size++;
	L->Data[L->size] = x;
}

ElementType element_at(List *L, int i)
{
	return L->Data[i];
}

int count_list(List *L)
{
	return L->size;
}
// Kiem tra x co thuoc danh sach L
int members(List *L, ElementType x)
{
	int i;
	for(i = 1; i <= L->size; i++)
	{
		if(x == element_at(L,i)) return 1;
	}
	return 0;	
}
void copy_list(List *src, List *des)
{
	makenull_list(src);
	src->size = des->size;
	int i;
	for(i = 1;i <= des->size;i++)
	{
		src->Data[i] = des->Data[i];
	}
}
#define Max_V 100
#define INF 999
#define NO_EDGE -1
typedef struct{
	int n,m;
	int edge[Max_V][Max_V];
}Graph;

void init_graph(Graph *G, int n, int m)
{
	G->n = n;
	G->m = m; int i,j;
	for(i = 1; i <= n; i++)
	{
		for(j = 1; j <= n; j++)
		{
			G->edge[i][j] = NO_EDGE;		
		}
	}	
}
void add_edge(Graph *G, int u, int v, int w)
{
	G->edge[u][v] = w;
	G->edge[v][u] = w;
}
int adjacent(Graph *G, int u, int v)
{
	return G->edge[u][v] != NO_EDGE;
}
int mark[Max_V];
int distangeForm(int u, List *L, Graph *G)
{
	int v,i,min_v = -1;
	int min_dis = INF;
	for( i =1 ; i<= L->size; i++)
	{
		v = element_at(L,i);
		if(adjacent(G,u,v) && min_dis > G->edge[u][v])
		{
			min_dis = G->edge[u][v];
			min_v = v;
		}
	}
	return min_v;
}
int Prim(Graph *g, Graph *T){
	init_graph(T, g->n, g->m);
	List S; makenull_list(&S);
	int i,u;
	for( i=1;i <= g->n; ++i){
		mark[i] = 0;
	}
	push_back(&S, 1);
	mark[1] = 1;
	int sum= 0;
	for(i = 1; i < g->n; ++i){ // them vao n -1 dinh con lai
		int min_dis= INF, min_u, min_v;
		for(u = 1; u <= g->n; ++u){ // quet lai tat ca cac dinh
			if(!mark[u]){
				int v= distangeForm(u, &S, g);
				if(v != -1 && min_dis > g->edge[u][v]){
					min_dis = g->edge[u][v];
					min_u= u;
					min_v= v;
				}
			}
		}
		// dua vao S
		mark[min_u] = 1;
		push_back(&S, min_u);
		sum += min_dis;
		add_edge(T, min_u, min_v, min_dis);
	}
	return sum;
}
int pi[Max_V], p[Max_V];
/*int Prim2(Graph *g, Graph* T)
{
	init_graph(T, g->n, g->m);
	int i, j;
	for(i=1;i<=g->n;++i){
		pi[i] = 9999;
	}
	pi[1] = 0;
	for(i=1;i<=g->n;++i){ // gan khoi tao cho dinh 1
		if(g->edge[1][i] != NO_EDGE){
			pi[i] = g->edge[1][i];
			p[i] = 1;
		}
	}
	for(i=1;i<=g->n;++i){
		mark[i] = 0;
	}
	mark[1] = 1;
	int sum = 0, u;
	for(i=1;i < g->n ; ++i){
		int min_dis = 9999, min_u;
		for(u= 1; u <= g->n ; ++u){
			if(!mark[u] && pi[u] < min_dis){
				min_dis = pi[u];
				min_u = u;
			}
		}
		u = min_u;
		mark[min_u] = 1;
		sum += min_dis;
		add_edge(T, min_u, p[min_u],min_dis);
		// cap nhat lai pi va p cua cac dinh ke cua u
		for(j= 1; j<=g->n;++j){
			if(g->edge[u][j] != NO_EDGE && !mark[j]){
				if(pi[j] > g->edge[u][j]){
					pi[j] = g->edge[u][j];
					p[j] = u;
				}
			}
		}
	}
	return sum;
}
*/
void swap(int* x, int* y){
	int temp= *x;
	*x= *y;
	*y = temp;
}
int main(){
	freopen("prim.txt","rt",stdin);
	Graph G,T;
	int n,m,u,v,i,w,j;
	scanf("%d%d",&n,&m);
	init_graph(&G,n,m);
	init_graph(&T, n, m);
	for(i = 1; i <= m; ++i)
	{
		scanf("%d%d%d",&u,&v,&w);
		add_edge(&G,u,v,w);
	}
	printf("%d\n",Prim(&G,&T));
	for(j=1;j<=n;++j){
		for(i=j+1;i<=n;++i){
		if(T.edge[j][i] != NO_EDGE)printf("%d %d %d\n", j, i,T.edge[j][i]);
		}
	}
	return 0;
}
