#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

typedef pair <int, int> meuPar; //define a aresta

class ConjuntoDisjunto{

    private:    
        int *pai, *rank;
        int numConjuntos;

    public:
        ConjuntoDisjunto(int numConjuntos){
            this->numConjuntos = numConjuntos;
            int n = numConjuntos;

            pai = new int[n + 1];
            rank = new int[n + 1];

            for(int i = 0; i <= n; i++){
                pai[i] = i;
                rank[i] = 0;
            }
        }

        int busca(int u){
            if(pai[u] == u) return u;
        
            pai[u] = busca(pai[u]);
            return pai[u];
        }

        void uniao(int u, int v){
            int compoU = busca(u);
            int compoV = busca(v);

            if(compoU != compoV){
                if(rank[compoU] > rank[compoV])
                    pai[compoV] = compoU;
            
                else{
                    pai[compoU] = compoV;
                    if (rank[compoU] == rank[compoV]) rank[compoV]++;
                }
            }
        }
};

class Grafo{
    
    private:
        int numVertices, pesoAGM = 0;
        vector<pair<int, meuPar>> arestas; //peso e aresta

    public:
        Grafo(int numVertices){
            this->numVertices = numVertices;
        }
        
        void addAresta(int u, int v, int peso){
            arestas.push_back(make_pair(peso, make_pair(u,v)));
        }

        int getPesoAGM(){
            return pesoAGM;
        }     

        void kruskal(){

            sort(arestas.begin(), arestas.end());

            ConjuntoDisjunto conj(numVertices);

            vector<pair <int, meuPar> >::iterator it;
            for(it = arestas.begin(); it != arestas.end(); it++){

                int u = it->second.first;
                int v = it->second.second;
  
                int componenteU = conj.busca(u);
                int componenteV = conj.busca(v);     
            
                if(componenteU != componenteV){

                    conj.uniao(componenteU, componenteV);    
                    pesoAGM += it->first;
                    cout << u << " - " << v << endl;                
                }  
            }
        }
};

int main()
{
    
    int V, E;
    cin >> V >> E;
    Grafo g(V);
  
    while(E != 0){
        int vert1, vert2, peso;
        cin >> vert1 >> vert2 >> peso;
        g.addAresta(vert1, vert2, peso);

        E--;
    }
  
    cout << "Edges of MST are \n";
    g.kruskal();
  
    cout << "\nWeight of MST is " << g.getPesoAGM() << endl;
  
    return 0;
}


