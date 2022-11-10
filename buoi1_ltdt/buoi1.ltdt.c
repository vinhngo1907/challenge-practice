#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
	int dinh[MAX];
	struct{
		int x[MAX], y[MAX];
	} cung;
	
	int n, m;
}Graph;

Graph input();
void output(Graph);

int main(){
	Graph g= input();
	output(g);
	
	getch();
	return 0;
}

Graph input(){
	Graph g;
	int i;
	
	printf(" So dinh: "); scanf("%d", &g.n);
	printf ("\n Nhap dinh: ");
	for(i=0;i<g.n;++i){
		scanf("%d", &g.dinh[i]);
	}
	
	printf ("\n So cung: "); scanf("%d", &g.m);
	printf ("\n Nhap cung (x-y): ");
	for(i=0;i<g.m;++i){
		scanf("%d-%d", &g.cung.x[i], &g.cung.y[i]);
	}
	
	return g;
}

void output(Graph g){
	int i;
	printf ("\n Cac dinh: ");
	for(i=0;i<g.n;++i){
		printf("\t%d", g.dinh[i]);
	}
	
	printf ("\n Cac cung (x-y): ");
	for(i=0;i<g.n;++i){
		printf("\t%d-%d", g.cung.x[i], g.cung.y[i]);
	} 
}
