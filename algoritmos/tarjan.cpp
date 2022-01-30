//algoritmo de tarjan que eu nao faco ideia do porque, mas funciona mais ou menos bem
//Tem um problema com os vetores resultntes de tempoDescoberta e pai (testem ai pra ver), no final da execucao 
//quase sempre no primeiro vertice; ainda sim o algoritmo faz o que tem que fazer que eh
//identificar quais arestas sao pontes no grafo,( pelo menos eh o que aconteceu com os 4 testes que eu fiz)
//baseei quase tudo no codigo que o professor deu

#include <iostream>
#include <vector>
#include <limits>
using namespace std;

class Grafo{
    private:
        int numVertices, tempo = 0;
        bool *articulacao;
        int *pai;  //indica o status do vertice quanto a sua exploracao
        int *tempoDescoberta, *low; //
        vector<int>* listaAdj;

    public:
        Grafo(int numVertices);
        void addAresta(int u, int v);
        void aplicaTarjan();
        void tarjan(int u);
        void printaGrafo();
};

Grafo::Grafo(int numVertices){
    this->numVertices = numVertices;
    tempoDescoberta = new int[numVertices + 1];
    low = new int[numVertices + 1];
    
    pai = new int[numVertices + 1];
    articulacao = new bool[numVertices + 1];
    
    listaAdj = new vector<int>[numVertices + 1];

    for(int i = 1; i <= numVertices; i++){
        low[i] = 0;
        tempoDescoberta[i] = 0; 
        pai[i] = -1;
        articulacao[i] = false;
    }
    
}

void Grafo::addAresta(int u, int v){
    listaAdj[u].push_back(v);
    listaAdj[v].push_back(u);
}

void Grafo::tarjan(int u){ 
    low[u] = tempoDescoberta[u] = tempo++;
 
    vector<int>::iterator it;
    for(it = listaAdj[u].begin(); it != listaAdj[u].end(); it++){
        int v = *it;
        if(tempoDescoberta[v] == 0){
            pai[v] = u;
             
            tarjan(v);
        
            if(low[v] >= tempoDescoberta[u]){
                articulacao[u] = true;
            }
        
            if(low[v] > tempoDescoberta[u]){
                cout << "ponte: (" << u << ", " << v << ")" << endl;
            }
     
            low[u] = min(low[u], low[v]);
        }
    
        else if(v != pai[u]){
            low[u] = min(low[u], low[v]);
        }
    }
}

void Grafo::aplicaTarjan(){
    for(int i = 1; i <= numVertices; i++){
        if(tempoDescoberta[i] == 0) tarjan(i);
    }
}

void Grafo::printaGrafo(){
    for(int i = 1; i <= numVertices; i++){
        cout << "Vertice " << i << "\n";
        cout << "Tempo de Descoberta: " << tempoDescoberta[i] << endl;
        cout << "low: " << low[i] << endl;
        cout << "Pai: " << pai[i] << endl << endl;
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

    meuGrafo.aplicaTarjan();
    meuGrafo.printaGrafo();

    return 0;
}
