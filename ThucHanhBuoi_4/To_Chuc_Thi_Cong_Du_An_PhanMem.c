#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 100
#define MAX_ELEMENTS 100
#define NO_EDGES 0
#define INFINITY 999999
int rank[MAX_VERTICES], d[100];

//do thi
typedef struct {
	int A[100][100];
	int n;
} Graph;

void init_graph(Graph *G, int n) {
	G->n = n;
	int i, j;
	for (i = 1; i <= n; i++) {
		for(j = 1; j <= n; j++)
			G->A[i][j]=NO_EDGES;
	}
}
void add_edge(Graph *G, int x, int y) {
	G->A[x][y] =1;
}
int degree(Graph *G,int x){
int i,j,deg,e;
	deg=0;
	for (i=1;i<=G->n+2;i++)
		 deg+=G->A[i][x];
return deg;
}
/* Khai bao Queue */
#define MAX_ELEMENTS 100
typedef struct {
 int data[MAX_ELEMENTS];
 int front, rear;
} Queue;
void make_null_queue(Queue* Q) {
 Q->front = 0;
 Q->rear = -1;
}
void push(Queue* Q, int x) {
 Q->rear++;
 Q->data[Q->rear] = x;
}
int top(Queue* Q) {
 return Q->data[Q->front];
}
void pop(Queue* Q) {
 Q->front++;
}
int empty(Queue* Q) {
 return Q->front > Q->rear;
}
/*DANH SACH*/
typedef struct {
	int data[MAX_ELEMENTS];
	int size ;
}list;
// tao danh sach rong
void makenull(list* L){
	L->size=0;
}
// them mot phan tu vao cuoi danh sach
void push_back(list* L, int x){
	L->data[L->size]=x;
	L->size++;
}
//lay phan tu tai vi tri i, phan tu bat dau tai vi tri l
int element_at(list* L, int i){
	return L->data[i-1];
}
int count_list (list* L){
	return L->size;
}
/*topo sort*/
void topo_sort(Graph *G,list *L){
	int i,v,deg[100];
	Queue Q;
	make_null_queue(&Q);
	makenull(L);
	for (i=1;i<=G->n;i++){
		deg[i]=degree(G,i);
		if(deg[i]==0)	
			push(&Q,i);
	}
	while(!empty(&Q)){
		int u=top(&Q); pop(&Q);
		push_back(L,u);
		for (i=1;i<=G->n;i++)
			if(G->A[u][i]!=NO_EDGES){
				deg[i]--;
				if(deg[i]==0) push(&Q,i);
			}	
	}

}
int min(int a,int b){
	if(a<b) return a;
	return b;
}
int max(int a,int b){
	if (a>b) return a;
	return b;
}
int main(){
	int n,u,v,x,j,i,work_at,start;
	list L;
	makenull(&L);
	Graph G;
	freopen("tochucthicong.txt","r",stdin);
	scanf("%d", &n);
	init_graph(&G,n+2);
	d[n+1]=0;	
	for (u=1;u<=n;u++){
		scanf("%d",&d[u]);
		do{
			scanf("%d", &x);
			if (x>0) add_edge(&G,x,u);
		}while(x>0);
	}
	scanf("%d%d", &work_at, &start);
		//them cung noi alpha 
	for(u=1;u<=n;u++){
		int deg_neg =0;
		for(x=1;x<=n;x++)
			if(G.A[x][u]>0)
				deg_neg++;
		if(deg_neg ==0 )
			add_edge(&G,n+1,u);
	}
	//them cung noi beta
	for(u=1;u<=n;u++){
		int deg_pos = 0;
		for(v=1;v<=n;v++)
			if(G.A[u][v]>0)
				deg_pos++;
		if(deg_pos ==0 )
			add_edge(&G,u,n+2);
	}

	topo_sort(&G,&L);
	int t[MAX_VERTICES],T[MAX_VERTICES];
	//tinh t[u]	
	t[n+1]=0;
	for(i=2;i<=L.size;i++){
		int u=element_at(&L,i);
		t[u]=-1;
		for (v = 1; v <= G.n; v++)
			if(G.A[v][u]!=0)
				t[u]=max(t[u],t[v]+d[v]);
	}
	// tinh T[u]
	T[n+2]=t[n+2];
	for(i=L.size-1;i>=1;i--){
		int u=element_at(&L,i);
		T[u]=INFINITY;
		for (v = 1; v <= G.n; v++)
			if(G.A[u][v]!=0)
				T[u]=min(T[u],T[v]-d[u]);
	}
	for(i = 1; i <= G.n; i++)
	{
		if(t[i] == T[i]) printf("%d\n",i);
	}
	
	return 0;
}

