//grafo direcionado
//vertice zero incluso
#include <iostream>
#include <vector>
using namespace std;

class Grafo{
    private:
        int numVertices, numArestas;
        int** matrizIncidencia; 

    public:
        Grafo(int numVertices, int numArestas);
        void addAresta(int u, int v, int aresta);
        void printaMatriz();
};

Grafo::Grafo(int numVertices,int numArestas){
    this->numVertices = numVertices;
    this->numArestas = numArestas;    
    matrizIncidencia = new int*[numArestas];
    
    for(int i = 0; i < numArestas;i++){
        matrizIncidencia[i] = new int[numVertices];
    }

    for(int i = 0; i < numArestas; i++)
    {
        for(int j = 0; j < numVertices; j++){
            matrizIncidencia[i][j] = 0;
        }
    }
}

void Grafo::addAresta(int u, int v, int aresta){
    
    matrizIncidencia[aresta][u] = 1;
    matrizIncidencia[aresta][v] = -1; //grafo direcionado

}

void Grafo::printaMatriz(){
    for(int i = 0; i < numArestas; i++){ 
        for(int j = 0; j < numVertices; j++){
            cout << matrizIncidencia[i][j] << " " ; 
        }

        cout << endl;    
    }
}

int main(){
    
    int numero_Vertices, numero_Arestas;
    cout << "Insira o numero de vertices: "; cin >> numero_Vertices;
    cout << "Insira o numero de Arestas: "; cin >> numero_Arestas;

    Grafo meuGrafo(numero_Vertices, numero_Arestas);

    for(int aresta = 0; aresta < numero_Arestas; aresta++){
        int u, v;
        cin >> u >> v;
        
        meuGrafo.addAresta(u,v,aresta);        
    }

    meuGrafo.printaMatriz();

    return 0;
 
}


    
