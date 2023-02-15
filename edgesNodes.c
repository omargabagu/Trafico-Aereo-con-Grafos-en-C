#include <stdlib.h>
#include <stdio.h>
//#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>

#define DBG_HELP 1

#if DBG_HELP > 1
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
	int code;
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
		vn->code=0;
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
//Eliminar y liberar un arco dada su llave y vertice de origen
void Vertex_DeleteEdge(Vertex* vertexOrigin, int edgeID){
	DBG_PRINT("6");
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

void Vertex_DeleteAllEdges(Vertex* v){
	DBG_PRINT("5");
	EdgeNode* ed = v->neighbors;
	if (ed){
		for (;ed->next;ed=ed->next){
			DBG_PRINT("d");
			Vertex_DeleteEdge(v,ed->edge.edgeID);
		}
		v->neighbors=NULL;
		v->lastNeighbor=NULL;
		v->neighbors=NULL;
		v->edgeListLen=0;
	}
	DBG_PRINT("All edges deleted\n");
	
	

	//Vertex_DeleteEdge(v,v->lastNeighbor->edge.edgeID);

	
}
void VertexNode_Delete(VertexNode* vn){
	DBG_PRINT("4");
	Vertex* v = &vn->vertex;
	Vertex_DeleteAllEdges(v);
	DBG_PRINT("8");
	//free(v);
	free(vn);
}
