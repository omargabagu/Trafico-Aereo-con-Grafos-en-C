#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define LINUXX 0
#ifdef	_linux_
#define LINUXX 1
#define LIMPIAR "clear"
#elif	_WIN32 || _WIN64
#define	LIMPIAR "cls"
#endif
#include "gsearch.c"

void PrintTitle(){
	printf("|\\   ____\\|\\   __  \\|\\   __  \\|\\  _____\\\\   __  \\|\\   ____\\     \n");
	printf("\\ \\  \\___|\\ \\  \\|\\  \\ \\  \\|\\  \\ \\  \\__/\\ \\  \\|\\  \\ \\  \\___|_  \n");
	printf(" \\ \\  \\  __\\ \\   _  _\\ \\   __  \\ \\   __\\\\ \\  \\\\\\  \\ \\_____  \\  \n");
	printf("  \\ \\  \\|\\  \\ \\  \\\\  \\\\ \\  \\ \\  \\ \\  \\_| \\ \\  \\\\\\  \\|____|\\  \\ \n");
	printf("   \\ \\_______\\ \\__\\\\ _\\\\ \\__\\ \\__\\ \\__\\   \\ \\_______\\____\\_\\  \\ \n");
	printf("    \\|_______|\\|__|\\|__|\\|__|\\|__|\\|__|    \\|_______|\\_________\\\n");
	printf("Ruta más rapida por omargabagu                      \\|_________|\n\n");
	
}

void main() {
	int opc=0;
	Graph* miGrafo = Graph_New();
	do {
		PrintTitle();
		printf("Menú:\nIngresar el caracter para acceder a la opción.\n");
		printf("0) Obtener Rutas  \n1) Ver Grafo \n2) Crear Verice\n3) Crear Arco\n4) Eliminar Vertice\n5) Eliminar Arco\n6) Salir\n");
		printf("\n> ");
		scanf("%i",&opc);
		switch (opc){
			case 0:
				system(LIMPIAR); 
				PrintTitle();
				printf("Buscar rutas\n");
				printf("	Ingresar ID del vertice de origen (int) ----> ");
				int ID7; scanf("%i",&ID7);
				printf("	Ingresar ID del vertice de destino (int) ---> ");
				int ID8; scanf("%i",&ID8);
				ResList* RList = ResList_New();
				Graph_Sort(miGrafo,ID7,ID8,RList);
				ResList_Print(RList);
				ResList_Delete(RList);
				printf("Enter para continuar...\n");
				fflush(stdin);
				getchar();
				break;
			case 1:
				system(LIMPIAR); 
				PrintTitle();
				printf("Ver Grafo\n");
				PrintGraph(miGrafo);
				printf("Enter para continuar...\n");
				fflush(stdin);
				getchar();
				break;
			case 2:
				system(LIMPIAR); 
				PrintTitle();
				printf("Crear Verice\n\n");
				printf("	Ingresar ID del nuevo vertice (int) ------------> ");
				int ID; scanf("%i",&ID);
				printf("	Ingresar nombre del nuevo vertice (string) -----> ");
				char name[10]; scanf("%s",&name);
				Graph_NewVertex(miGrafo, ID, name );
				printf("Enter para continuar...\n");
				fflush(stdin);
				getchar();
				break;
			case 3:
				system(LIMPIAR); 
				PrintTitle();
				printf("Crear Arco\n\n");
				printf("	Ingresar ID del vertice de origen (int) ----> ");
				int ID1; scanf("%i",&ID1);
				printf("	Ingresar ID del vertice de destino (int) ---> ");
				int ID2; scanf("%i",&ID2);
				printf("	Ingresar ID del nuevo arco (int) -----------> ");
				int ID3; scanf("%i",&ID3);
				printf("	Ingresar peso del nuevo arco (double) ------> ");
				int W; scanf("%i",&W);
				Graph_NewEdge(miGrafo,ID1, ID2,W,ID3); 
				printf("Enter para continuar...\n");
				fflush(stdin);
				getchar();
				break;
			case 4:
				system(LIMPIAR); 
				PrintTitle();
				printf("Eliminar Vertice\n\n");
				printf("	Ingresar ID del vertice a eliminar (int) ---> ");
				int ID4; scanf("%i",&ID4);
				Graph_DeleteVertex(miGrafo, ID4);
				break;
			case 5:
				system(LIMPIAR); 
				PrintTitle();
				printf("Eliminar Arco\n\n");
				printf("	Ingresar ID del vertice padre del arco (int) ---> ");
				int ID5; scanf("%i",&ID5);
				printf("	Ingresar ID del arco a eliminar (int) ----------> ");
				int ID6; scanf("%i",&ID6);
				Graph_DeleteEdge(miGrafo, ID5, ID6);
				break;
			case 6:
				Graph_Delete(miGrafo);
				break;
			default:
				break;
		}
		system(LIMPIAR);
	}while ((opc!=6));
	
}
