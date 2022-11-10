#include "stdGraph-vector.h"
#include "stack.h"

int *num, *min_num, *on_stack, idx= -1, nth= 0;
Stack s;

int min(int x, int y){
	return (x<y)?x:y;
}

int strong_connect(Graph g, int x){
	num[x]= min_num[x]= idx++;
	push(&s, x);
	on_stack[x]= 1;
	
	List l; make_null(&l);
	l=neighbors(g, x);
	int i, y, nlt= 0;
	for(i=1;i<=l.size;++i){
		y= element_at(&l, i);
		if(!num[y]){
			nlt += strong_connect(g, y);
			min_num[x] = min(min_num[x], min_num[y]);
		}else if(on_stack[y]){
			min_num[x] = min(min_num[x], num[y]);
		}
	}
	
	if(num[x]==min_num[x]){
		int w;
		printf ("\n TP lien thong manh thu %d [", ++nth);
		do{
			w= top(&s); pop(&s);
			printf ("%4d ", w);
			on_stack[w]= 0;
		}while(w!=x);
		++nlt;
		printf ("]\n");
	}
	return nlt;
}

void listCycle(Graph g){
	int i, n= 0;
	idx= 1;
	make_null_stack(&s);

	num= (int*) malloc(g.n*sizeof(int));
	min_num= (int*) malloc(g.n*sizeof(int));
	on_stack= (int*) malloc(g.n*sizeof(int));
	init_mark(num, g.n);init_mark(min_num, g.n);init_mark(on_stack, g.n);
	
	for (i=1;i<=g.n;++i){
		if(!num[i]){
			n +=strong_connect(g, i);
		}
	}
	
	//printf ("\n => %d thanh phan lien thong manh.", n);
}

int main(){
	Graph g= readFile("dothi.lienthong.vector.txt");
	
	listCycle(g);
	
	return 0;
}
