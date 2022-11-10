#include <stdio.h>

#define MAX_V 101

/* KHAI BAO VA DINH NGHIA CTDL DANH SACH */
#define MAX_ELEMENTS 100

typedef int ElementType;
typedef struct {
ElementType data[MAX_ELEMENTS];
	int size;
} List;
/* Tao danh sach rong */
void make_null(List* L) {
	L->size = 0;
}
/* Them mot phan tu vao cuoi danh sach */
void push_back(List* L, ElementType x) {
	L->data[L->size] = x;
	L->size++;
}
/* Lay phan tu tai vi tri i, phan tu bat dau o vi tri 1
*/
ElementType element_at(List* L, int i) {
	return L->data[i-1];
}
/* Tra ve so phan tu cua danh sach */
int count_list(List* L) {
	return L->size;
}

void copy_list(List* src, List* des){
	des->size = src->size;
	int i;
	for(i=0;i<src->size;++i){
		des->data[i] = src->data[i];
	}
}

//	(list)(end)

typedef struct {
	int n;
	int A[MAX_V][MAX_V];
}Graph;

int rank[MAX_V];

void ranking(Graph *G){
	int d[MAX_V], x, u, i;
	List S1, S2;
	
	//	khoi tao
	for(i=1;i<=G->n;++i){
		d[i] = 0;
	}
	
	for(u=1;u<=G->n;++u){
		for(x=1;x<=G->n;++x){
			if(G->A[u][x] != 0){
				++d[x];
			}
		}
	}
	
	make_null(&S1);
	for(i=1;i<=G->n;++i){
		if(d[i]==0){
			push_back(&S1, i);
		}
	}
	
	//	tim hang
	int k=0;
	while(S1.size!=0){
		make_null(&S2);
		
		for(i=1;i<=S1.size;++i){
			u= element_at(&S1, i);
			rank[u] = k;
			
			for(x=1;x<=G->n;++x){
				if(G->A[u][x] != 0){
					--d[x];
					
					if(0==d[x]){
						push_back(&S2, x);
					}
				}
			}
		}
		++k;
		copy_list(&S2, &S1);
	}
}

void init_graph(Graph* G, int n){
	G->n = n;
	int i,j;
	for(i=1;i<=n;++i){
		for(j=1;j<=n;++j){
			G->A[i][j] = 0;
		}
	}
}

int main(){
	freopen("else.txt", "r", stdin);
	
	Graph G;
	int n, m, i, x, y;
	
	scanf("%d%d", &n, &m);
	
	init_graph(&G, n);
	for(i=1;i<=m;++i){
		scanf("%d%d", &x, &y);
		G.A[x][y] = 1;
	}
	
	ranking(&G);
	for(i=1;i<=G.n;++i){
		printf ("%d\n", rank[i]);
	}
	return 1;
}
