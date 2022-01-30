#include <iostream>
using namespace std;

class Grafo{
    private:
        int numVertices;
        int** matrizAdj; 
        int** fecho; //matriz em que o warshall eh executado

    public:
        Grafo(int numVertices);
        void warshall();
        void addAresta(int u, int v);
        void printaGrafo();
};

Grafo::Grafo(int numVertices){
    this->numVertices = numVertices;     
    matrizAdj = new int*[numVertices + 1]; //esse codigo nao considera 0 um vertice
    fecho = new int*[numVertices + 1];
    
    for(int i = 1; i <= numVertices; i++){
        matrizAdj[i] = new int[numVertices + 1];
        fecho[i] = new int[numVertices + 1];
    }

    for(int i = 1; i <= numVertices; i++){
        for(int j = 1; j <= numVertices; j++){
            matrizAdj[i][j] = fecho[i][j] = 0;
        }
    }
}

void Grafo::addAresta(int u, int v){
    matrizAdj[u][v] = fecho[u][v] = 1; 
}

void Grafo::warshall(){
    for (int k = 1; k <= numVertices; k++){
        for (int i = 1; i <= numVertices; i++){
            for (int j = 1; j <= numVertices; j++){
                fecho[i][j] = fecho[i][j] || (fecho[i][k] and fecho[k][j]);    
            }
        }
    }    
}

void Grafo::printaGrafo(){
    for(int i = 1; i <= numVertices; i++){
        for(int j = 1; j <= numVertices; j++){
            cout << matrizAdj[i][j] << " "; 
        }

        cout << endl;    
    }

    cout << "Fecho transitivo de cada vertice" << endl;
    for(int i = 1; i <= numVertices; i++){
        cout << "Vertice " << i << ": ";
        for(int j = 1; j <= numVertices; j++){
            if(fecho[i][j]){
                cout << j << " ";
            }
        }

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

    meuGrafo.warshall();
    meuGrafo.printaGrafo();

    return 0;
 
}


    
