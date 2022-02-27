#include <iostream>
#include <vector>
#include <limits>
using namespace std;

#define INFINITO numeric_limits<int>::max();

class Grafo{
    private:
        int numVertices, tempo = 0;
        int *pai, *cor; //indica o status do vertice quanto a sua exploracao
        vector<int>* listaAdj;
        int possibilidades_caminhos = 0;

    public:
        Grafo(int numVertices);
        void addAresta(int u, int v);
        void dfs();
        void visitaVertice(int vert);
        void getCaminhosPossiveis();
};

Grafo::Grafo(int numVertices){
    this->numVertices = numVertices;
    
    pai = new int[numVertices + 1];
    cor = new int[numVertices + 1];
    
    listaAdj = new vector<int>[numVertices + 1];

    for(int i = 1; i <= numVertices; i++)
    {
        pai[i] = -1;
    }
    
}

void Grafo::addAresta(int u, int v){
    listaAdj[u].push_back(v);
}

void Grafo::dfs(){ //algoritmo padrao de busca em profundidade
        visitaVertice(1); 
}

void Grafo::visitaVertice(int vert){
    vector<int>::iterator it; //olha suas adjacencias
    for(it = listaAdj[vert].begin(); it != listaAdj[vert].end(); it++){
            pai[*it] = vert;
            visitaVertice(*it);
    }
    
    if(listaAdj[vert].empty()) possibilidades_caminhos++;
    
}

void Grafo::getCaminhosPossiveis(){
    cout << possibilidades_caminhos << endl;
}

int main(){

    int numero_Vertices;
    cin >> numero_Vertices;
    
    Grafo meuGrafo(numero_Vertices);

    int vertice_u, vertice_v;
    cin >> vertice_u >> vertice_v;

    while(vertice_u != -1 and vertice_v != -1){
        meuGrafo.addAresta(vertice_u,vertice_v);
        cin >> vertice_u >> vertice_v;
    }

    meuGrafo.dfs();
    meuGrafo.getCaminhosPossiveis();

    return 0;
}
