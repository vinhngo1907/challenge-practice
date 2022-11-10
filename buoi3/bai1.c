#include <stdio.h>

#define NO_EDGE -999
#define INFINITE 999999
#define MAX_N 101

typedef struct{
	int n;
	int A[MAX_N][MAX_N];
} Graph;

int mark[MAX_N],	//	luu mot dinh da duoc xet chua
	pi[MAX_N],		//	luu do dai ngan nhat den thoi diem xet
	p[MAX_N];		//	luu dinh truoc cua dinh dang xet

void init_graph(Graph *g, int n){
	int i, j;
	
	g->n = n;
	for(i=1;i<=n;++i){
		for(j=1;j<=n;++j){
			g->A[i][j] = NO_EDGE;
		}
	}
}

Graph readFromFile(char* filename){
	Graph g;
	int i, n, m, x, y, w;
	FILE* f= fopen(filename, "r");
	
	fscanf(f, "%d%d", &n, &m);
	init_graph(&g, n);
	
	for(i=1;i<=m;++i){
		fscanf(f, "%d%d%d", &x, &y, &w);
		g.A[x][y] = w;	// truong hop do thi CO HUONG
		//g.A[y][x] = w;  // neu VO HUONG thi them dong nay
	}
	
	fclose(f);
	return g;
}

void Dijktra(Graph g, int x){
	int i, j, n=g.n, idx= -1, min_pi;
	for(i = 1; i <= n; ++i)
	{
		pi[i] = INFINITE;
		p[i] = -1;
		mark[i] = 0;
	}
	
	p[x] = -1;
	pi[x] = 0;
	
	for(i=1;i<n;++i){
		//	tim do dai ngan nhat trong cac canh chua danh dau
		min_pi= INFINITE;		
		for(j=1;j<=n;++j){
			if(!mark[j] && pi[j]<min_pi){
				min_pi= pi[j];
				idx = j;
			}
		}
		
		mark[idx]= 1;// danh dau de khong di lai no nua vi co dinh khac tu goc di den no la ngan nhat roi
		//	xet va/hoac cap nhat cac dinh ke cua no
		for(j=1;j<=n;++j){
			if((g.A[idx][j] != NO_EDGE) && !mark[j] && pi[j]>pi[idx]+g.A[idx][j]){				
				pi[j] = pi[idx]+g.A[idx][j];
				p[j]= idx;
			}
		}
	}	
}

int main(){
	Graph g= readFromFile("dothicotrongso.txt");
	int i;
	
	Dijktra(g, 1);
	for(i=1;i<=g.n;++i){
		printf ("\tpi[%d] = %3d | p[%d] = %d\n", i, pi[i], i, p[i]);
	}
	
	return 0;
}
