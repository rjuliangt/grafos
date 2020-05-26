
#ifndef _GRAPH_H
#define _GRAPH_H


#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

const unsigned UERROR = 65000;
const int maxint = 1000000;
const int INF = 1000000;

typedef struct{

	unsigned j; // nodo
	int      c; // peso, longitud, etc...
	int residuo;                    // capacidad residual del arco
        unsigned  inv;                  // nos idica la posicion del arco (j,i) en LS[j]
} ElementoLista;

// definicion del tipo de una lista de adyacencia de un nodo

typedef vector<ElementoLista> LA_nodo;

class GRAFO{
	unsigned dirigido;  //0 si el grafo es no dirigido y 1 si es dirigido
    unsigned n;         /* numero de NODOS */
	unsigned m;         /* numero de ARCOS */
    unsigned c;         /* logitud aristas*/
	vector<LA_nodo> LS;        /* Lista de adyacencia de los sucesores    es una matriz donde cada fila posiblemente es de distinto tama�o*/
	vector<vector<int>> ady; //matriz de adyacencia
	vector<int>longitud;   //longitud de las aristas para kruskal
    public:
        GRAFO(char nombrefichero[]);  //constructor con nombre del fichero
        void Mostrar_Grafo();
        void dfs(unsigned i, vector<bool> &visitado);
        void kruskal();
        void Amplitud(unsigned i,unsigned t, vector<unsigned> &pred, vector<unsigned> &pospred, vector<int> &CuelloBotella);
        void MostrarCamino (unsigned s, unsigned i, vector <unsigned> &pred);
        void MostrarCamino (unsigned s, int i, vector<unsigned> &pred, vector<int> &d);
        void Dijkstra();
        void edmods_karp();
        ~GRAFO();  //destructor
    };
#endif
