//Poryecto areopuerto 

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdint.h>



// Arco para un vertice
typedef struct{
	int edgeID;
	int vertexDestiny;			///< Destino del arco
	double weight;	///< Peso del arco
}Edge;
// Nodo para una Lista arcos
typedef struct EdgeNode EdgeNode;
struct EdgeNode{
	EdgeNode* back;	//< Arco anterior en la lista si back=NULL este nodo es el primero 
	Edge edge;
	EdgeNode* next;	//< Arco siguiente en la lista si next=NULL este nodo es el ultimo
};
typedef struct EdgeNode EdgeNode;

// Vertice para un grafo
typedef struct{    
	int vertexID;    		///< Llave unica del vertice 
	EdgeNode* neighbors;	///< Apunta al primer nodo de una lista de arcos (vecinos)
	EdgeNode* lastNeighbor;	///< Apunta al ultimo nodo de las misma lista de arcos
	char name[10];			///< Nombre del vertice
	size_t edgeListLen;		///<
}Vertex;


// Nodo para una Lista de vertices
typedef struct VertexNode VertexNode;
struct VertexNode{
	VertexNode* back;	//< Vertice anterior en la lista si back=NULL este nodo es el primero
	Vertex vertex;
	VertexNode* next;	//< Vertice siguiente en la lista si next=NULL este nodo es el ultimo
};
typedef struct VertexNode VertexNode;
//typedef struct Vertex Vertex;


// Crear un nodo de una lista de arcos
EdgeNode* EdgeNode_New(int edgeID, int vertexDestiny, double weight){
	printf("Creando nodo de arco...	");
	EdgeNode* en = (EdgeNode*) malloc( sizeof( EdgeNode ) );
	if( en ){
		//información del nodo de arco
		en-> back = NULL;
		en-> next = NULL;
		//Informacion del arco
		en-> edge.edgeID = edgeID;
		en-> edge.vertexDestiny = vertexDestiny;
		en-> edge.weight = weight;
		printf("Nodo de arco creado!\n");
		return en; 
	}
	printf("Eorror\n");
	// Error de memoria
	free( en );
	en = NULL;
	return NULL; 
}
//Insertar un nodo en una lista de arcos
EdgeNode* EdgeNode_Insert(Vertex* originVertex, int edgeID, int vertexDestiny, double weight){
	printf("Insertando nodo a la lista de arcos...	\n");
	//Se crea el nuevo nodo a insertar
	EdgeNode* en = EdgeNode_New(edgeID, vertexDestiny, weight);
	//Se le asigna el nuevo vertice --REDUNDANTE--
	en->edge.edgeID = edgeID;
	en->edge.vertexDestiny= vertexDestiny;
	en->edge.weight = weight;
	//Si no es el primer nodo de arcos del vertice
	if (originVertex->lastNeighbor){
		//El siguiente nodo del (ex)ultimo nodo apunta a al nuevo nodo 
		originVertex->lastNeighbor->next=en;	
	}else{//Si es el primer nodo de arcos del vertice
		//Se establece como el primer nodo de arcos al nodo insertado
		originVertex->neighbors=en;
	}
	//Se especifica la informacion del nuevo arco
	en->back=originVertex->lastNeighbor;
	//Se actualiza quien es es el ulrimo nodo de la lista
	originVertex->lastNeighbor=en;
	
	
	//Se suma 1 la longitud de la lista
	originVertex->edgeListLen++;
	printf("Nodo insertado!\n");
}
// Crear un vertice para un grafo.
Vertex* Vertex_New(int ID){
	printf("	Creando vertice...	");
	Vertex* v = (Vertex*) malloc( sizeof( Vertex ) );
	if( v ){
		v->vertexID=ID;
		v->edgeListLen=0;
		v->neighbors = NULL;
		v->lastNeighbor = NULL;
		printf("	Vertice de ID: %i creado!\n",ID);
		return v;
	}
	printf("Error\n");
	// Error de memoria
	free( v );
	v = NULL;
	return NULL; 
}
// Crear el primer nodo de un  lista de vertices
VertexNode* VertexNode_New(int vertexID){
	printf("Creando nodo de vertice...	\n");
	VertexNode* vn = (VertexNode*) malloc( sizeof( VertexNode ) );
	if( vn ){
		vn-> back = NULL;
		vn-> vertex = *Vertex_New(vertexID);
		vn-> next = NULL;
		printf("Nodo de vertice creado!\n");
		return vn;
	}printf("Error\n");
	// Error de memoria
	free( vn );
	vn = NULL;
	return NULL; 
}

// Grafo
typedef struct{
	VertexNode *vertexes;		///< Apunta al primer nodo de una lista de vertices
	size_t vertexListLen;		///< Número de vértices actualmente en el grafo.
	VertexNode* lastVertexNode;	///< Apunta al ulrimo nodo de la lista
}Graph;

VertexNode* VertexNode_Insert(Graph* originGraph, int vertexID){
	printf("Insertando nodo a la lista de vertices...	\n");
	//Se crea el nuevo nodo a insertar
	VertexNode* vn = VertexNode_New(vertexID);
	//Se le asigna el nuevo vertice
	vn->vertex.vertexID= vertexID;
	vn->vertex.neighbors = NULL;
	vn->vertex.lastNeighbor= NULL;
	//Si no es el primer nodo de vertices del grafo
	if (originGraph->lastVertexNode){
		//El siguiente nodo del (ex)ultimo nodo apunta a al nuevo nodo 
		originGraph->lastVertexNode->next=vn;	
	}else{//Si es el primer nodo de vertices del grafo
		//Se establece como el primer nodo de vertices al nodo insertado
		originGraph->vertexes=vn;
	}
	//Se especifica la informacion del nuevo arco
	vn->back=originGraph->lastVertexNode;
	//Se actualiza quien es es el ultimo nodo de la lista
	originGraph->lastVertexNode=vn;
	
	
	//Se suma 1 la longitud de la lista
	originGraph->vertexListLen++;
	printf("Nodo insertado!\n");
	return vn;
}


Vertex* Vertex_Get(Graph* graph,int vertexID){
	printf("Buscando vertice  con ID: %i\n",vertexID);	
	if (graph->vertexes){
		printf("	Si hay vertices\n");
		VertexNode* vn=graph->vertexes;
		for(int i=0;i<graph->vertexListLen;i++){
			Vertex  *sv = &vn->vertex;
			if (sv->vertexID==vertexID){
				printf("Vector encontrado\n");
				return sv;
			}
			vn=vn->next;
		} 
		printf("Vertice no encontrado!\n");
		return NULL;
			
	}else{
		printf("No hay vertices!\n");
		return NULL;
	}
}
Edge* Edge_Get(Vertex* originVertex, int edgeID){
	printf("Buscando arco  con ID: %i\n",edgeID);	
	if (originVertex->neighbors){
		printf("	Si hay arcos\n");
		EdgeNode* en=originVertex->neighbors;
		for(int i=0;i<originVertex->edgeListLen;i++){
			Edge  *e = &en->edge;
			if (e->edgeID==edgeID){
				printf("Arco encontrado\n");
				return e;
			}
			en=en->next;
		} 
		printf("Arco NO encontrado!\n");
		return NULL;
			
	}else{
		printf("No hay arcos!\n");
		return NULL;
	}
}
bool Graph_NewEdge(Graph* graph,int originVertexID, int destinyVertexID,double weight,int edgeID){
	Vertex* originVertex = Vertex_Get(graph,originVertexID );
	if(originVertex&&Vertex_Get(graph,destinyVertexID )){
		if(!Edge_Get(originVertex,edgeID)){
			EdgeNode_Insert(originVertex,edgeID,destinyVertexID,weight);
			return true;
		}
		printf("Arco no creado,ya existe uno con ID: %i\n",edgeID);
		return false;
	}
	printf("Arco no creado, no existe alguno de los vertices.\n");
	return false;
}
bool Graph_NewVertex(Graph* graph, int vertexID){
	if (!Vertex_Get(graph,vertexID)){
		if(VertexNode_Insert(graph,vertexID))
			return true;
	}
	printf("Vertice con no creado, ID: %i ya existente.\n", vertexID);
	return false;	
}
// Crear un grafo
Graph* Graph_New(){
	Graph* g = (Graph*) malloc( sizeof( Graph ) );
	if( g ){
		g->vertexListLen=0;
		g->vertexes=NULL;
		g->lastVertexNode=NULL;
		return g;
	}
	// Error de memoria
	free( g );
	g = NULL;
	return NULL;
}

void PrintGraph(Graph* g ){ 
	if(g->vertexes){
		VertexNode* vn = g->vertexes;	
		for (int i=0;i<g->vertexListLen;i++){
			Vertex* v = &vn->vertex;
			printf("%i. %i\n",i,v->vertexID);
			
			if (v->neighbors){
				EdgeNode* en = v->neighbors;
				for (int j=0;j<v->edgeListLen;j++){
					Edge* e= &en->edge;
					printf("	%i. %i\n",j,e->edgeID);
					en=en->next;
				}	
			}
			vn=vn->next;
		}			
	}
} 
void PrintGraphInfo(Graph* g){
	printf("Cantidad de vertices: %i\n",g->vertexListLen);
}
int main(){
	//Creando un grafo
	Graph* myGraph = Graph_New();
	// Creando un vertice
	Graph_NewVertex(myGraph,20);
	
	Graph_NewVertex(myGraph,10);
	//Creando un arco entre el vertice 20 y 10, con un peso de 608.50 y con ID de 1
	Graph_NewEdge(myGraph,20,10,608.50,1);
	
	Graph_NewEdge(myGraph,10,20,608.50,2);
	
	Graph_NewEdge(myGraph,20,10,608.50,3);
	
	Graph_NewVertex(myGraph,15);
	
	Graph_NewEdge(myGraph,15,10,608.50,3);
	//Imprimendo grafo
	PrintGraph(myGraph);
	
	return 0;
}







