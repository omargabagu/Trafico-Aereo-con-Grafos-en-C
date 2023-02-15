



#include "graphs.c"
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
void resetCodes(Graph* g){
	VertexNode* vn = g->vertexes;
	for(int i=0;i<g->vertexListLen;i++){
		vn->code=0;
		if (vn->next){
			vn=vn->next;
		}
	}
}
void OmargabaguAlgorithm(Graph* g, VertexNode* vnStart,VertexNode* vnEnd,ResList* resList){
	int n=g->vertexListLen;
	printf("Vertices: %i\n",n);
	if (n<2){
		return;
	}
	vnEnd->code=3;
	int Stack[n+2]; int SP=0;
	double weight[n+2];
	VertexNode* vn = vnStart;
	bool stop=false;
	for (;stop==false;){
		
		Stack[SP]=vn->vertex.vertexID;
		EdgeNode* en = vn->vertex.neighbors;
		int nn = vn->vertex.edgeListLen;
		int n0 = visited(g,vn,0); //CANTIDAD DE NODOS VECINOS NO VISITADOS
		int n1 = visited(g,vn,1); //CANTIDAD DE NODOS VECINOS VISITADOS
		int n2 = visited(g,vn,2); //CANTIDAD DE NODOS VECINOS COMPLETAMENTE EXPLORADOS
		int n3 = visited(g,vn,3); //CANTIDAD DE NODOS VECINOS DE DESTINO 
		
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
		/*if (vn->vertex.vertexID==vnEnd->vertex.vertexID){
			vn->code=3;
			Stack[SP]=vn->vertex.vertexID;
			
			//vn=pop
			SP=SP-2;vn=VertexNode_Get(g,Stack[SP]);
			printf("%ib",vn->vertex.vertexID);
		} else */
		if((n0)>0){
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

void Graph_Sort(Graph* g,int vertexIDA,int vertexIDB,ResList* resList){
	
	OmargabaguAlgorithm(g,VertexNode_Get(g,vertexIDA),VertexNode_Get(g,vertexIDB),resList);
	resetCodes(g);
}



