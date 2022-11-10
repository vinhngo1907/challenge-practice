#include "stdGraph-vector.h"

#define white 0
#define black 1
#define grey 2
#define MAX_V 101

int* color, cycle= 0;

void findCycle(Graph g, int x){
	color[x]= grey;
	List l; make_null(&l);
	l= neighbors(g, x);
	int i, y;
	for(i=1;i<=l.size;++i){
		y= element_at(&l, i);
		if(color[y]==grey){
			cycle= 1;
			return;
		}
		if(color[y]==white){
			findCycle(g, y);
		}
	}
	color[x]= black;
}

int contain_cycle(Graph g){
	int i;
	for(i=1;i<=g.n;++i){
		if(color[i]==white){
			findCycle(g, i);
		}
	}
	return cycle;
}

int main(){
	Graph g= readFile("dothi.chutrinh.txt");
	color= (int*) malloc(g.n*sizeof(int));
	init_mark(color, g.n);
	
	duyetdequy(g, 1);
	if(contain_cycle(g)){
		printf("\n YES");
	}else{
		printf("\n NO");
	}
	
	return 0;
}
