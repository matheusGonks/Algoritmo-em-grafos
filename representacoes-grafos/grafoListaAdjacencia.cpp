#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

class Grafo{
    private:
        int numVertices;
        int* grau; //de cada vertice
        vector<int>* listaAdj; 

    public:
        Grafo(int numVertices);
        void addAresta(int u, int v);
        void printaGrafo();
};

Grafo::Grafo(int numVertices){
    this->numVertices = numVertices;
    grau = new int[numVertices];
            
    //cria uma array de vetores dinamicos, representando cada 
    //elemento e suas respectivas adjacencias
    listaAdj = new vector<int>[numVertices];
    memset(grau, 0, numVertices);

}

void Grafo::addAresta(int u, int v){

    // evitando a leitura de vertices repetidos nas listas
    //if(find(lista_adj[u].begin(), lista_adj[u].end(), v) == lista_adj[u].end());

    listaAdj[u].push_back(v);
    listaAdj[v].push_back(u); //esta linha eh so no caso de um grafo nao direcionado

    grau[u]++;
    grau[v]++;
}

void Grafo::printaGrafo(){
    //laco que 'visita' cada vertice do grafo
    for(int i = 0; i < numVertices; i++){
        
        cout << i << "(head)";
        
        vector<int>::iterator it; //percorre as adjacencias de cada vertice 
        for(it = listaAdj[i].begin(); it != listaAdj[i].end(); it++){
            cout << "-" << *it ; 
        }

    cout << " -> seu grau eh " << grau[i];
    cout << endl;
    
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


    