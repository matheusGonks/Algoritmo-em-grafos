//Alunos: Gustavo Costa Daguer , Matheus Silva GOnçalves , Milton Carvalhaes Pereira Neto

#include <iostream>
#include <list>
#include <limits>
#include <queue>
using namespace std;

#define INFINITO 100000000;

typedef pair<int, int> par_de_vertices;

class Grafo{
    private:
        int quantidade_vertices; 
        list<pair<int,int> > *lista_Adjacencia; //vertice destino e peso
        int *custo;
        int *pai;

    public:

        Grafo(int v){
            this->quantidade_vertices = v;
            lista_Adjacencia = new list<pair<int,int>>[v + 1]; 
            custo = new int[v + 1];
            pai = new int[v + 1];

            for(int i = 1; i <= v; i++){
                custo[i] = INFINITO;
                pai[i] =  -1;
            }
        }

        int getCusto(int v){
            return custo[v];
        }

        void adicionarAresta(int u, int v, int peso){ 
            lista_Adjacencia[u].push_back(make_pair(v, peso));
            lista_Adjacencia[v].push_back(make_pair(u, peso));
        }   

        void removerAresta(int u, int v){ 
 
            lista_Adjacencia[u].remove_if([v](auto it) { 
                    return it.first == v; 
            });

            lista_Adjacencia[v].remove_if([u](auto it) { 
                    return it.first == u; 
            });

            for(int i = 1; i <= v; i++){
                custo[i] = INFINITO;
                pai[i] =  -1;
            }

        }  

        void eliminarRotas(int v){
            if(v > 1){
                removerAresta(pai[v], v);
                eliminarRotas(pai[v]);
            }            
        }

        void aplicaDijkstra(int fonte){

            priority_queue < par_de_vertices, vector<par_de_vertices>, greater <par_de_vertices> > fila; //Min HEAP 
        
            fila.push(make_pair(0, fonte)); 
            custo[fonte] = 0;

            while(!fila.empty()){

                int u = fila.top().second;
                fila.pop();

                list< pair<int, int> >::iterator i;
                for (i = lista_Adjacencia[u].begin(); i != lista_Adjacencia[u].end(); i++){
                    
                    int v = (*i).first;
                    int peso = (*i).second;
        
                    if (custo[v] > custo[u] + peso){
                        
                        pai[v] = u;
                        custo[v] = custo[u] + peso;
                        fila.push(make_pair(custo[v], v));
                    }
                }
            } 
 
        }
};

int main(){
    
    
    int instancia = 1;
    
    while(!cin.eof()){
        int N, M;//Numero de cidades; numero de rotas
        cin >> N >> M;

        Grafo* planoVoos = new Grafo(N);

        while(M != 0){
            
            int vertA, vertB, custo;
            cin >> vertA >> vertB >> custo;

            planoVoos->adicionarAresta(vertA, vertB, custo);

            M--;
        }

        int D, K; //D = numero de amigos e K = numero de assentos livres
        cin >> D >> K;

        int custoAtualN, custoTotal = 0;
        while(D > 0){

            planoVoos->aplicaDijkstra(1);
            custoAtualN = planoVoos->getCusto(N);

            if(custoAtualN != 100000000) planoVoos->eliminarRotas(N);

            if(D > K){
                custoTotal +=  custoAtualN * K;
                D = D - K;

            }else{
                custoTotal += custoAtualN * D;
                D -= D;
            }
        }

        cout << "Instancia " << instancia << endl;        
        if(custoAtualN == 100000000){
            cout << "impossivel" << endl << endl;        
        }else{
            cout << custoTotal << endl << endl;            
        }

        instancia++;

    } 
  
    return 0;

}    
