#include <iostream>
#include <vector>
using namespace std;

class Grafo{
    private:
        int numVertices;
        int* grauSaida;
        int * grauEntrada; //de cada vertice
        int** matrizAdj; 

    public:
        Grafo(int numVertices);
        void addAresta(int u, int v);
        void printaGrafo();
};

Grafo::Grafo(int numVertices){
    this->numVertices = numVertices;
    grauSaida = new int[numVertices];
    grauEntrada = new int[numVertices];        
    matrizAdj = new int*[numVertices];
    
    for(int i = 0; i < numVertices;i++){
        matrizAdj[i] = new int[numVertices];
        grauEntrada[i] = 0;
        grauSaida[i] = 0;
    }

    for(int i = 0; i < numVertices; i++)
    {
        for(int j = 0; j < numVertices; j++){
            matrizAdj[i][j] = 0;
        }
    }
}

void Grafo::addAresta(int u, int v){
    matrizAdj[u][v] = 1;
    //matrizAdj[v][u] = 1; essa linha eh ignorada considerando que o grafo seja direcionado
    //caso nao seja, ainda assim da pra tratar a matriz pra ignorar abaixo da diagonal
    grauSaida[u]++;
    grauEntrada[v]++;
}

void Grafo::printaGrafo(){
    //laco que 'visita' cada vertice do grafo
    for(int i = 0; i < numVertices; i++){
        cout << i << "(head)";
        //percorre as adjacencias de cada vertice 
        for(int j = 0; j < numVertices; j++){
            if(matrizAdj[i][j] == 1) cout << "-" << j; 
        }

    cout << " -> seu grau  de saida eh " << grauSaida[i]
         << " e seu grau de entrada eh " << grauEntrada[i]
         << endl;    
    
    }
}

int main(){
    
    int numero_Vertices, numero_Arestas;
    cout << "Insira o numero de vertices: "; cin >> numero_Vertices;
    cout << "Insira o numero de Arestas: "; cin >> numero_Arestas;

    Grafo meuGrafo(numero_Vertices);

    while(numero_Arestas != 0){
    int u, v;
        cin >> u >> v;
        meuGrafo.addAresta(u,v);
        
        numero_Arestas--;
    }

    meuGrafo.printaGrafo();

    return 0;
 
}


    