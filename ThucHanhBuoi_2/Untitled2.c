#include <stdio.h>
#define Max_Vertexs 100
typedef int ElementType;
typedef struct{
	ElementType data[100];
	int size;
}List;

void MakeNull_List(List *L)
{
	L->size = 0;
}

void PushBack(List *L, int x)
{
	L->data[L->size] = x;
	L->size++;
}

ElementType Element_at(List *L, int i)
{
	return L->data[i-1]; 
}

/* Mot so bien ho tro */
int mark[100];
int color[100];
int fail;

typedef int ElementType;

typedef struct{
	int n;
	int A[Max_Vertexs][Max_Vertexs];
}Graph;

void init_graph(Graph *G, int n)
{
	G->n = n;
	int i,j;
	for(i = 1; i <= n; i++)
	{
		for(j = 1; j <= n; j++)
		{
			G->A[i][j] = 0;
		}
	}
}

void add_edge(Graph* G, int x, int y) {
	G->A[x][y] += 1; //y ke voi x
	G->A[y][x] += 1; //x ke voi y
}


int adjacent(Graph *G, int x, int y)
{
	return G->A[x][y] != 0;
}
List neighbors(Graph *G, int x)
{
	int y; List L; MakeNull_List(&L);
	for(y = 1; y <= G->n ; y++)
	{
		if(adjacent(G,x,y)) PushBack(&L,y);
	}
	return L;
}

void list_doi_bong(Graph G, int* list,int type){
	int i;
	for(i=1; i<=G.n;++i){
		if(color[i]==type) printf ("%d ", i);
	}
}

/* To mau bang phuong phap de quy */
void colorize(Graph* G, int x, int c) {
	/* Neu dinh a chua co mau thi to no */
	if (color[x] == -1) {
		color[x] = c;
		/* Lay cac dinh ke va to mau cho cac dinh ke bang mau nguoc lai voi c */
		List list = neighbors(G, x);
		int j;
		for (j = 1; j <= list.size; j++) 
		{
			int y = Element_at(&list, j);
			colorize(G, y, !c);
		}
	} 
	else /* x da có màu */
	{
		if (color[x] != c) /* 1 dinh bi to mau 2 lan khac chau */
			fail = 1; /* that bai */
	}	
}
//	kiem tra do thi co la do thi phan doi
int is_bigraph(Graph* G) {
	//	khoi tao color, chua dinh nao co mau
	int j;
	for (j = 1; j <= G->n; j++)
		color[j] = -1;
	
	fail = 0;
	colorize(G, 1, 0); /* To mau dinh bang 1 mau den */
	/* Neu khong that bai thi B la do thi phan doi */
	return !fail;
}
int main(){
	freopen("doibong.txt", "r", stdin);
	Graph G;
	int n, m, u, v, w, e;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	
	for (e = 1; e <= m; e++) {
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	if(is_bigraph(&G)){
		list_doi_bong(G, color, 0);
		printf("\n"); list_doi_bong(G, color, 1);
	}else{
		printf("IMPOSSIBLE");
	}
	return 0;
}

