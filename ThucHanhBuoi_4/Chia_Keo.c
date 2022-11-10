#include <stdio.h>

#define Max 100

// Dinh - Dinh

typedef struct{
	int A[Max][Max];
	int n;
}Graph;

void init_graph(Graph *G, int n){
	int i, j;
	G->n=n;
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++)
			G->A[i][j]=0;
}

void add_edge(Graph *G, int x, int y){
	G->A[x][y]=1;
}

int adjacent(Graph *G, int x, int y){
	return (G->A[x][y]!=0);
}

int degree(Graph *G, int y){
	int i, count=0;
	for (i=1;i<=G->n;i++)
		if (G->A[i][y]==1) count++;
	return count;
}

// Danh sach

typedef struct{
	int Data[Max];
	int size;
}List;

void makenull_list(List *L){
	L->size=0;
}

void push_back(List *L, int x){
	L->size++;
	L->Data[L->size]=x;
}

int element_at(List *L, int i){
	return L->Data[i];
}

void copy_list(List *S1, List *S2){
	int i;
	makenull_list(S1);
	S1->size=S2->size;
	for (i=1;i<=S2->size;i++)
		S1->Data[i]=S2->Data[i];
}

int rank[Max];

void ranking(Graph *G){
	int i, j, k, y;
	int d[G->n]; //bac vao cua cac dinh
	List S1, S2;
	makenull_list(&S1);
	for (i=1;i<=G->n;i++) {
		d[i]=degree(G,i);
		if (d[i]==0) push_back(&S1,i);
	}
	k=1;
	while(S1.size!=0){
		makenull_list(&S2);
		for (i=1;i<=S1.size;i++)
		{
			y=element_at(&S1,i);
			rank[y]=k;
			for (j=1;j<=G->n;j++)
			{
				if (adjacent(G,y,j))
				{
					d[j]--;
					if (d[j]==0) push_back(&S2,j);
				}
			}
		}
		k++;
		copy_list(&S1,&S2);
	}
}

int main(){
//	freopen("t.txt","r", stdin);
// 	freopen("chiakeo.txt","r", stdin);
	Graph G;
	int i, j, x, y, n, m, tong=0;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	for (i=1;i<=m;i++){
		scanf("%d%d",&x,&y);
		add_edge(&G,y,x); // chu y chi co bai chia keo
	}
	for (j=1;j<=n;j++) rank[j]=-1;
	ranking(&G);
	for (i=1;i<=n;i++) {
		printf("%d\n",rank[i]);
		tong=tong+rank[i];
	}
	printf("%d",tong);
	return 0;
}

