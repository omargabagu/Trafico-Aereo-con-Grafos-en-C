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
					printf("	%i. %i",j,e->edgeID);
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
	Graph* myGraph = Graph_New();
	VertexNode_Insert(myGraph,20);
	VertexNode_Insert(myGraph,10);
	PrintGraph(myGraph);
	return 0;
}







