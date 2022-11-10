#include <stdio.h>

#define MAX_V 101
#define MAX_E 101

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

int member(List* l, ElementType x){
	int i, len= l->size;
	for(i=1;i<=len;++i){
		if(x==element_at(l, i)) return 1;
	}
	return 0;
}

typedef struct{
	int n, m; // n: so dinh, m: so cung
	
	//Bang luu quan de lien thuoc dinh cung
	int A[MAX_V][MAX_E];
}Graph;

/*	Khai bao ham	*/
void init_graph(Graph*, int, int);
void add_edge(Graph*, int ,int, int);
int adjacent(Graph, int, int);
int degree(Graph, int);
List neighbors(Graph*, int);

int main(){
	Graph G;
	int n, m, u, v, w, e, maxidx= 0, maxv= 0;
	scanf("%d%d", &n, &m);
	init_graph(&G, n, m);
	
	for (e = 0; e < m; e++) {
		scanf("%d%d", &u, &v);
		add_edge(&G, e, u, v);
	}
	
	for (v = 1; v <= n; v++){
		printf ("\n %d-%d", v, degree(G,v));
		if(degree(G, v)>maxv){
			maxv = degree(G, v);
			maxidx= v;
		}
	}
	
	printf ("\n %d %d", maxidx, maxv);	
	return 0;
}

void init_graph(Graph* g, int n, int m){
	g->m = m; g->n= n;
	
	int i, j;
	for(i=1;i<=n;++i){
		for(j=1;j<=m;++j){
			g->A[i][j]= 0;
		}
	}
}

void add_edge(Graph* g, int e,int x, int y){
	g->A[x][e] = 1;
	g->A[y][e] = 1;
}

int adjacent(Graph g, int x, int y){
	int e;
	for(e=1;e<=g.m;++e){
		if(g.A[x][e] && g.A[y][e]) return 1;
	}
	return 0;
}

int degree(Graph g, int x){
	int e, deg= 0;
	for(e=1;e<=g.m;++e){
		if(g.A[x][e]) ++deg;
	}
	return deg;
}

List neighbors(Graph *g, int x){
    List l, l2; make_null(&l);make_null(&l2);
    int i, found= 0, j, temp[100], n= 0, e;
    
    for(i=1;i<=g->n;++i){
    	for(e=1;e<=g->m && !found;++e){
			if(g->A[x][e] && g->A[i][e]) found= 1;
		}
		
    	if(found && i!=x){
    		for(j=1;j<=n;++j){
				if(i==temp[j]) continue;
			}
    		temp[++n]= i;
    	}
    }
    
    for(i=1;i<=n;++i){
        for(j=1;j<=n-i;++j){
            if(temp[j]>temp[j+1]){
                int tmp = temp[j];
                temp[j] = temp[j+1];
                temp[j+1] = tmp;
            }
        }
    }
    
    for(i=1;i<=n;++i) push_back(&l, temp[i]);
    
    return l;
}
