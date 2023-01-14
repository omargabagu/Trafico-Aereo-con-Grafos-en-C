#include <stdio.h>
#include <stdlib.h>
#include "edgesvertex.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void PrintTitle(){
	printf("     ___        _______   .______          ______   .___________. __  .___  ___.  _______ \n");
	printf("    /   \%c      |   ____|  |   _  \%c        /  __  \%c  |           ||  | |   \%c/   | |   ____|\n",92,92,92,92);
	printf("   /  ^  \%c     |  |__     |  |_)  |      |  |  |  | `---|  |----`|  | |  \%c  /  | |  |__   \n",92,92);
	printf("  /  /_\%c  \%c    |   __|    |      /       |  |  |  |     |  |     |  | |  |\%c/|  | |   __|  \n",92,92,92);
	printf(" /  _____  \%c   |  |____   |  |\%c  \%c----.  |  `--'  |     |  |     |  | |  |  |  | |  |____ \n",92,92,92);
	printf("/__/     \%c__\%c  |_______|  | _| `._____|   \%c______/      |__|     |__| |__|  |__| |_______|\n",92,92,92);
}
int main(){
	PrintTitle();
	//Creando un grafo
	Graph* myGraph = Graph_New();
	// Creando un vertice
	Graph_NewVertex(myGraph,5,"MEX");
	Graph_NewVertex(myGraph,20,"ACA");
	Graph_NewVertex(myGraph,10,"GDL");
	Graph_NewVertex(myGraph,11,"CZM");
	Graph_NewVertex(myGraph,12,"CAN");
	Graph_NewVertex(myGraph,13,"MTY");
	Graph_NewVertex(myGraph,9,"LOL");
	//Creando un arco entre el vertice 20 y 10, con un peso de 608.50 y con ID de 1
	Graph_NewEdge(myGraph,20,5,300,0);
	Graph_NewEdge(myGraph,20,11,1500,1);
	Graph_NewEdge(myGraph,20,12,608,2);
	Graph_NewEdge(myGraph,11,10,2340,3);
	Graph_NewEdge(myGraph,10,13,2100.50,4);
	Graph_NewEdge(myGraph,10,20,980,5);
	Graph_NewEdge(myGraph,12,13,740,6);
	Graph_NewEdge(myGraph,10,9,1000,7);
	Graph_NewEdge(myGraph,9,13,790,8);
	PrintGraph(myGraph);
	//Graph_DeleteEdge(myGraph,20,1);
	ResList* MyList = ResList_New();
	Graph_Sort(myGraph,10,12,MyList);
	
	//printf("%i\n",VertexID_LowestNeighbor(Vertex_Get(myGraph,13)));
	//Imprimendo grafo
	ResList_Print(MyList);
	
	
	Graph_Delete(myGraph);
	
	ResList_Delete(MyList);
	
	return 0;
}

