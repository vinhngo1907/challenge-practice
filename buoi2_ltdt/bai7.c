#include "stdGraph.h"

int duyetdequy2(Graph g, int x){
	if(mark[x]) return 0; //	if(mark[x] == 1 )
	else{
		int sl= 1;
		mark[x] = 1;
		
		printf ("%4d", x);
		List l; make_null(&l);
		l= neighbors(g, x);
		int i;
		for(i=1; i<=l.size;++i){
			sl += duyetdequy2(g, element_at(&l, i));
		}
		return sl;
	}
}

int main(){
	Graph g= readFile("dothi2.txt");
	int i, j= 1;
	/*
	printf("\t\tDuyet do thi: [");
	for(i = 1; i <= g.n; i++)
	{
		if(!mark[i]) duyetdequy2(g,i);
		mark[i] = 0;
	}printf(" ]\n"); 
	*/
	for(i=1; i<=g.n;++i){
		if(!mark[i]){
			printf ("\n Thanh phan lien thong thu %d: ", j++);
			printf ("\n\t (co %d dinh)", duyetdequy2(g, i));
		}
	}
	
	return 0;
}
