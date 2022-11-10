int adjacent(Graph *G, int x, int y){
	int e;
	for(e=1; e <= G->m; e++){
		if(G->A[x][e] == 1 && G->A[y][e] == 1) return 1;
	}
	return 0;
}
List neighbors(Graph* G, int x){
 	int y;
 	List L; 
 	make_null(&L);
	for(y = 1; y <= G->n; y++)
	{
		if(y!=x && adjacent(G,x,y)) push_back(&L,y); 
	}
	return L;
}
