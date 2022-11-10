#include "stdGraph-vector.h"
#include "stack.h"

int *num, *min_num, *on_stack, idx= -1;
Stack s;

int min(int x, int y){
	return (x<y)?x:y;
}

void strong_connect(Graph g, int x){
	num[x]= min_num[x]= idx++;
	push(&s, x);
	on_stack[x]= 1;
	
	List l; make_null(&l);
	l=neighbors(g, x);
	int i, y;
	for(i=1;i<=l.size;++i){
		y= element_at(&l, i);
		if(!num[y]){
			strong_connect(g, y);
			min_num[x] = min(min_num[x], min_num[y]);
		}else if(on_stack[y]){
			min_num[x] = min(min_num[x], num[y]);
		}
	}
	printf("\n num[%d]: %d - min_num[%d]: %d", x, num[x], x, min_num[x]);
	
	if(num[x]==min_num[x]){
		printf ("\n %d la khop [", x);
		int w;
		do{
			w= top(&s); pop(&s);
			printf ("%4d ", w);
			on_stack[w]= 0;
		}while(w!=x);
		printf ("]\n");
	}
}

void listCycle(Graph g){
	int i;
	idx= 1;
	make_null_stack(&s);
	
	num= (int*) malloc(g.n*sizeof(int));
	min_num= (int*) malloc(g.n*sizeof(int));
	on_stack= (int*) malloc(g.n*sizeof(int));
	init_mark(num, g.n);init_mark(min_num, g.n);init_mark(on_stack, g.n);
	
	for (i=1;i<=g.n;++i){
		if(!num[i]){
			strong_connect(g, i);
		}
	}
}

int main(){
	Graph g= readFile("dothi.lienthong.vector.txt");	
	duyetdequy(g, 1);
	
	listCycle(g);
	
	return 0;
}
