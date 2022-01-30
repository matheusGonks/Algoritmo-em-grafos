#include <iostream>
#include <queue>
#include <vector>
#include <limits>
using namespace std;

#define BRANCO 0;
#define CINZA 1;
#define PRETO 2;
#define INFINITO numeric_limits<int>::max();

class Grafo{
    private:
        int numVertices;
        int* pai; 
        int* cor; //indica o status do vertice quanto a sua exploracao
        int* distancia; //menor distancia a partir da origem
        vector<int>* listaAdj;

    public:
        Grafo(int numVertices);
        void addAresta(int u, int v);
        void bfs();
        void printaGrafo();
};

Grafo::Grafo(int numVertices){
    this->numVertices = numVertices;
    distancia = new int [numVertices + 1];
    pai = new int[numVertices + 1];
    cor = new int[numVertices + 1];
    listaAdj = new vector<int>[numVertices + 1];

    for(int i = 1; i <= numVertices; i++)
    {
        distancia[i] = INFINITO; 
        pai[i] = -1;
        cor[i] = BRANCO;
    }
    
}

void Grafo::addAresta(int u, int v){
    listaAdj[u].push_back(v);
}

void Grafo::bfs(){ //algoritmo padrao de busca em largura
    
    int origem = 1;
    queue<int> fila; //cria fila
    fila.push(origem);

    distancia[origem] = 0;
    cor[origem] = CINZA; //marca o primeiro vertice como visitado

    while(!fila.empty()){
        int vertAtual = fila.front(); //o vertice que eh analisado eh o primeiro da fila
        fila.pop();

        vector<int>::iterator it; 
        for(it = listaAdj[vertAtual].begin(); it != listaAdj[vertAtual].end(); it++) //olha sua adjacencias
        {
            if(cor[*it] == 0){ //vertice ainda nao descoberto; nao sei porque nao funciona usando "BRANCO"
                cor[*it] = CINZA;
                pai[*it] = vertAtual;
                distancia[*it] = distancia[vertAtual] + 1; //caso a aresta tenha peso 1

                fila.push(*it);
            }

            cor[vertAtual] = PRETO; //marcando vertice como explorado
        }
    }

}

void Grafo::printaGrafo(){
    for(int i = 1; i <= numVertices; i++)
    {
        cout << "Vertice " << i << "\n";
        cout << "Distancia: " << distancia[i] << endl;
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

    meuGrafo.bfs();
    meuGrafo.printaGrafo();

    return 0;
}
