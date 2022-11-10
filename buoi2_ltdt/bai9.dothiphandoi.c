#include "stdGraph.h"

int* colortable, fail= 0;

void fillcolor(int x, int color){
	if(!colortable[x]) colortable[x] = color;
	else{
		if(color!=colortable[x]) fail= 1;
	}
}

void phandoi(Graph g, int x, int color){
	if(!mark[x]){
		int uncolor = (color==1)?2:1, i;
		mark[x] = 1;
		printf ("%4d", x);
		fillcolor(x, color);	//	to mau dinh dau vao cua ham goi chinh, khi de quy thi nhung dinh nay da to mau
		List l; make_null(&l);
		l= neighbors(g, x);
		for(i=1;i<=l.size;++i){
			fillcolor(element_at(&l, i), uncolor);		//	to mau dinh ke cua no
			phandoi(g, element_at(&l, i), uncolor);		//	nhay toi dinh ke do de xet tiep
		}
	}
}

int main(){
	Graph g= readFile("dothi3.txt");	
	
	colortable= (int*) malloc(g.n*sizeof(int));
	init_mark(colortable, g.n);
	
	phandoi(g, 1, 1);
	
	if(!fail){
		printf("\n YES");
	}else{
		printf("\n NO");
	}
	
	int i;
	for(i=1;i<=g.n;++i){
		printf ("\n color: %d", colortable[i]);
	}
	
	return 0;
}
