#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>
//#Include "edgesnodes.h"

#define DBG_HELP 0

#if DBG_HELP > 0
#define DBG_PRINT( ... ) do{ fDBG_PRINT( stderr, "DBG:" __VA_ARGS__ ); } while( 0 )
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

int visited (Graph* g,VertexNode* vn,int data){
	Vertex* v = &vn->vertex;
	EdgeNode* en = v->neighbors;
	
	int n = v->edgeListLen;
	int visited=0;
	for (int i=0;i<n;i++){
		if (VertexNode_Get(g,en->edge.vertexDestiny)->code==data){
			visited++;
		}
		en=en->next;
	}
	return visited;

}
//Los resultados se guardan en partes de enteros, son una lista de enteros que 
//representan los IDs de los aeropuertos. 
typedef struct{
	int arrayIDs[20];
	double cost;
	int resSize;
}Res;
Res* Res_New(int n, int IDs[], double weights[]){
	Res* res = calloc(1, sizeof(Res));
	if (res==NULL){
		free(res);
		return NULL;
	}
	res->cost=0;
	res->resSize=n;
	for (int i =0;i<n;i++){
		res->arrayIDs[i]=IDs[i];
		if(weights[i]){
			res->cost=res->cost+weights[i];
		}
		
	}
	return res;
}
typedef struct{
	Res* arrayRes[50];
	int listSize;
}ResList;

ResList* ResList_New(){
	ResList* rl = calloc(1, sizeof(ResList));
	if (rl==NULL){
		free(rl);
		return NULL;
	}
	rl->listSize=0;
}
void ResList_NewRes(ResList* rl,Res* r){
	rl->arrayRes[rl->listSize]=r;
	rl->listSize++;
}
void Res_Delete(Res* r){
	free(r);
}
void ResList_Delete(ResList* rl){
	for (int i=0;i<50;i++){
		Res_Delete(rl->arrayRes[i]);
	}
	free(rl);
}
void ResList_Print(ResList* resList){
	
	printf("\n\n	--------------POSIBLES RUTAS----------------\n");
	for (int i=0;i<resList->listSize;i++){
		for (int j=0;j<resList->arrayRes[i]->resSize;j++){
			printf("%i->",resList->arrayRes[i]->arrayIDs[j]);
		}
		DBG_PRINT("		Costo de los vuelos: %f",resList->arrayRes[i]->cost);
		printf("\n");
	}
	
}
//Busqueda por profundidad altamente modificada para registrar todas las rutas posibles .
void OmargabaguAlgorithm(Graph* g, VertexNode* vnStart,VertexNode* vnEnd,ResList* resList){
	int n=g->vertexListLen;
	int Stack[n+2]; int SP=0;
	double weight[n+2];
	VertexNode* vn = vnStart;
	bool stop=false;
	for (;stop==false;){
		
		Stack[SP]=vn->vertex.vertexID;
		EdgeNode* en = vn->vertex.neighbors;
		int nn = vn->vertex.edgeListLen;
		int n0 = visited(g,vn,0);
		int n1 = visited(g,vn,1);
		int n2 = visited(g,vn,2);
		int n3 = visited(g,vn,3);
		
		//printf("	n0=%i, n1=%i, n2=%i, n3=%i		Stack[SP=%i]=%i\n",n0,n1,n2,n3,SP,Stack[SP]);
		SP++;
		printf("%i -> ",vn->vertex.vertexID);
		vn->code=1;
		
		
		if (n3>0){
			//save stack
			Stack[SP]=vn->vertex.vertexID;
			printf("\n");
			int arrayIDs[SP+1];
			double arrayW[SP];
			arrayIDs[SP+1]=vnEnd->vertex.vertexID;
			for (int i=0;i<SP+1;i++){
				arrayW[i]=weight[i+1];
				arrayIDs[i]=Stack[i];
			}arrayIDs[SP]=vnEnd->vertex.vertexID;
			Res* r = Res_New(SP+1,arrayIDs,arrayW);
			ResList_NewRes(resList,r);
			for (int i=0;i<SP+1;i++){
				printf("-%i-",arrayIDs[i]);
			}arrayIDs[SP+1]=vnEnd->vertex.vertexID;
			printf("\n");
		}
		if (vn->vertex.vertexID==vnEnd->vertex.vertexID){
			vn->code=3;
			Stack[SP]=vn->vertex.vertexID;
			
			//vn=pop
			SP=SP-2;vn=VertexNode_Get(g,Stack[SP]);
			printf("%ib",vn->vertex.vertexID);
		}
		else if((n0)>0){
			//push
			while(VertexNode_Get(g,en->edge.vertexDestiny)->code!=0){
				if (en->next){
					en=en->next;
				}
			}
			weight[SP]=en->edge.weight;
			vn=VertexNode_Get(g,en->edge.vertexDestiny);
			printf("%ia",vn->vertex.vertexID);
		}
		else if (nn==0||n0==0){
			vn->code=2;
			
			//vn=pop
			SP=SP-2;vn=VertexNode_Get(g,Stack[SP]);
			printf("NULL");
		}
		else{
			printf("ERROR EN LA LOGICA");
			stop=true;
		}
		printf(" :D\n");
		if (SP<0){
			stop=true;
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
void Graph_DeleteVertex(Graph* graphOrigin, int vertexID){
	DBG_PRINT("6");
	//Si el vertice padre de origen tiene vecinos
	if (graphOrigin->vertexes&&graphOrigin->vertexListLen>0){
		DBG_PRINT("	El grafo origen del verice a elminar, si tiene vertices.\n");
		VertexNode* vn = VertexNode_Get(graphOrigin, vertexID);
		//Si el nodo con vertexID existe
		if (vn){
			DBG_PRINT("	Obteniendo información del nodo del vertice...	");
			VertexNode* vnAux;
			//Si es el unico nodo
			if (graphOrigin->vertexListLen==1){
				DBG_PRINT("	Es el unico nodo\n");
				graphOrigin->vertexes=NULL;
				graphOrigin->lastVertexNode=NULL;
			}else if(vn->back==NULL){
				DBG_PRINT("	Es el primer nodo\n");
				vnAux=vn->next;
				vnAux->back=NULL;
				graphOrigin->lastVertexNode=vnAux;
			}else if (vn->next==NULL){
				DBG_PRINT("Es el ultimo nodo\n");
				vnAux=vn->back;
				vnAux->next=NULL;
				graphOrigin->lastVertexNode=vnAux;
			}else if(vn->next&&vn->back){
				DBG_PRINT("El nodo se encuentra en medio2\n");
				vnAux=vn->next;
				vnAux->back=vn->back;
				vnAux=vn->back;
				vnAux->next=vn->next;
			}else {
				return;
			}
			graphOrigin->vertexListLen--;
			//Eliminar nodo 
			DBG_PRINT("Eliminando nodo...\n");
			VertexNode_Delete(vn);
			DBG_PRINT("----NODO ELIMINADO----\n");
			
		}
	}
	
}

void Graph_DeleteAllVertexes(Graph* g){
	VertexNode* vn = g->vertexes;
	if (vn){
		for (int i=0;vn->next!=NULL;vn=vn->next,i++){
			DBG_PRINT("Eliminando vertice no.%i\n",i);
			Graph_DeleteVertex(g,vn->vertex.vertexID);
		}//Graph_DeleteVertex(g,vn->vertex.vertexID);
		g->lastVertexNode=NULL;
		g->vertexes=NULL;
		g->vertexListLen=0;
	}
	
}
void Graph_Delete(Graph* g){
	if (g){
		DBG_PRINT("1");
		Graph_DeleteAllVertexes(g);
		free(g);
	}
}
void Graph_Sort(Graph* g,int vertexIDA,int vertexIDB,ResList* resList){
	
	OmargabaguAlgorithm(g,VertexNode_Get(g,vertexIDA),VertexNode_Get(g,vertexIDB),resList);
}
void createRegistry(FILE** json_output, int vertexID, char vertexName[]){
    fprintf( *json_output, "{ " );
    fprintf( *json_output, "\"Airport\": \"%s\", \"AirPortID\": %d,", vertexName, vertexID );
    fprintf( *json_output, " }" );
}

void createJSON(int vertexID, char vertexName[]){
    FILE* json_output = fopen("registro.json", "a");
    if(!json_output){
		printf("Error abriendo el archivo JSON\n");
		exit(1);
	}
	fprintf(json_output, "{\n");
	fprintf( json_output, "\"historial\": [\n" );
	createRegistry(&json_output, vertexID, vertexName);
	fprintf( json_output, "\n]" );
	fprintf( json_output, "\n}" );
	fclose( json_output );
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
