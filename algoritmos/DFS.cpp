#include <iostream>
#include <vector>
#include <limits>
using namespace std;

#define BRANCO 0;
#define CINZA 1;
#define PRETO 2;
#define INFINITO numeric_limits<int>::max();

class Grafo{
    private:
        int numVertices, tempo = 0;
        int *pai, *cor; //indica o status do vertice quanto a sua exploracao
        int *tempoDescoberta, *tempoTermino; //
        vector<int>* listaAdj;

    public:
        Grafo(int numVertices);
        void addAresta(int u, int v);
        void dfs();
        void visitaVertice(int vert);
        void printaGrafo();
};

Grafo::Grafo(int numVertices){
    this->numVertices = numVertices;
    tempoDescoberta = new int[numVertices + 1];
    tempoTermino = new int[numVertices + 1];
    
    pai = new int[numVertices + 1];
    cor = new int[numVertices + 1];
    
    listaAdj = new vector<int>[numVertices + 1];

    for(int i = 1; i <= numVertices; i++)
    {
        tempoTermino[i] = INFINITO;
        tempoDescoberta[i] = INFINITO; 
        pai[i] = -1;
        cor[i] = BRANCO;
    }
    
}

void Grafo::addAresta(int u, int v){
    listaAdj[u].push_back(v);
}

void Grafo::dfs(){ //algoritmo padrao de busca em profundidade
    for(int i = 1; i <= numVertices; i++){
        if(cor[i] == 0) visitaVertice(i); 
        //0 era pra ser 'BRANCO' mas nao funciona; se o grafo nao for conexo 
        //acho que nao precisa da dfs ser dividida em dosi metodos, usei o 
        //pseudocodigo do livro 'Algoritmo e Estrutura de Dados' do Cormen,cap 22
    }
}

void Grafo::visitaVertice(int vert){
    cor[vert] = CINZA; //indica que foi visitado
    tempo++; tempoDescoberta[vert] = tempo;

    vector<int>::iterator it; //olha suas adjacencias
    for(it = listaAdj[vert].begin(); it != listaAdj[vert].end(); it++){
        if(cor[*it] == 0){
            pai[*it] = vert;
            visitaVertice(*it);
        }
    }

    cor[vert] = PRETO; //termino de sua exploracao
    tempo++; tempoTermino[vert] = tempo;
}

void Grafo::printaGrafo(){
    for(int i = 1; i <= numVertices; i++){
        cout << "Vertice " << i << "\n";
        cout << "Tempo de Descoberta: " << tempoDescoberta[i] << endl;
        cout << "Tempo de termino: " << tempoTermino[i] << endl;
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

    meuGrafo.dfs();
    meuGrafo.printaGrafo();

    return 0;
}
