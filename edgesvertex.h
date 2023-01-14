#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
//EdgeVertexNames
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
	int code;
	VertexNode* next;	//< Vertice siguiente en la lista si next=NULL este nodo es el ultimo
};
typedef struct VertexNode VertexNode;
//typedef struct Vertex Vertex;




//Edge

typedef struct EdgeNode EdgeNode;

EdgeNode* EdgeNode_New(int edgeID, int vertexDestiny, double weight);
VertexNode* VertexNode_New(int vertexID, char* vertexName);


//Vertex

EdgeNode* EdgeNode_Insert(Vertex* originVertex, int edgeID, int vertexDestiny, double weight);
Vertex* Vertex_New(int ID,char* vertexName);
void VertexNode_Delete(VertexNode* vn);
void Vertex_DeleteAllEdges(Vertex* v);
void Vertex_DeleteEdge(Vertex* vertexOrigin, int edgeID);
EdgeNode* EdgeNode_Get(Vertex* originVertex, int edgeID);
Edge* Edge_Get(Vertex* originVertex, int edgeID);


//Lectura en JSON NO TERMINADO
void createJSON(int vertexID, char vertexName[]);
void createRegistry(FILE** json_output, int vertexID, char vertexName[]);

//Graph
typedef struct{
	VertexNode *vertexes;		///< Apunta al primer nodo de una lista de vertices
	size_t vertexListLen;		///< Número de vértices actualmente en el grafo.
	VertexNode* lastVertexNode;	///< Apunta al ulrimo nodo de la lista
}Graph;

Graph* Graph_New();
void Graph_DeleteEdge(Graph* g, int vertexID, int edgeID);
void Graph_Delete(Graph* g);
void Graph_DeleteAllVertexes(Graph* g);
void Graph_DeleteVertex(Graph* graphOrigin, int vertexID);
bool Graph_NewVertex(Graph* graph, int vertexID, char vertexName[] );
bool Graph_NewEdge(Graph* graph,int originVertexID, int destinyVertexID,double weight,int edgeID);
VertexNode* VertexNode_Get(Graph* graph,int vertexID);
Vertex* Vertex_Get(Graph* graph,int vertexID);
VertexNode* VertexNode_Insert(Graph* originGraph, int vertexID,char vertexName[]);
void PrintGraph(Graph* g );

//Res
typedef struct{
	int arrayIDs[20];
	double cost;
	int resSize;
}Res;
Res* Res_New(int n, int IDs[], double weights[]);
void Res_Delete(Res* r);

//ResList
typedef struct{
	Res* arrayRes[50];
	int listSize;
}ResList;
ResList* ResList_New();
void ResList_Print(ResList* resList);
void ResList_Delete(ResList* rl);
void ResList_NewRes(ResList* rl,Res* r);



//Graph sort
void OmargabaguAlgorithm(Graph* g, VertexNode* vnStart,VertexNode* vnEnd,ResList* resList);
int visited (Graph* g,VertexNode* vn,int data);



