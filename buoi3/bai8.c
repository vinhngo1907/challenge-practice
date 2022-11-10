#include <stdio.h>

#define INFINITE 9999
#define NO_EDGE -1
#define MAX_N 101

typedef struct{
	int L[MAX_N][MAX_N];
	int n;
}Graph;

int pi[MAX_N][MAX_N], next[MAX_N][MAX_N];

void init_graph(Graph* g, int n){
	int i, j= 1;
	
	g->n = n;
	for(j=1;j<=n;++j){
		for(i=1;i<=n;++i){
			g->L[j][i]= NO_EDGE;
		}
	}
}

Graph readFromFile(char* filename){
	Graph g;
	FILE* f = fopen(filename, "r");
	int i, j, x, y, w, n, m;
	
	fscanf(f, "%d%d", &n, &m);
	init_graph(&g, n);
	
	for(i=1;i<=m;++i){
		fscanf(f, "%d%d%d", &x, &y, &w);
		g.L[x][y] = w;	// co huong
	}
	
	fclose(f);	
	return g;
}

void Floy_Wallson(Graph g){
	int i,j, k;
	
	for(i=1;i<=g.n;++i){
		for(j=1;j<=g.n;++j){
			if(NO_EDGE==g.L[i][j]){
				pi[i][j] = INFINITE;
				next[i][j] = -1;
			}else{
				pi[i][j] = g.L[i][j];
				next[i][j] = j;
			}
		}
	}
	
	for(i=1;i<=g.n;++i){
		pi[i][i] = 0;
	}
	
	for(k=1;k<=g.n;++k){
		for(i=1;i<=g.n;++i){
			for(j=1;j<=g.n;++j){
				if(pi[i][k]+pi[k][j] < pi[i][j]){
					pi[i][j] = pi[i][k]+pi[k][j];
					next[i][j] = next[i][k];
				}
			}
		}
	}
	
}

void getStreet(int start, int end){
	if (start==end) return;
	int nxt = next[start][end];
	printf ("%d", nxt);
	if(nxt!=end) printf(" -> ");
	getStreet(nxt, end);
}

int main(){
	Graph g= readFromFile("dothicotrongso.txt");
	
	Floy_Wallson(g);
	int i, j; char x[255];
	for(i=1;i<=g.n;++i){
		for(j=1;j<=g.n;++j){
			printf ("%d -> %d : ", i, j,i);
			if(pi[i][j]==INFINITE) printf("khong co duong di");
			else {
				if(i!=j) printf ("%d -> ");
				else{
					printf("khong can di dau ca");
				}
				getStreet(i,j);
			}
			printf ("\n");
		}
	}
	
	return 0;
}
