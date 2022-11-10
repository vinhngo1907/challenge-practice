#include <stdio.h>
#include <conio.h>
#include "queue.h"

#define MAXN 101
#define NO_EDGE 0
#define INF 99999

typedef struct{
	int F[MAXN][MAXN], C[MAXN][MAXN];
	int n;
}Graph;

typedef struct{
	int dir;	//	co duyet chua
	int pre;	//	dinh truoc
	int signma;	//	gia tri tang luong
}Label;

Label labels[MAXN];

void init_flow(Graph* g, int n){
	g->n = n;
	int i, j;
	for(i=1; i<=n;++i){
		for(j=1;j<=n;++j){
			g->F[i][j] = NO_EDGE;
			g->C[i][j] = NO_EDGE;
		}
	}
}

int min(int a, int b){
	return  (a<b)?a:b;
}

int FordFulkerson(Graph *g, int s, int t){
	//	I
	//init_flow(g, g->n);
	
	//	II Lap
	Queue q;
	
	int i, j, sum_flow= 0, n= g->n;
	do{
		int  found= 0;
		//b1
		//xoa tat ca cac nut
		for(i=1;i<=n;++i){
			labels[i].dir = 0;
		}
		
		//gan nhan cho s
		labels[s].dir = 1;
		labels[s].pre = s;
		labels[s].signma = INF;
		make_null_queue(&q);
		push(&q, s);
		
		while(!empty(&q)){
			int v, u= top(&q); pop(&q);
			for(v=1;v<=n;++v){
				if(labels[v].dir == 0 && g->C[u][v] != NO_EDGE && g->C[u][v] > g->F[u][v]){
					labels[v].dir = 1;
					labels[v].pre = u;
					labels[v].signma = min(labels[u].signma,g->C[u][v] - g->F[u][v]);
					push(&q, v);
				}
				
				if(labels[v].dir == 0 && g->C[u][v] != NO_EDGE && g->F[v][u] > 0){
					labels[v].dir = -1;
					labels[v].pre = u;
					labels[v].signma = min(labels[u].signma,g->F[v][u]);
					push(&q, v);
				}
			}
			
			if(labels[t].dir != 0){
				found= 1;
				break;
			}
		}
		
		if(found){
			int x= t;
			int signma = labels[t].signma;
			sum_flow += signma;
			
			while(x != s){
				int u= labels[x].pre;
				if(labels[x].dir > 0){
					g->F[u][x] += signma;
				}else{
					g->F[x][u] -= signma;
				}
				
				x= u;
			}
		}else{
			break;
		}
		
	}while(1);
	
	return sum_flow;
}

int main(){
	freopen("luongcucdai.txt", "r", stdin);
	
	Graph g;
	int n, m, u, v, c, i, j;
	
	scanf("%d%d", &n, &m);
	init_flow(&g, n);
	
	for(i=1;i<=m;++i){
		scanf("%d%d%d", &u, &v, &c);
		g.C[u][v] = c;
	}		
	
	printf ("\n Tong luong cuc dai la: %d", FordFulkerson(&g, 1, n));
	
	return 0;
}
