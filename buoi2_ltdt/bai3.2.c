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
	Graph g= readFile("dothi2.txt");
	int i, n= g.n;
	
	for(i=1;i<=n;++i){
		if(!mark[i]) duyetqueue(g, i); // mark[i] == 0;
	}
	
	return 0;
}
