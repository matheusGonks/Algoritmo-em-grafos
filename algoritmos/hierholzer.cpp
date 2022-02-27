//tirado de: https://www.geeksforgeeks.org/hierholzers-algorithm-directed-graph/
//o codigo nao euleriza o grafo, ja espera que o que ele recebe eh um grafo euleriano 

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Grafo{
    private:
        int numVertices;
        vector<int> *listaAdj; //lista de Adjacencia de cada vertice
        vector<int> circuito; //um circuito que esta sendo percorrido
        stack<int> caminhoAtual; //caminho atual
        int *quant_Arcos_Saindo;

    public:
        Grafo(int numVertices){ //inicializando     um grafo
            this->numVertices = numVertices + 1;
            listaAdj = new vector<int>[numVertices + 1];
            quant_Arcos_Saindo = new int[numVertices + 1];
        }

        void adicionarArco(int u, int v){
            listaAdj[u].push_back(v);
        }

        void realizaHierholzer(){
            for(int i = 1; i <= numVertices; i++){
                quant_Arcos_Saindo[i] = listaAdj[i].size(); 
                //saber quantos arcos saem de cada vertice permite
                //saber , durante a execucao, se ainda existem arestas inexploradas
            }

            int verticeAtual = 1;
            caminhoAtual.push(1);

            while(!caminhoAtual.empty()){
                
                if( quant_Arcos_Saindo[verticeAtual] != 0){
                    caminhoAtual.push(verticeAtual);

                    int proximoVertice = listaAdj[verticeAtual].back();

                    quant_Arcos_Saindo[verticeAtual]--;
                    listaAdj[verticeAtual].pop_back();

                    verticeAtual = proximoVertice;
                
                }else{
                    circuito.push_back(verticeAtual);
                    verticeAtual = caminhoAtual.top();
                    caminhoAtual.pop();

                }

            }
        }

        void printaCircuitoGerado(){
            for(int i = circuito.size() - 1; i >= 0; i--){
                cout << circuito[i];

                if(i) cout << " -> ";
            }
            
            cout << endl;
        }
};

int main()
{
    cout << "Quantos vertices tem o grafo?\n";
    int numVertices; cin >> numVertices;
    Grafo meuGrafo(numVertices);

    cout << "Quantas Arestas?\n";
    int numArestas; cin >> numArestas;

    cout << "Insira as arestas:\n";
    
    while(numArestas){
        int u, v;
        cin >> u >> v;
        meuGrafo.adicionarArco(u,v);

        numArestas--;
    }

    meuGrafo.realizaHierholzer();
    meuGrafo.printaCircuitoGerado();
}
