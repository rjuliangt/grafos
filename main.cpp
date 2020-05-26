#include "HeadG.h"
#include<iostream>

using namespace std;

int main (){
    char nombreFichero[30];
    int opc,i,j;
    int inicio=0,fin=0;

	cout << " RECORRIDO DE GRAFOS \n";
    cout << " Introduzca el nombre del fichero: ";
    cin >> nombreFichero;
    GRAPH Ografo (nombreFichero);
	Ografo.viewGraph();
        
	do{
	    cout << "\n\nMENU: \n";
	    cout << "\t1.Distancias y caminos m�nimos desde un v�rtice dado por el usuario aplicando el algoritmo de Dijkstra.\n";
	    cout << "\t2.Aplicar el algoritmo de Edmonds-karp.\n";
	    cout << "\t3.Aplicar el algoritmo de Kruskal.\n";
	    cout << "\t4.SALIR.\n\n";
	    cin >> opc;
	    switch(opc){
	        case(1):
        	    Ografo.Dijkstra();
        	    break;
            case(2):
        	    Ografo.edmodsKarp();
        	    break;
            case(3):
        	    Ografo.kruskal();
        	    break;
        	case(4):
        	    break;
	    };
	}while( opc != 4);
    return 0;
}

