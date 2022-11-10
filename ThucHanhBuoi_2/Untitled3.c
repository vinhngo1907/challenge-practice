#include <stdio.h>
#include <stdlib.h>
#define  Max_V 100
#define  Max_Elements 100
#define white 0
#define black 1
#define gray 2
typedef int ElementType;
typedef struct{
	ElementType data[Max_Elements];	
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
ElementType element_at(List *L, int i)
{
	return L->data[i-1];
}
typedef struct{
	int data[Max_Elements];
	int size;
}Stack;

void MakeNull_Stack(Stack *S)
{
	S->size = 0;
}
int empty_stack(Stack *S)
{
	return S->size == 0;
}
void push_stack(Stack *S, int x)
{
	S->data[S->size] = x;
	S->size++;
}
int top_stack(Stack *S)
{
	return S->data[S->size-1];
}
void pop_stack(Stack *S)
{
	S->size--;
}

typedef struct{
	int front, rear;
	int data[Max_Elements];
}Queue;

void makenull_queue(Queue *Q)
{
	Q->front = 0;
	Q->rear = -1;
}
int empty_queue(Queue *Q)
{
	return (Q->front > Q->rear);
}
void push_queue(Queue *Q, int x)
{
	Q->rear++;
	Q->data[Q->rear] = x;
}
int top_queue(Queue *Q)
{
	return Q->data[Q->front];
}
void pop_queue(Queue *Q)
{
	Q->front--;
}

typedef struct{
	int n;
	int A[Max_V][Max_V];
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
	G->A[x][y] += 1;
	G->A[y][x] += 1;
}

int adjacent(Graph *G, int x, int y)
{
	return G->A[x][y] != 0;
}

int degree(Graph *G, int x)
{
	int y, deg  =0;
	for(y = 1 ; y <= G->n; y++)
	{
		if(G->A[x][y] > 0 ) deg++;
	}
	return deg;
	/*for(y = 1 ; y <= G->n; y++)
	{
		deg+=G->A[x][y];
	}*/
}
List neighbors(Graph *G, int x)
{
	List list; MakeNull_List(&list);
	int y;
	for(y = 1; y <= G->n; y++)
	{
		if(y!= x && adjacent(G,x,y)) PushBack(&list,y);
	}
	return list;
}
int color[100], cycle, fail;
void colorize(Graph *G, int x, int c)
{
	if(color[x] == -1)
	{
		int j;
		color[x] = c;
		List list; MakeNull_List(&list);
		list = neighbors(G,x);
		for(j = 1; j <= list.size; j++)
		{
			int y = element_at(&list, j);
			colorize(G,y,!c);
		}
	}
	else
	{
		if(color[x] != c) fail = 1;
	}
}

int is_bigraph(Graph *G)
{
	int i;
	for(i = 1; i <= G->n; i++)
	{
		color[i] = -1;
	}
	fail = 0;
	colorize(G,1,0);
	return !fail;
}

void dfs(Graph *G, int x){
	int j, mark[Max_V];
	Stack frontier; MakeNull_Stack(&frontier);
	for(j = 1; j <= G->n; j++)
	{
		mark[j] = 0;
	}
	push_stack(&frontier,x);
	while(!empty_stack(&frontier))
	{
		x = top_stack(&frontier); pop_stack(&frontier);
		if(mark[x] == 1) continue;
		//printf("%d",x);
		mark[x] = 1;
		List list = neighbors(G,x);
		for(j = 1; j <= list.size; j++)
		{
			int y = element_at(&list,j);
			push_stack(&frontier,y);
		}
	}
}

void find_cycle(Graph *G, int x){
	int i; color[x] = gray;
	List list = neighbors(G,x);  MakeNull_List(&list);
	for(i= 1; i <= list.size; i++)
	{
		int y = element_at(&list, i);
		if(color[i] == gray)
		{
			cycle = 1;
			return ;
		}
		if(color[y] == white) find_cycle(G,y);
	}
	color[x] = black;
}

int contains(Graph *G)
{
	int i;
	for(i = 1; i <= G->n; i++)
	{
		color[i] = white;
	}
	cycle = 0;
	for(i = 1; i <= G->n; i++)
	{
		if(color[i] == white) find_cycle(G,i);
	}
	return cycle;
}
int mark[100];
int duyetdequye(Graph *G, int x)
{
	if(mark[x] == 1) return 0;
	else
	{
		int i,n = 1;
		mark[x] = 1;
		List list = neighbors(G,x);
		for(i =1 ; i <= list.size; i++)
		{
			n+=duyetdequye(G,element_at(&list,i));
		}
		return n;
	}
}

void duyet_dothi(Graph *G)
{
	int i;
	for(i = 1; i <= G->n; ++i)
	{
		if(!mark[i])
		{
			duyetdequye(G,i);
		}
		mark[i] = 0;
	}
	int nlt = 0;
	for(i = 1; i <= G->n; ++i)
	{
		if(!mark[i])
		{
			printf("\nThanh phan lien thong thu %d[",++nlt);
			duyetdequye(G,i); printf("]\n");
		}
		mark[i] = 0;
	}
	printf("Do thi co %d thanh phan lien thong !",nlt);
	if(nlt > 1) printf("Do thi khong lien thong !");
	else printf("Do thi lien thong !");
}
int main(){
	freopen("dothi.txt","rt",stdin);
	int i,j,x,y,m,n,u,v,e;
	Graph G;
	scanf("%d%d",&n,&m);
	init_graph(&G,n);
	for(e = 1 ; e <= m; e++)
	{
		scanf("%d%d",&u,&v);
		add_edge(&G, u,v);
	}
	duyet_dothi(&G);
	return 0;
}
