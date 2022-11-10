#include "stdGraph.h"
#include "stack.h"

void duyetstack(Graph g, int x){
	Stack s; int e, i;
	make_null_stack(&s);
	
	push(&s, x);
	
	while(!empty(&s)){
		e= top(&s); pop(&s);
		if(1!=mark[e]){
			mark[e]= 1;
			printf("%4d", e);
			
			List l; make_null(&l);
			l= neighbors(g, e);
			for(i= 1;i<=l.size;++i){
				push(&s, element_at(&l, i));
			}
		}
	}
}

int main(){
	Graph g= readFile("dothi.txt");
	
	printf ("\n Do thi da nhap: ");
	duyetstack(g, 2);
	
	return 0;
}
