#include <iostream>
#include <list>
#include <limits>
#include <queue>
using namespace std;

#define INFINITO std::numeric_limits<int>::max();

typedef pair<int, int> par_de_vertices;

class Grafo{
    private:
        int quantidade_vertices;
        list<pair<int,int> > *lista_Adjacencia; //vertice destino e peso
        int *distancia;

    public:

        Grafo(int v){
            quantidade_vertices = v;
            lista_Adjacencia = new list<pair<int,int>>[v]; 
            distancia = new int[v];

            for(int i = 0; i < v; i++){
                distancia[i] = INFINITO; 
            }
        }

        void adicionarAresta(int u, int v, int peso){ 
            lista_Adjacencia[u].push_back(make_pair(v, peso));
            lista_Adjacencia[v].push_back(make_pair(u, peso));
        }     

        void aplicaDijkstra(int fonte){

            priority_queue < par_de_vertices, vector<par_de_vertices>, greater <par_de_vertices> > fila; //Min HEAP 
        
            fila.push(make_pair(0, fonte)); 
            distancia[fonte] = 0;

            while(!fila.empty()){

                int u = fila.top().second;
                fila.pop();

                list< pair<int, int> >::iterator i;
                for (i = lista_Adjacencia[u].begin(); i != lista_Adjacencia[u].end(); i++){
                    // Get vertex label and weight of current adjacent
                    // of u.
                    int v = (*i).first;
                    int peso = (*i).second;
        
                    //  If there is shorted path to v through u.
                    if (distancia[v] > distancia[u] + peso){
                        
                        distancia[v] = distancia[u] + peso;
                        fila.push(make_pair(distancia[v], v));
                    }
                }
            }

            // Print shortest distances stored in dist[]
            printf("Vertex   Distance from Source\n");
            for (int i = 0; i < quantidade_vertices; i++){
                printf("%d \t\t %d\n", i, distancia[i]);
            }   
        }
};

int main(){
    // create the graph given in above figure
    int V; cin >> V;
    Grafo g(V);
  
    //  making above shown graph
    while(V != 0){
        int u, v, peso; 
        cin >> u >> v >> peso;
        g.adicionarAresta(u, v, peso);

        V--;    
    }
    
  
    g.aplicaDijkstra(0);
  
    return 0;

}    
