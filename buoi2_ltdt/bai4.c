#include "stdGraph.h"

int main(){
	Graph g= readFile("dothi.txt");
	int i;
	
	printf ("\n Do thi da nhap: ");
	duyetdequy(g, 1);
	
	g= readFile("dothi2.txt");
	
	printf ("\n Do thi da nhap: ");
	for(i=1;i<=g.n;++i){
		if(!mark[i])duyetdequy(g, i);
	}
	
	return 0;
}
