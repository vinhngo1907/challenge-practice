int deg(Graph *G, int x)
{
	int e;
	int deg = 0;
	for(e = 1; e <= G->n; e++)
	{
		if(G->A[x][e] > 0) 
		    deg++;
	}
	return deg;
}
