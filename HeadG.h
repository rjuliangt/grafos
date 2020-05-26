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
	unsigned node;                  // nodo
	int weight;                     // peso, longitud, etc...
	int residue;                    // capacidad residual del arco
    unsigned  inv;                  // nos idica la posicion del arco (j,i) en LS[j]
} ElementList;

// definicion del tipo de una lista de adyacencia de un nodo

typedef vector<ElementList> LA_node;

class GRAPH{
	unsigned managed;           //0 si el grafo es no dirigido y 1 si es dirigido
    unsigned nodes;              /* numero de NODOS */
	unsigned arcs;              /* numero de ARCOS */
    unsigned edges;             /* logitud aristas*/
	vector<LA_node> LS;         /* Lista de adyacencia de los sucesores    es una matriz donde cada fila posiblemente es de distinto tama�o*/
	vector<vector<int>> ady;    //matriz de adyacencia
	vector<int>lng;             //longitud de las aristas para kruskal
    public:
        GRAPH(char nameFile[]);  //constructor con nombre del fichero
        void viewGraph();
        void dfs(unsigned i, vector<bool> &visited);
        void kruskal();
        void amplitude(unsigned i,unsigned t, vector<unsigned> &pred, vector<unsigned> &posPred, vector<int> &bottleneck);
        void showWay (unsigned s, unsigned i, vector <unsigned> &pred);
        void showWay (unsigned s, int i, vector<unsigned> &pred, vector<int> &d);
        void Dijkstra();
        void edmodsKarp();
        ~GRAPH();
    };
#endif
