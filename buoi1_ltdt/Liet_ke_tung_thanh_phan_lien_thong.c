#include <stdio.h>
#include "stack.h"
#include "list.h"

#define MAX_V 101

typedef struct{
	int n; // n la so dinh
	int A[MAX_V][MAX_V];
}Graph;

int mark[MAX_V];

/* Khai bao ham */
void init_graph(Graph*, int);
void add_edge(Graph*, int, int);
int adjacent(Graph*, int , int);
int degree(Graph*, int);
List neighbors(Graph*, int);
int duyetdothi(Graph*, int);
void cungtrung(Graph*, int);

int main(){
	int i, j, n, m, x, y;
	Graph G; List l;
		
	FILE* f = fopen("dothilienthong.txt", "r");
	fscanf(f, "%d%d", &n, &m);	
	init_graph(&G, n);
	
	for(i=1;i<=m;++i){
		fscanf(f, "%d%d", &x, &y);
		add_edge(&G, x, y);
	}
	fclose(f);
	
	for(i=1;i<=G.n;++i){
		printf("\n degree(%d) = %d | thanh phan: ", i, degree(&G, i));
		l = neighbors(&G, i);
		for(j=1;j<=l.size;++j){
			printf ("\t%d", element_at(&l, j));
		}
	}
	
	printf ("\n Duyet do thi: ");
	for(i=1; i<=n;++i){
		if(!mark[i])duyetdothi(&G, i);
		mark[i] = 0;
	}
	
	int nlt= 0;
	for(i=1; i<=n;++i){
		if(!mark[i]){
			printf ("\n Thanh phan lien thong thu %d: ", ++nlt);
			printf (" (co %d phan tu)", duyetdothi(&G, i));
		}
		mark[i] = 0;
	}
	printf ("\n => Vay co tat ca %d thanh phan lien thong.", nlt);
	if(nlt>1) printf("\n => KHONG lien thong.\n");
	else printf("\n lien thong.\n");
	
	printf ("\n Cac cap cung trung nhau: ");	
	for(i=1; i<=n;++i){
		if(!mark[i]) cungtrung(&G, i);
		//mark[0] = 0;
	}
	return 0;
}

void init_graph(Graph* G, int n){
	int i, j;
	G->n = n;
	for(i=1;i<=n;++i){
		for(j=1;j<=n;++j){
			G->A[i][j] = 0;
		}
	}
}

void add_edge(Graph* G, int x, int y){
	G->A[x][y] += 1;
	G->A[y][x] += 1;
}

int adjacent(Graph* G, int x, int y){
	return (G->A[x][y]>0);
}

int degree(Graph* G, int x){
	int i, degree= 0;
	for(i=1;i<=G->n;++i){
		if(adjacent(G, x, i)) degree += G->A[x][i];
	}
	return degree;
}

List neighbors(Graph* G, int x){
	List l;
	int i;
	make_null(&l);
	
	for(i=1;i<=G->n;++i){
		if(adjacent(G, x, i)){
			push_back(&l, i);
		}
	}
	
	return l;
}

int duyetdothi(Graph* G, int x){
	if(mark[x]) return 0;
	else{
		int n= 1;
		printf("%4d", x);
		mark[x] = 1;
		
		List l; int i;
		make_null(&l);
		l = neighbors(G, x);
		for(i=1;i<=l.size;++i){
			n+=duyetdothi(G, element_at(&l, i));
		}
		return n;
	}
}

void cungtrung(Graph* G, int x){
	if(mark[x]) return;
	else{
		mark[x] = 1;
		
		List l; int i;
		make_null(&l);
		l = neighbors(G, x);
		
		for(i=1;i<=l.size;++i){
			//	xet cung cua phan tu dang xet va cac phan tu lan can cua no
			if((G->A[x][element_at(&l, i)]>1) && mark[element_at(&l, i)]==0){
				printf(" %d-%d", x, element_at(&l, i));
			}
		}
		
		for(i=1;i<=l.size;++i){
			cungtrung(G, element_at(&l, i));
		}
	}
}
