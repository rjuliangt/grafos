#include "HeadG.h"

GRAPH::GRAPH (char nameFile[]){
	unsigned i, j;
	int c;
	float x,y,z;
	x=y=z=0;
	arcs=0;
	ElementList dummy,dummy2;
	ifstream textFile;
	textFile.open (nameFile);
	
	if (textFile.is_open ()) {
		textFile >> (unsigned &) nodes;	// n = NODOS
		LS.resize (nodes);  // tamano de las filas
		 
		for(int ind=0;ind<nodes;ind++){
		    textFile >> (float &) x >> (float &) y;
		    z= sqrt((pow(x,2))-(pow(y,2)));
		    lng.push_back((int)z);
		};
		
		for (i = 0; i < nodes; i++ ) {
		    ady.push_back (vector<int>());
		    for (j = 0; j < nodes; j++ ){
                textFile >> (int &) edges;
                ady[i].push_back (edges);
            }
		}

		textFile.close ();

		for(i=0;i<nodes;i++)
		    for(j=0;j<nodes;j++){
                if(ady.at(i).at(j) == 1 && j>i){
                    cout << i << " " << j << "\n";
                    dummy.node = j;
                    dummy.weight = lng.at(i);
                    dummy.residue = lng.at(i);
                    dummy.inv = LS[j].size();
                    LS[i].push_back (dummy);
                    dummy2.node = i;
                    // Incializa los campos del arco virtual y capacidad residual a 0
                    dummy2.weight = 0;
                    dummy2.residue = 0;
                    dummy2.inv = LS[i].size() - 1;
                    LS[j].push_back(dummy2);
                    arcs++;
                }
            }
	} 
	else
	{  
	  cout << "\nNo se encuentra el fichero.\n";
	  exit(1);
	}	
};

void GRAPH::viewGraph(){
	cout << endl;
	cout << "*******************************************************************" << endl;
	cout << " - Numero de nodos: " << nodes << " - Numero de arcos: " << arcs << endl;
	cout << "*******************************************************************" << endl;
	cout << " - Lista de Adyacencia de los Sucesores: " << endl; 

	for (unsigned k = 0; k < nodes; k++){
	    cout << " * Sucesores del nodo " << k + 1 << " : ";
		    for (unsigned i = 0; i < LS[k].size(); i++){
		        cout << " " << (LS[k][i].node) + 1; //mostramos sumando uno, porque fue guardado restando uno
		    }
		cout  << endl;
	}
};

void GRAPH::dfs (unsigned i, vector<bool> &visited){
	visited[i] = true;
	cout << i + 1 << ",";
	for (unsigned k = 0; k < LS[i].size(); k++) {
		if (visited[LS[i][k].node] == false) dfs (LS[i][k].node, visited);  //todo nodo j en LS[i] no visitado
	}
};

GRAPH::~GRAPH () {}

void GRAPH :: kruskal(){
    vector<LA_node> adjacency= this->LS;
    vector< vector<int> > tree(nodes);
    vector<int> belongs(nodes); // indica a que arbol pertenece el nodo

    for(int i = 0; i < nodes; i++){
        tree[i] = vector<int> (nodes, lng[i]);
        belongs[i] = i;
    }
    int nodeA;
    int nodeB;
    int arcsX = 1;

    while(arcsX < nodes){
        // Encontrar  el arco minimo que no forma ciclo y guardar los nodos y la distancia.
        int min = lng[0];
        for(int i = 0; i < nodes; i++)
            for(int j = 0; j < nodes; j++)
                if(min > adjacency[i][j].weight && belongs[i] != belongs[j]){
                    min = adjacency[i][j].weight;
                    nodeA = i;
                    nodeB = j;
                }
                // Si los nodos no pertenecen al mismo arbol agrego el arco al arbol minimo.
                if(belongs[nodeA] != belongs[nodeB]){
                    tree[nodeA][nodeB] = min;
                    tree[nodeB][nodeA] = min;
                // Todos los nodos del arbol del nodoB ahora pertenecen al arbol del nodoA.
                    int temp = belongs[nodeB];
                    belongs[nodeB] = belongs[nodeA];
                    for(int k = 0; k < nodes; k++)
                        if(belongs[k] == temp) belongs[k] = belongs[nodeA];
            arcsX++;
        }
    }
  cout << "\n\nKRUSKAL: �rbol de expansi�n m�nimo del grafo.(longitudes)\n\n\n";
  for(int i = 0; i < 2; i++)
     for(int j = 0; j < 2; j++)
	    cout << tree[i][j] << "->";
	
}

void GRAPH::amplitude(unsigned i,unsigned t, vector<unsigned> &pred, vector<unsigned> &posPred, vector<int> &bottleneck){
    vector<unsigned> queue;
    queue.begin();
    int mini=0;
    queue.push_back(i);
    while (!queue.empty()) {
        int i=queue.front();
        queue.erase(queue.begin());  //borramos el primer elemento del vector
        for (int k=0; k<LS[i].size(); k++) {
            if (pred[LS[i][k].node]==UERROR && LS[i][k].residue>0) {
                pred[LS[i][k].node]=i;
                posPred[LS[i][k].node]=k;
                if (bottleneck[i]<LS[i][k].residue) {
                    mini=bottleneck[i];
                }
                else {
                    mini=LS[i][k].residue;
                }
                bottleneck[LS[i][k].node]=mini;
                queue.push_back(LS[i][k].node);
            }
        }
    }
}

void GRAPH::edmodsKarp(){
    int maxFlow = 0;                                                       //Suma de todos los cuellos de botella
    bool way = true;
    unsigned s, t, k;
    vector<int> bottleneck;
    vector<unsigned> pred, posPred;
    cout << "Introduzca el nodo fuente (1-" << nodes << "): ";
    cin >> s;
    s--;
    cout << "Introduzca el nodo sumidero (1-" << nodes << "): ";
    cin >> t;
    t--;
    cout << endl;
    while (way == true) {
        pred.resize(nodes,UERROR);
        posPred.resize(nodes);
        bottleneck.resize(nodes, maxint);
        for (unsigned k = 0; k < nodes; k++) {
            pred[k] = UERROR;
	        posPred[k] = 0;
	        bottleneck[k] = maxint;
        }
        pred[s] = s;
        amplitude(s, t, pred, posPred, bottleneck);
        if (pred[t] == UERROR){
            way = false;
	        cout <<"---------------------------------------------------------"<<endl;
	        cout << "    Patron de Flujo Maximo es " << maxFlow << endl;
        	cout << endl;
	        cout << "    El [S,T]-corte es: S= {";
	        for (unsigned k = 0; k < nodes; k++) {
	            if (pred[k] != UERROR) {
	                cout << " " << k+1 << ",";
	            }
            }                                                     //Todos los nodos k tales que pred[k] <> UERROR
            cout << " } y T = V-S"<<endl;
        }else{
            maxFlow += bottleneck[t];
	        unsigned k = t;
	        cout << "Camino Incremental: ";
	        // actualizaci�n de las capacidades residuales
	        showWay(s, t, pred);
	        cout << " Cuello de botella: " << bottleneck[t];
	        cout << endl;
	        while (k != s)  {
	            LS[pred[k]][posPred[k]].residue -= bottleneck[t];
	            LS[k][LS[pred[k]][posPred[k]].inv].residue += bottleneck[t];
	            k = pred[k];
            }
        }
   }
   cout << "    Patron de flujo maximo es:"<< endl;

    for (unsigned i = 0; i < nodes; i++) {
        for (unsigned k = 0; k < LS[i].size(); k++) {
            if (LS[i][k].weight > 0) {
           	    cout << "         X[" << i + 1 << ", " << LS[i][k].node + 1 << "] = " << LS[i][k].weight - LS[i][k].residue;
           	    cout << endl;
           	}
        }
    }
}

void GRAPH::Dijkstra(){
	vector<bool> minWay; 			                        // == Su camino minimo ya ha sido calculado
	vector<int> d;				                            // vector de coste
	vector<unsigned> pred;
	unsigned s, ca, mini = maxint, aux = 0;
	minWay.resize (nodes, false);		    // etiquetados a false
	d.resize (nodes, maxint);									// d es la etiqueta de distancia		(n) 		maxint = infinito
	pred.resize (nodes, UERROR);								// Los predecesores son unicos, por lo que puedo usar un array
	cout << endl;
	cout << " - Introduzca el nodo de partida [1-" << nodes << "]: ";
	cin >> s;
	cout << endl;
	s--;
	d[s]= 0;				// coste para llegar a el desde el = 0
	pred[s]= s;				//pred del nodo elegido (i) = i
	do{
		ca = UERROR;
		while ((ca == UERROR) && (aux < nodes)) {
				if (minWay[aux] == false)
					ca = aux;
				else
					aux++;
		}		//Sea candidato el nodo no etiquetado permanentemente con menor etiqueta distancia;
		if (ca != UERROR) {					// si me encuentro un nodo con una etiqueta no infinita
			mini = d[ca];
			for (unsigned j = 0; j < nodes; j++) {
				if (d[j] < mini) {
					if (minWay[j] == false) {
						mini = d[j];
						ca = j;
					}
				}
			}
			minWay[ca] = true;
			for (unsigned k = 0; k < LS[ca].size (); k++) {		// para todo nodo k en LS[candidato]
			    if (d[LS[ca][k].node] > d[ca] + LS[ca][k].weight) {		// d[LS[candidato][k].j]			LS[candidato][k].c
					d[LS[ca][k].node] = d[ca] + LS[ca][k].weight;
					pred[LS[ca][k].node] = ca;
				}
			}
		}
	} while (ca != UERROR);
	
	for (int i = 0; i < nodes; i++) {				// Para todo nodo i!= s

		if (i != s) {
		    if (pred[i] != UERROR)
			    showWay(s, i, pred, d);
			else
				cout << " * No hay Camino desde " << s + 1 << " al nodo " << i + 1 << endl;
		}
	}
}

void GRAPH::showWay (unsigned s, unsigned i, vector <unsigned> &pred){

    if (i != s) {
        showWay (s, pred[i], pred);
    }
    cout << i+1 << " -> ";
}

void GRAPH::showWay(unsigned s, int i, vector<unsigned> &pred, vector<int> &d){

	unsigned q = d[i];
	cout << " - El camino desde " << s + 1 << " al nodo " << i + 1 << " es: " << i + 1;
	
	do {
		cout << " -> " << pred[i] + 1;
		i = pred[i];
	} while (pred[i] != i);
	
	cout << " de longitud " << q << endl;
}
