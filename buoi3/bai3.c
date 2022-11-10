#include <stdio.h>

#define NO_EDGE -9
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
	int i, j, r, c, n, w, p[6];
	
	/*
		.	p1	.
		p2	p3	p4
		.	p5	.
	*/
	
	FILE* f= fopen(filename, "r");
	
	fscanf(f, "%d%d", &r, &c);
	n= r*c;
	init_graph(&g, n);
	
	for(i=1;i<=r;++i){
		for(j=1;j<=c;++j){
			fscanf(f, "%d", &w);
			p[3]= (i-1)*c+j;
			p[1]= p[3] - c; p[5] = p[3] + c;
			p[2]= p[3] - 1; p[4] = p[3] + 1;
			if(p[1]>0) g.A[p[1]][p[3]]= w; if(p[2]>0) g.A[p[2]][p[3]]= w;
			if(p[4]<=c) g.A[p[4]][p[3]]= w; if(p[5]<=r) g.A[p[5]][p[3]]= w;
		}
	}
	
	fclose(f);
	
	return g;
}

void Dijktra(Graph g, int x){
	int i, j, n=g.n, idx= -1, min_pi;
	for(i=1;i<=n;++i){
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
				idx= j;
			}
		}
		
		mark[idx]= 1;	// danh dau de khong di lai no nua vi co dinh khac tu goc di den no la ngan nhat roi
						// neu di nua se tao thanh vong tron
		//	xet va/hoac cap nhat cac dinh ke cua no
		for(j=1;j<=n;++j){
			if((g.A[idx][j]!=NO_EDGE)&& !mark[j] && pi[j]>pi[idx]+g.A[idx][j]){				
				pi[j] = pi[idx]+g.A[idx][j];
				p[j]= idx;
			}
		}
	}	
}

void timduong(int c, int old){
	if(c!=-1){
		int temp= c;
		c= p[c]; // lay vi tri cha no
		timduong(c, old);
		printf ("%d", temp);
		if(old!=temp) printf(" -> ");
	}else return;
}

int main(){
	Graph g= readFromFile("matranso.txt");
	int i, j, start= 1, end = g.n;;
	
	Dijktra(g, start);
//	timduong(end, end);

	printf ("\ngia tri: %d", pi[g.n]);
	
	return 0;
}
