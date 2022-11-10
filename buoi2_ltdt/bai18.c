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
		do{
			w= top(&s); pop(&s);
			on_stack[w]= 0;
		}while(w!=x);
		++nlt;
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
	
	if(n!=1){
		printf("\n NO");
	}else{
		printf ("\n YES");
	}
}

Graph readFile_2chieu(char* filename){
	Graph g;
	int n, m, i, x, y, p;
	FILE* f= fopen(filename, "r");
	
	fscanf(f, "%d%d", &n, &m);
	init_graph(&g, n);
	mark = (int*) malloc(n*sizeof(int));
	init_mark(mark, n);
	
	for(i=1;i<=m;++i){
		fscanf(f, "%d%d%d", &x, &y, &p);
		add_edge(&g, x, y);
		if(2==p){
			add_edge(&g, y, x);
		}
	}
	
	fclose(f);
	
	return g;
}

int main(){
	Graph g= readFile_2chieu("dothi.lienthong.ComeGo.txt");
	
	listCycle(g);
	
	return 0;
}
