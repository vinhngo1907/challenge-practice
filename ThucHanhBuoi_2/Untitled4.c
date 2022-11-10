#include <stdio.h>
#define white 0
#define black 1
#define gray 2
#define Max_Vertexs 100
#define MAX_ELEMENTS 100
typedef int ElementType;
typedef struct{
	ElementType data[MAX_ELEMENTS];
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

typedef struct{
	int data[100];
	int size;
}Stack;

void MakeNull_Stack(Stack *S)
{
	S->size = 0;
}
int Empty_Stack(Stack *S)
{
	return S->size == 0;
}
void Push_Stack(Stack *S, int x)
{
	S->data[S->size] = x;
	S->size++;
}

int Top_Stack(Stack *S)
{
	return S->data[S->size-1];	
}

void Pop_Stack(Stack *S)
{
	S->size--;
}
typedef struct{
	int n,m;
	int A[Max_Vertexs][Max_Vertexs];
}Graph;

void init_graph(Graph *G, int n)
{
	int i,j;
	G->n = n;
	for(i = 1; i <= n; i++)
	{
		for(j = 1; j <= n; j++)
		{
			G->A[i][j] = 0;
		}
	}
}

void add_edge(Graph *G, int x, int y)
{
	G->A[x][y] = 1;
	G->A[y][x] = 1;
}

int adjacent(Graph *G, int x, int y)
{
	return G->A[x][y] != 0;
} 
List neighbors(Graph *G, int x)
{
	List L; MakeNull_List(&L);
	int y;
	for(y = 1; y <= G->n; y++)
	{
		if(y != x && adjacent(G,x,y)) PushBack(&L,y);
	}
	return L;
}
int dfs(Graph *G, int x)
{
	int j, mark[100];
	Stack frontier; MakeNull_Stack(&frontier);
	for(j = 1; j <= G->n; j++)
	{
		mark[j] = 0;
	}
	Push_Stack(&frontier,x);
	while(!Empty_Stack(&frontier))
	{
		x = Top_Stack(&frontier); Pop_Stack(&frontier);
		if(mark[x] == 1) continue;
		printf("%d\n",x);
		mark[x] = 1;
		List list = neighbors(G,x);
		for(j = 1; j <= list.size; j++)
		{
			Push_Stack(&frontier,Element_at(&list,j));
		}
	}
}
int mark[100];
/*
void traversal(Graph *G, int x)
{
	if(mark[x] == 1) return ;
	int j;
	printf("%d\n",x); mark[x] = 1;
	List list; MakeNull_List(&list) ;
	list = neighbors(G,x);
	for(j= 1 ; j <= list.size; j++)
	{
		traversal(G,Element_at(&list,j));	
	}	
}
void duyetdequy_1(Graph *G)
{
	int j;
	for(j = 1; j <= G->n; j++)
	{
		mark[j] = 0;
	}
	traversal(G,1);
	for(j = 1; j <= G->n; j++)
	{
		if(mark[j] == 0) traversal(G,j);
	}
}*/
int duyetdequy_2(Graph *G, int x)
{
	if(mark[x] == 1) return 0;
	else
	{
		int n = 1,i;
//		printf(" %d ",x); 
		mark[x] = 1;
		List list; MakeNull_List(&list); list = neighbors(G,x);
		for(i = 1; i <= list.size; ++i)
		{
			n+=duyetdequy_2(G,Element_at(&list,i));
		}
		return n;
	}
}
void duyetdothi(Graph *G)
{
	int i;
	printf("\t\tDuyet do thi : ");
	for(i = 1 ; i <= G->n; ++i)
	{
		if(!mark[i]) duyetdequy_2(G,i);
		mark[i] = 0;
	}
	int lt = 0;
	for(i = 1; i <= G->n; ++i)
	{
		if(!mark[i])
		{
			printf("\n\tThanh phan lien thong thu %d: ",++lt);
			duyetdequy_2(G,i);
		}
		mark[i] = 0;
	}
	printf("\nDo thi co %d thanh phan lien thong => ",lt);
	if(lt > 1) printf("Do thi khong lien thong !");
	else printf("Do thi lien thong !");
}
int color[100];
int fail;
void colorize(Graph *G, int x, int c)
{
	if(color[x] == -1)
	{
		color[x] = c;
		List list = neighbors(G,x); int i;
		for(i = 1; i <= list.size;i++)
		{
			int y = Element_at(&list,i);
			colorize(G,y,!c);
		}	
	}	
	else
	{
		if(color[x] != c)
			fail = 1;	
	}		
}
int is_bigraph(Graph *G)
{
	int i;
	for(i = 1;  i <= G->n; i++)
	{
		color[i] = -1;
	}
	fail = 0;
	colorize(G,1,0); /* to mau tu dinh 1 voi mau den */
	/* Neu khong that bai thi G is_bigraph */
	return !fail;
}
void list_doi_bong(Graph G, int* list, int type)
{
	int i;
	for(i = 1; i <= G.n; i++)
	{
		if(color[i] == type) printf(" %d ",i);
	}
}
int cycle;

void findcycle(Graph *G, int x, int parent)
{
	color[x] = gray;
	List list; MakeNull_List(&list);
	list = neighbors(G,x);
	int j,y;
	for(j = 1 ; j <= list.size; ++j)
	{
		y = Element_at(&list,j);
		if(parent == y) continue;
		if(color[y] == gray) 
		{
			cycle = 1; /*Ton tai chu trinh*/
			return;
		}	
		if(color[y] == white)	findcycle(G,y,x);
	}
	color[x] = black;
}
int contains_cycle(Graph *G)
{
	int j;
	for(j = 1; j <= G->n; j++)
	{
		color[j] = white;
	}
	cycle = 0;
	for(j = 1; j <= G->n; j++)
	{
		if(color[j] == white)
			findcycle(G,j,0);
	}
	return cycle;
}

int main(){
	freopen("dothi.txt", "rt", stdin);
	Graph G; int n,m,u,v,x,y,e,i,j;
	scanf("%d%d",&n,&m);
	init_graph(&G,n);
	for(e = 1; e <= m; e++)
	{
		scanf("%d%d",&u,&v);
		add_edge(&G,u,v);
	}
//	duyetdothi(&G);
/*
	if(is_bigraph(&G))
	{
		printf("Doi bong 1: "); list_doi_bong(G, color, 0); 
		printf("\nDoi bong 2: "); list_doi_bong(G, color, 1);
	}
	else
	{
		printf("IMPOSSIBLE !");
	}*/
	
//	printf("Do thi co chu trinh khong ? ");
	duyetdequy_2(&G,1);
	if(contains_cycle(&G))
	{
		printf("Yes !");
	}
	else printf("No !");
	return 0;
}
