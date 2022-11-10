#include <stdio.h>
#include <stdlib.h>
#include <D:\Thu vien lap trinh\thuvien\ThucHanhBuoi_3\CTDL.h>
#define MAX_V 100
#define MAX_E 500
#define NO_EDGE -1
#define INFINITY 9999999
typedef struct{
	int u,v;
	int w;
}Edge;
typedef struct{
    int n,m;
    Edge edges[1000];
}Graph;
void init_graph(Graph*G,int n){
	G->n = n;
	G->m = 0;
}
void add_edge(Graph*G, int u, int v, int w){
	G->edges[G->m].u =u;
   	G->edges[G->m].v =v;
 	G->edges[G->m].w =w;
   	G->m++;
}

int mark[MAX_V], pi[MAX_V], p[MAX_V];
/*void dijktra(Graph *G, int x)
{
	int i,j,it,min_pi;
	for(i = 1; i <= G->n; i++)
	{
		pi[i] = INFINITY;
		p[i] = -1;
		mark[i] = 0;
	}
	pi[x] = 0;
	p[x] = -1;
	for(it = 1; it <= G->n; it++)
	{
		min_pi = INFINITY;
		for(j = 1; j <= G->n; j++)
		{
			if(!mark[j] && pi[j] < min_pi)
			{
				min_pi = pi[j];
				i = j;
			}
		}
		mark[i] = 1;
		for(j = 1; j <= G->n; j++)
		{
			if(!mark[j] && G->A[i][j] != NO_EDGE && pi[j] > pi[i] + G->A[i][j])
			{
				pi[j] = pi[i] + G->A[i][j];
				p[j] = i;
			}
		}
	}
}*/
void findstreet(Graph *G, int c, int old)
{
	if(c!= -1)
	{
		int tempt = c;
		c = p[c];
		findstreet(G,c,old);
		printf("%d",tempt);
		if(c != old) printf(" -> ");
	}
	else return;
}
#define INFINITY 999999
#define MAXN 1000
void BellmanFord(Graph* G, int s){
	int i, j, it, k;
	for(i=1; i<=G->n; i++){
		pi[i]=INFINITY;
	}
	pi[s]=0;
	p[s]=-1;
	for(it=1; it<G->n; it++)
	{
		for(k=0; k<G->m; k++)
		{
			int u = G->edges[k].u;
			int v = G->edges[k].v;
			int w = G->edges[k].w;
			if(pi[u] + w < pi[v])
			{
				pi[v] = pi[u] + w;
				p[v] = u;
			}
		}
	}
	for(k=0; k<G->m; k++)
	{
		int u = G->edges[k].u;
		int v = G->edges[k].v;
		int w = G->edges[k].w;
		if(pi[u] + w < pi[v])
		{
			printf("negative cycle");
			return;
		}
	}
	printf("ok");
}
void findStreet(int c, int old){
	if(c!=-1){
	int temp= c;
	c= p[c];
	findStreet(c, old);
	printf("%d", temp);
	if(old!=temp) printf(" -> ");
	}
}
int minusCycle(Graph *G){
	int i, j, u, v, w;
	for(i=1;i<G->n;++i){
		for(j=1;j<=G->m;++j){
			u= G->edges[j].u;
			v= G->edges[j].v;
			w= G->edges[j].w;
			if(pi[u]+w<pi[v]){
			return 1;
			}
		}
	}
	return 0;
}
void lietke_minusCycle(Graph g){
	int i, j, u, v, w, cycle=0;
	for(i=1;i<g.n;++i)
	{
		for(j=1;j<=g.m;++j)
		{
			u= g.edges[j].u;
			v= g.edges[j].v;
			w= g.edges[j].w;
			if(pi[u] + w < pi[v]){
				cycle= u;
			}
		}
	}
	if(cycle){
		printf ("%d ", cycle);
		int temp= p[u];
		while(temp!= u){
			printf("%d ", temp);
			char c;
			temp= p[temp];
		}
	}
}
int main(){
	int n,m,e,i,j,u,v,w;
	int start= 1, end= 8;
	freopen("dothi.txt","rt",stdin);
	Graph G;
	scanf("%d%d",&n,&m);
	init_graph(&G,n);
	for(e =1; e <=m; e++)
	{
		scanf("%d%d%d",&u,&v,&w);
		add_edge(&G,u,v,w);
	}
	BellmanFord(&G,1);
	if(minusCycle(&G)){
		printf ("\ncycle\n");
		lietke_minusCycle(G);
	}
	else{
		printf ("\nno cycle\n");
		findStreet(end, end);
	}
	for(i = 1; i <= n; i++)
	{
		printf("\n\tpi[%d] = %d, p[%d] = %d",i,pi[i],i,p[i]);
	}

	return 0;
}
