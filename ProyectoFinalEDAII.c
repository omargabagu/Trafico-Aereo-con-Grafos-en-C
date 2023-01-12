//Poryecto areopuerto 

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>

#define DBG_HELP 0

#if DBG_HELP > 0
#define DBG_PRINT( ... ) do{ fprintf( stderr, "DBG:" __VA_ARGS__ ); } while( 0 )
#else
#define DBG_PRINT( ... ) ;
#endif 

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
	DBG_PRINT("Creando nodo de arco...	");
	EdgeNode* en = (EdgeNode*) malloc( sizeof( EdgeNode ) );
	if( en ){
		//información del nodo de arco
		en-> back = NULL;
		en-> next = NULL;
		//Informacion del arco
		en-> edge.edgeID = edgeID;
		en-> edge.vertexDestiny = vertexDestiny;
		en-> edge.weight = weight;
		DBG_PRINT("Nodo de arco creado!\n");
		return en; 
	}
	DBG_PRINT("Eorror\n");
	// Error de memoria
	free( en );
	en = NULL;
	return NULL; 
}
//Insertar un nodo en una lista de arcos
EdgeNode* EdgeNode_Insert(Vertex* originVertex, int edgeID, int vertexDestiny, double weight){
	DBG_PRINT("Insertando nodo a la lista de arcos...	\n");
	//Se crea el nuevo nodo a insertar
	EdgeNode* en = EdgeNode_New(edgeID, vertexDestiny, weight);
	//Se le asigna el nuevo arco --REDUNDANTE--
	en->edge.edgeID = edgeID;
	en->edge.vertexDestiny= vertexDestiny;
	en->edge.weight = weight;
	//Se le asigna información de nodo
	//Si no es el primer nodo de arcos del vertice
	if (originVertex->edgeListLen>0){
		//El siguiente nodo del (ex)ultimo nodo apunta a al nuevo nodo 
		originVertex->lastNeighbor->next=en;
		//Se especifica la informacion del nuevo arco
		en->back=originVertex->lastNeighbor;	
	}else{//Si es el primer nodo de arcos del vertice
		//Se establece como el primer nodo de arcos al nodo insertado
		originVertex->neighbors=en;
		//Se especifica la informacion del nuevo arco
		en->back=NULL;
	}

	//Se actualiza quien es es el ulrimo nodo de la lista
	originVertex->lastNeighbor=en;
	en->next=NULL;
	
	//Se suma 1 la longitud de la lista
	originVertex->edgeListLen++;
	DBG_PRINT("Nodo insertado!\n");
}
// Crear un vertice para un grafo.
Vertex* Vertex_New(int ID,char* vertexName){
	DBG_PRINT("	Creando vertice...	");
	Vertex* v = (Vertex*) malloc( sizeof( Vertex ) );
	if( v ){
		v->vertexID=ID;
		v->edgeListLen=0;
		strcpy(v->name,vertexName);
		v->neighbors = NULL;
		v->lastNeighbor = NULL;
		DBG_PRINT("	Vertice de ID: %i creado!\n",ID);
		return v;
	}
	DBG_PRINT("Error\n");
	// Error de memoria
	free( v );
	v = NULL;
	return NULL; 
}
// Crear el primer nodo de un  lista de vertices
VertexNode* VertexNode_New(int vertexID, char* vertexName){
	DBG_PRINT("Creando nodo de vertice...	\n");
	VertexNode* vn = (VertexNode*) malloc( sizeof( VertexNode ) );
	if( vn ){
		vn-> back = NULL;
		vn-> vertex = *Vertex_New(vertexID,vertexName);
		vn-> next = NULL;
		DBG_PRINT("Nodo de vertice creado!\n");
		return vn;
	}DBG_PRINT("Error\n");
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

VertexNode* VertexNode_Insert(Graph* originGraph, int vertexID,char vertexName[]){
	DBG_PRINT("Insertando nodo a la lista de vertices...	\n");
	//Se crea el nuevo nodo a insertar
	VertexNode* vn = VertexNode_New(vertexID,vertexName);
	//Se le asigna el nuevo vertice
	vn->vertex.vertexID = vertexID;
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
	DBG_PRINT("Nodo insertado!\n\n");
	return vn;
}


Vertex* Vertex_Get(Graph* graph,int vertexID){
	DBG_PRINT("Buscando vertice  con ID: %i\n",vertexID);	
	if (graph->vertexes){
		DBG_PRINT("	Si hay vertices\n");
		VertexNode* vn=graph->vertexes;
		for(int i=0;i<graph->vertexListLen;i++){
			Vertex  *sv = &vn->vertex;
			if (sv->vertexID==vertexID){
				DBG_PRINT("Vector encontrado\n");
				return sv;
			}
			vn=vn->next;
		} 
		DBG_PRINT("Vertice no encontrado!\n");
		return NULL;
			
	}else{
		DBG_PRINT("No hay vertices!\n");
		return NULL;
	}
}
VertexNode* VertexNode_Get(Graph* graph,int vertexID){
	DBG_PRINT("Buscando vertice  con ID: %i\n",vertexID);	
	if (graph->vertexes){
		DBG_PRINT("	Si hay vertices\n");
		VertexNode* vn=graph->vertexes;
		for(int i=0;i<graph->vertexListLen;i++){
			Vertex  *sv = &vn->vertex;
			if (sv->vertexID==vertexID){
				DBG_PRINT("Vector encontrado\n");
				return vn;
			}
			vn=vn->next;
		} 
		DBG_PRINT("Vertice no encontrado!\n");
		return NULL;
			
	}else{
		DBG_PRINT("No hay vertices!\n");
		return NULL;
	}
}
Edge* Edge_Get(Vertex* originVertex, int edgeID){
	DBG_PRINT("Buscando arco  con ID: %i\n",edgeID);	
	if (originVertex->neighbors){
		DBG_PRINT("	Si hay arcos\n");
		EdgeNode* en=originVertex->neighbors;
		for(int i=0;i<originVertex->edgeListLen;i++){
			Edge  *e = &en->edge;
			if (e->edgeID==edgeID){
				DBG_PRINT("Arco encontrado\n");
				return e;
			}
			en=en->next;
		} 
		DBG_PRINT("Arco NO encontrado!\n");
		return NULL;
			
	}else{
		DBG_PRINT("No hay arcos!\n");
		return NULL;
	}
}
EdgeNode* EdgeNode_Get(Vertex* originVertex, int edgeID){
	DBG_PRINT("Buscando nodo de arco  con ID: %i\n",edgeID);	
	if (originVertex->neighbors){
		DBG_PRINT("	Si hay nodos de arcos\n");
		EdgeNode* en=originVertex->neighbors;
		for(int i=0;i<originVertex->edgeListLen;i++){
			Edge  *e = &en->edge;
			if (e->edgeID==edgeID){
				DBG_PRINT("Arco encontrado\n");
				return en;
			}
			en=en->next;
		} 
		DBG_PRINT("Nodo de arco NO encontrado!\n");
		return NULL;
			
	}else{
		DBG_PRINT("No hay arcos!\n");
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
		DBG_PRINT("Arco no creado,ya existe uno con ID: %i\n",edgeID);
		return false;
	}
	DBG_PRINT("Arco no creado, no existe alguno de los vertices.\n");
	return false;
}
/**
 * @brief Crea un vertice a partir de los datos mandados
 *
 * @param graph        El grafo.
 * @param vertexID     El ID del vertice a crear
 * @param vertexName   El nombre del vertice a crear
 * @return             True si lo creamos correctamente, False en caso contrario
 */
bool Graph_NewVertex(Graph* graph, int vertexID, char vertexName[] ){
	if (!Vertex_Get(graph,vertexID)){
		if(VertexNode_Insert(graph,vertexID,vertexName))
			return true;
	}
	DBG_PRINT("Vertice con no creado, ID: %i ya existente.\n", vertexID);
	return false;	
}
//Eliminar y liberar un arco dada su llave y vertice de origen
void Vertex_DeleteEdge(Vertex* vertexOrigin, int edgeID){
	//Si el vertice padre de origen tiene vecinos
	if (vertexOrigin->neighbors&&vertexOrigin->edgeListLen>0){
		DBG_PRINT("El vertice origen del arco a elminar, si tiene arcos.\n");
		EdgeNode* en = EdgeNode_Get(vertexOrigin, edgeID);
		//Si el nodo con edgeID existe
		if (en){
			DBG_PRINT("Obteniendo información del nodo del arco...	");
			EdgeNode* enAux;
			//Si es el unico nodo
			if (vertexOrigin->edgeListLen==1){
				DBG_PRINT("Es el unico nodo\n");
				vertexOrigin->neighbors=NULL;
				vertexOrigin->lastNeighbor=NULL;
			}else if(en->back==NULL){
				DBG_PRINT("Es el primer nodo\n");
				enAux=en->next;
				enAux->back=NULL;
				vertexOrigin->neighbors=enAux;
			}else if (en->next==NULL){
				DBG_PRINT("Es el ultimo nodo\n");
				enAux=en->back;
				enAux->next=NULL;
				vertexOrigin->lastNeighbor=enAux;
			}else if(en->next&&en->back){
				DBG_PRINT("El nodo se encuentra en medio2\n");
				enAux=en->next;
				enAux->back=en->back;
				enAux=en->back;
				enAux->next=en->next;
			}else {
				return;
			}
			vertexOrigin->edgeListLen--;
			//Eliminar nodo 
			DBG_PRINT("Eliminando nodo...\n");
			free(en);
			DBG_PRINT("----NODO ELIMINADO----\n");
			
		}
	}
	
}
// Eliminar un arco de un vertice de un grafo
void Graph_DeleteEdge(Graph* g, int vertexID, int edgeID){
	Vertex* v=Vertex_Get(g,vertexID);
	if (v){
		Vertex_DeleteEdge(v,edgeID);
	}
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
//Retorna el ID del vertice vecino a un vertice, retorna -1 si el vertice no tien vecinos
int VertexID_LowestNeighbor(Vertex* vertex){
	EdgeNode* en = vertex->neighbors;
	if (en){
		int lowestWeightEdgeID=en->edge.vertexDestiny;
		//printf("Lowest = %i\n",lowestWeightEdgeID);
		double lowestWeight;
		for(int i=1;i<vertex->edgeListLen;i++){
			
			
			en=en->next;
			//printf("	%f > %f",lowestWeight,en->edge.weight);
			if (lowestWeight> en->edge.weight){
				lowestWeightEdgeID=en->edge.vertexDestiny;
			}
			else{
				//printf("  No\n");
			}
				
			//printf("Lowest = %i\n",lowestWeightEdgeID);
		}
		
		return lowestWeightEdgeID;
	}
	else{
		//No tiene vecinos 
		return -1; 
	}
}
//Estructura par busqueda
typedef struct{
	int vertexID;
	VertexNode* vectorNode;
	int status;
}DFSVector;
//retorna el indice del arreglo DFSVList[] donde se encuentra el elemento con vID
//Si no existe retorna -1
int DFSList_GetIndex (int size,DFSVector* DFSVList,int vID){
	for (int i=0;i<size;i++){;
		if (vID==(DFSVList+i)->vertexID){
			return i;
		}
	}
	return -1;
}
//Busqueda por profundidad por peso EN DESARROLLO (parcialmente funcionando).
void DFS_Weight(Graph* graph, VertexNode* vnStart, VertexNode* vnEnd){
	VertexNode* vn = graph->vertexes;
	int n=graph->vertexListLen;
	//pseudoTablaHash
	DFSVector DFSVList [n];
	//Llenando tabla con los vertices del grafo
	for (int i=0;i<n;i++){
		DFSVList [i].vectorNode=vn;
		DFSVList [i].vertexID=vn->vertex.vertexID;
		DFSVList [i].status=0;
		//printf("%i,%i",DFSVList [i].vertexID,DFSVList [i].status);
		vn=vn->next;
	}
	vn = vnStart;
	//condición de i temporal
	for(int i=0;vn!=vnEnd&&i<5;i++){
		//Verice abierto status=1
		DFSVList[DFSList_GetIndex(n,DFSVList,vn->vertex.vertexID)].status=1;
		printf("%2i ->",vn->vertex.vertexID);
		//El siguiente vertice es igual al vecino con menor peso
		int lowestwID = VertexID_LowestNeighbor(&vn->vertex);
		if (lowestwID!=-1){
			//Se obtiene el ID del vertice vecino con menor peso
			vn = VertexNode_Get(graph,lowestwID);
			printf("%2i\n",vn->vertex.vertexID);
		}else{
			printf(" NULL\n");
			break;
		}
	}
	printf("\nDONE\n");
	
	/*for(;vn!=vnEnd;){
		
		en = vnStart->vertex.neighbors;
	}*/
	
	
	/*for (;;){
		VertexNode* vnNext = VertexNode_Get(graph,VertexID_LowestNeighbor(&vnStart->vertex));
	}*/
	
	
	
	
	/*if (en){
		int 
		printf("Correcto.\n");
		//Obtener el vecino con menor peso. 
		VertexNode* vnNext = VertexNode_Get(graph,VertexID_LowestNeighbor(&vnStart->vertex));
		
	}
	else {
		printf("Error el vertice con ID: %i no tiene vecinos.\n",vnStart->vertex.vertexID );
		//Error el vertice no tiene vecinos. 
	}*/
}

void PrintGraph(Graph* g ){ 
	if(g->vertexes){
		VertexNode* vn = g->vertexes;
		for (int i=0;i<g->vertexListLen;i++){
			Vertex* v = &vn->vertex;
			printf("%i. ID:%i. %s\n",i+1,v->vertexID,v->name);
			
			if (v->neighbors){
				EdgeNode* en = v->neighbors;
				for (int j=0;j<v->edgeListLen;j++){
					Edge* e= &en->edge;
					printf("		Vuelo: %i-%i. %s - $%f",v->vertexID,e->edgeID,Vertex_Get(g,e->vertexDestiny)->name,e->weight);
					//if(en->back)printf("b");
					//if(en->next)printf("n");
					printf("\n");
					en=en->next;
				}	
			}
			vn=vn->next;
		}			
	}
} 
void PrintGraphInfo(Graph* g){
	printf("Cantidad de vertices: %il\n",g->vertexListLen);
}
int main(){
	//Creando un grafo
	Graph* myGraph = Graph_New();
	// Creando un vertice
	Graph_NewVertex(myGraph,5,"MEX");
	Graph_NewVertex(myGraph,20,"ACA");
	Graph_NewVertex(myGraph,10,"GDL");
	Graph_NewVertex(myGraph,11,"CZM");
	Graph_NewVertex(myGraph,12,"CAN");
	Graph_NewVertex(myGraph,13,"MTY");
	//Creando un arco entre el vertice 20 y 10, con un peso de 608.50 y con ID de 1
	Graph_NewEdge(myGraph,20,5,300,0);
	Graph_NewEdge(myGraph,20,11,1500,1);
	Graph_NewEdge(myGraph,20,12,608,2);
	Graph_NewEdge(myGraph,11,10,2340,3);
	Graph_NewEdge(myGraph,10,13,2100.50,1);
	Graph_NewEdge(myGraph,10,20,980,1);
	Graph_NewEdge(myGraph,12,13,740,2);
	PrintGraph(myGraph);
	//Graph_DeleteEdge(myGraph,20,1);
	//printf("ID del vertice con menor ID: %i",VertexID_LowestNeighbor(Vertex_Get(myGraph,20)));
	DFS_Weight(myGraph,VertexNode_Get(myGraph,20),VertexNode_Get(myGraph,13));
	//printf("%i\n",VertexID_LowestNeighbor(Vertex_Get(myGraph,13)));
	//Imprimendo grafo
	
	
	return 0;
}







