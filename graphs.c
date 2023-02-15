#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>



#include "edgesNodes.c"

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
			//Eliminando ARCOS con destino al Vertice a eliminar
			
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
					if (Vertex_Get(g,e->vertexDestiny)){
						printf("		Arco: %i-%i. %s - $%f",v->vertexID,e->edgeID,Vertex_Get(g,e->vertexDestiny)->name,e->weight);
					}else{
						printf("		Arco: %i-%i. %s - $%f",v->vertexID,"--DELETED--",e->weight);
					}
					
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
