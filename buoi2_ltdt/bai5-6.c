#include "stdGraph.h"

int main(){
	Graph g= readFile("dothi.txt");
	int i, cnt= 0;
	
	duyetdequy(g, 1);
	for(i=1;i<=g.n;++i)
	{
		if(!mark[i])
		{
			cnt= 1;
			break;
		}
	}
	if(!cnt){
		printf("\n YES");
	}else{
		printf ("\n NO");
		cnt= 0;
	}
	
	g= readFile("dothi2.txt");
	
	for(i=1;i<=g.n;++i)
	{
		if(!mark[i]){
			duyetdequy(g, i);
			++cnt;
		}
	}
	
	if(1==cnt)
	{
		printf("\n YES");
	}else
	{
		printf("\n NO. Co %d thanh phan lien thong.", cnt);
	}
	
	return 0;
}
