#include <stdio.h>

#define Max 100

typedef struct{
	int n;
	int A[Max][Max];
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
		if (adjacent(G,i,y)) count++;
	return count;
}

// List

typedef struct{
	int size;
	int Data[Max];
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

void copy(List *L1, List *L2){
	int i;
	makenull_list(L1);
	L1->size=L2->size;
	for (i=1;i<=L2->size;i++)
		L1->Data[i]=L2->Data[i];
}

int rank[Max];

void ranking(Graph *G){
	int i, j, k, y;
	int d[Max];
	List L1, L2;
	makenull_list(&L1);
	for (i=1;i<=G->n;i++){
		d[i]=degree(G,i);
		if (d[i]==0) push_back(&L1,i);
	}
	k=0;
	while(L1.size!=0){
		makenull_list(&L2);
		for (i=1;i<=L1.size;i++){
			y = element_at(&L1,i);
			rank[y] = k;
			for (j = 1; j <= G->n; j++)
				if (adjacent(G,y,j))
				{
					d[j]--;
					if (d[j]==0) push_back(&L2,j);
				}
		}
		k++;
		copy(&L1,&L2);
	}
}

int main(){
	freopen("canda.txt","rt",stdin);
	Graph G;
	int i, j, n, m, x, y;
	int temp=0, count=1;
	int topo[Max];
	scanf("%d%d", &n, &m);
	init_graph(&G,n);
	for (i=1;i<=m;i++){
		scanf("%d%d",&x, &y);
		add_edge(&G,x,y);
	}
	for(j=1;j<=G.n;j++) rank[j]=-1;
	ranking(&G);
	while(temp<=G.n){
		for (i=1;i<=G.n;i++) 
		{
			if (rank[i]==temp)
			{
				topo[count]=i;
				count++;
			}
		}
		temp++;
	}
	for (j=1;j<=G.n;j++) printf("%d ",topo[j]);
	return 0;
}
