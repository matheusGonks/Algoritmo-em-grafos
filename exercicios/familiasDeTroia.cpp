#include <iostream>
#include <algorithm>
#include <list>
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
                pai[i] = i; //cada vertice é inicializado como conjunto, pai de si mesmo
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

                numConjuntos--;//cada vez que conjuntos sao fundidos , o numero de conjuntos é decrementado 
            }
        }

        int getNumeroDeConjuntos(){
            return numConjuntos;
        }
};

class Grafo{
    
    private:
        int numIndividuos;
        list<int> *parentesco; 

    public:
        Grafo(int numIndividuos){
            this->numIndividuos = numIndividuos;
            parentesco = new list<int>[numIndividuos + 1];
        }
        
        void addParentesco(int u, int v){
            parentesco[u].push_back(v);
            parentesco[v].push_back(u);
        }   

        int retornaFamilias(){
 
            ConjuntoDisjunto conj(numIndividuos);

            for(int i = 1; i <= numIndividuos; i++){
                
                list<int>::iterator it;
                for(it = parentesco[i].begin(); it != parentesco[i].end(); it++){
                    
                    int v = (*it);
    
                    int componenteU = conj.busca(i);
                    int componenteV = conj.busca(v);     
                
                    if(componenteU != componenteV) conj.uniao(componenteU, componenteV);    
                }
            } 

            return conj.getNumeroDeConjuntos();
        }
};

int main()
{
    
    int N, M;
    cin >> N >> M;

    Grafo *familias = new Grafo(N); 

    while(M != 0){
        int u, v;
        cin >> u >> v;

        familias->addParentesco(u,v);
        
        M--;
    }

    cout << familias->retornaFamilias() << endl;
  
    return 0;
}


