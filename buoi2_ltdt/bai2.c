#include "stdGraph.h"
#include "queue.h"

void duyetqueue(Graph g, int x){
	Queue q; int e, i;
	make_null_queue(&q);
	
	push(&q, x);
	
	while(!empty(&q)){
		e= top(&q); pop(&q);
		if(!mark[e]){
			mark[e]= 1;
			printf("%4d", e);
			
			List l; make_null(&l);
			l= neighbors(g, e);
			for(i= 1;i<=l.size;++i){
				push(&q, element_at(&l, i));
			}
		}
	}
}

int main(){
	Graph g= readFile((char*) "dothi.txt");
	printf ("\n Do thi da nhap: ");
	duyetqueue(g, 2);
	
	return 0;
}
