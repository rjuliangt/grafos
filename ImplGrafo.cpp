#include "HeadG.h"

GRAFO::GRAFO (char nombreFichero[]) {
	unsigned i, j;
	int c;
	float x,y,z;
	x=y=z=0;
	m=0;
	ElementoLista dummy,dummy2;
	ifstream textfile;
	
	textfile.open (nombreFichero);
	
	if (textfile.is_open ()) {
		
		textfile >> (unsigned &) n;	// n = NODOS
		LS.resize (n);  // tamano de las filas
		 
		for(int ind=0;ind<n;ind++)
		{  
		  textfile >> (float &) x >> (float &) y;
		  z= sqrt((pow(x,2))-(pow(y,2)));
		  longitud.push_back((int)z);	
		};
		
		for (i = 0; i < n; i++ ) {
		  ady.push_back ( vector<int>() );
		  for (j = 0; j < n; j++ )
		  {  
		    textfile >> (int &) c ; 
		    ady[i].push_back (c);
		  }  
		}

		textfile.close (); 

		for(i=0;i<n;i++)
		  for(j=0;j<n;j++)
		  {
		    if(ady.at(i).at(j) == 1 && j>i)
		    {
		        cout << i << " " << j << "\n";
		        dummy.j = j;
			dummy.c = longitud.at(i);
			dummy.residuo = longitud.at(i);
                       	dummy.inv = LS[j].size();
			LS[i].push_back (dummy);
			dummy2.j = i;  
			// Incializa los campos del arco virtual y capacidad residual a 0
                        dummy2.c = 0;                
                        dummy2.residuo = 0;
                        dummy2.inv = LS[i].size() - 1;
 	                LS[j].push_back(dummy2);   
			m++;
                    }
                    
                 }
	} 
	else
	{  
	  cout << "\nNo se encuentra el fichero.\n";
	  exit(1);
	}	
};


void GRAFO::Mostrar_Grafo () 
{
	
	cout << endl;
	   
	cout << "*******************************************************************" << endl;
	cout << " - Numero de nodos: " << n << " - Numero de arcos: " << m << endl;
	cout << "*******************************************************************" << endl;
	cout << " - Lista de Adyacencia de los Sucesores: " << endl; 
	
	for (unsigned k = 0; k < n; k++) 
        {
		
	  cout << " * Sucesores del nodo " << k + 1 << " : ";
		
		for (unsigned i = 0; i < LS[k].size(); i++)
		{
		  cout << " " << (LS[k][i].j) + 1; //mostramos sumando uno, porque fue guardado restando uno
		}
		cout  << endl;
	}
};

void GRAFO::dfs (unsigned i, vector<bool> &visitado){
	visitado[i] = true;
	cout << i + 1 << ",";

	for (unsigned k = 0; k < LS[i].size(); k++) {
		if (visitado[LS[i][k].j] == false)							//  para todo nodo j en LS[i] no visitado
			dfs (LS[i][k].j, visitado);
	}

};

GRAFO::~GRAFO () {}		// Destructor

// Devuelve la matriz de adyacencia del arbol minimo.
void GRAFO :: kruskal(){
    vector<LA_nodo> adyacencia = this->LS;
    
    vector< vector<int> > arbol(n);
    vector<int> pertenece(n); // indica a que arbol pertenece el nodo
 
    for(int i = 0; i < n; i++){
        arbol[i] = vector<int> (n, longitud[i]);
        pertenece[i] = i;
    }
 
    int nodoA;
    int nodoB;
    int arcos = 1;
    
    while(arcos < n)
    {
        // Encontrar  el arco minimo que no forma ciclo y guardar los nodos y la distancia.
        int min = longitud[0];
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                if(min > adyacencia[i][j].c && pertenece[i] != pertenece[j])
		{
                    min = adyacencia[i][j].c;
                    nodoA = i;
                    nodoB = j;	
		    
                }
 
        // Si los nodos no pertenecen al mismo arbol agrego el arco al arbol minimo.
        if(pertenece[nodoA] != pertenece[nodoB]){
            arbol[nodoA][nodoB] = min;
            arbol[nodoB][nodoA] = min;
 
            // Todos los nodos del arbol del nodoB ahora pertenecen al arbol del nodoA.
                int temp = pertenece[nodoB];
                pertenece[nodoB] = pertenece[nodoA];
                for(int k = 0; k < n; k++)
                        if(pertenece[k] == temp)
                                pertenece[k] = pertenece[nodoA];
 
            arcos++;
        }
    }
  
  cout << "\n\nKRUSKAL: �rbol de expansi�n m�nimo del grafo.(longitudes)\n\n\n";
  for(int i = 0; i < 2; i++)
            for(int j = 0; j < 2; j++) 
	      cout << arbol[i][j] << "->";
	
}

// Recorrido en AMPLITUD
void GRAFO::Amplitud(unsigned i,unsigned t, vector<unsigned> &pred, vector<unsigned> &pospred, vector<int> &CuelloBotella)
{
vector<unsigned> Cola;
    Cola.begin();
    int minimo=0;
    Cola.push_back(i);
    while (!Cola.empty()) {
        int i=Cola.front();
        Cola.erase(Cola.begin());  //borramos el primer elemento del vector
        for (int k=0; k<LS[i].size(); k++) {
            if (pred[LS[i][k].j]==UERROR && LS[i][k].residuo>0) {
                pred[LS[i][k].j]=i;
                pospred[LS[i][k].j]=k;
                if (CuelloBotella[i]<LS[i][k].residuo) {
                    minimo=CuelloBotella[i];
                }
                else {
                    minimo=LS[i][k].residuo;
                }
                CuelloBotella[LS[i][k].j]=minimo;
                Cola.push_back(LS[i][k].j);
            }
        }
    }
}


void GRAFO::edmods_karp(){

int maxflow = 0;                                                       //Suma de todos los cuellos de botella
bool camino = true;
unsigned s, t, k;
vector<int> CuelloBotella;
vector<unsigned> pred, pospred;

   cout << "Introduzca el nodo fuente (1-" << n << "): ";
   cin >> s;
   s--;
   cout << "Introduzca el nodo sumidero (1-" << n << "): ";
   cin >> t;
   t--;
   cout << endl;
   while (camino == true) {
      pred.resize(n,UERROR);
      pospred.resize(n);
      CuelloBotella.resize(n, maxint);
      for (unsigned k = 0; k < n; k++) {
         pred[k] = UERROR;
	 pospred[k] = 0;
	 CuelloBotella[k] = maxint;
      }
      pred[s] = s;
      Amplitud (s, t, pred, pospred, CuelloBotella);
      if (pred[t] == UERROR) {
         camino = false;
	 cout <<"---------------------------------------------------------"<<endl;
	 cout << "    Patron de Flujo Maximo es " << maxflow << endl;
	 cout << endl;
	 cout << "    El [S,T]-corte es: S= {";
	 for (unsigned k = 0; k < n; k++) {
	    if (pred[k] != UERROR) {
	       cout << " " << k+1 << ",";
	    }
         }                                                     //Todos los nodos k tales que pred[k] <> UERROR
         cout << " } y T = V-S"<<endl;
      }
      else {
         maxflow += CuelloBotella[t];
	 unsigned k = t;
	 cout << "Camino Incremental: ";
	 // actualizaci�n de las capacidades residuales
	 MostrarCamino (s, t, pred);
	 cout << " Cuello de botella: " << CuelloBotella[t];
	 cout << endl;
	 while (k != s)  {
	    LS[pred[k]][pospred[k]].residuo -= CuelloBotella[t];
	    LS[k][LS[pred[k]][pospred[k]].inv].residuo += CuelloBotella[t];
	    k = pred[k];
         }
      }
   }
   cout << "    Patron de flujo maximo es:"<< endl;
   for (unsigned i = 0; i < n; i++) {
      for (unsigned k = 0; k < LS[i].size(); k++) {
         if (LS[i][k].c > 0) {
	    cout << "         X[" << i + 1 << ", " << LS[i][k].j + 1 << "] = " << LS[i][k].c - LS[i][k].residuo;
	    cout << endl;
	 }
      }
   }
}


void GRAFO::Dijkstra() {
	vector<bool> PermanentementeEtiquetado; 			// == Su camino minimo ya ha sido calculado
	vector<int> d;												// vector de coste
	vector<unsigned> pred;
	unsigned s, candidato, minimo = maxint, aux = 0;

	PermanentementeEtiquetado.resize (n, false);				// etiquetados a false
	d.resize (n, maxint);											// d es la etiqueta de distancia		(n) 		maxint = infinito
	pred.resize (n, UERROR);										// Los predecesores son unicos, por lo que puedo usar un array

	cout << endl;
	cout << " - Introduzca el nodo de partida [1-" << n << "]: ";
	cin >> s;
	cout << endl;
	
	s--;
	d[s]= 0;				// coste para llegar a el desde el = 0
	pred[s]= s;				//pred del nodo elegido (i) = i
	
	do {
		 
		candidato = UERROR;
		
		while ((candidato == UERROR) && (aux < n)) {
				if (PermanentementeEtiquetado[aux] == false)
					candidato = aux;
				else
					aux++;
		}		//Sea candidato el nodo no etiquetado permanentemente con menor etiqueta distancia;
		
		
		if (candidato != UERROR) {					// si me encuentro un nodo con una etiqueta no infinita
			
			minimo = d[candidato];
			
			for (unsigned j = 0; j < n; j++) {
				
				if (d[j] < minimo) { 
					if (PermanentementeEtiquetado[j] == false) {
						
						minimo = d[j];
						candidato = j;
					}
				}
			}
			
			PermanentementeEtiquetado[candidato] = true;
				                       
				for (unsigned k = 0; k < LS[candidato].size (); k++) {		// para todo nodo k en LS[candidato] 
					
					if (d[LS[candidato][k].j] > d[candidato] + LS[candidato][k].c) {		// d[LS[candidato][k].j]			LS[candidato][k].c
						d[LS[candidato][k].j] = d[candidato] + LS[candidato][k].c;
						pred[LS[candidato][k].j] = candidato;
					}
			    }
		}
	} while (candidato != UERROR);
	
	for (int i = 0; i < n; i++) {				// Para todo nodo i!= s
		
		if (i != s) {
			
			if (pred[i] != UERROR)
				MostrarCamino (s, i, pred, d);
			else
				cout << " * No hay Camino desde " << s + 1 << " al nodo " << i + 1 << endl;
		}
	}
}




void GRAFO::MostrarCamino (unsigned s, unsigned i, vector <unsigned> &pred) {

   if (i != s) {
      MostrarCamino (s, pred[i], pred);
   }
   cout << i+1 << " -> ";
}

void GRAFO::MostrarCamino (unsigned s, int i, vector<unsigned> &pred, vector<int> &d) {
	
	unsigned q = d[i];
	cout << " - El camino desde " << s + 1 << " al nodo " << i + 1 << " es: " << i + 1;
	
	do {
		cout << " -> " << pred[i] + 1;
		i = pred[i];
	} while (pred[i] != i);
	
	cout << " de longitud " << q << endl;
}
