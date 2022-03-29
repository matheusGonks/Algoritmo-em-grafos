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
    int V = 9;
    Grafo g(V);
  
    //  making above shown graph
    g.adicionarAresta(0, 1, 4);
    g.adicionarAresta(0, 7, 8);
    g.adicionarAresta(1, 2, 8);
    g.adicionarAresta(1, 7, 11);
    g.adicionarAresta(2, 3, 7);
    g.adicionarAresta(2, 8, 2);
    g.adicionarAresta(2, 5, 4);
    g.adicionarAresta(3, 4, 9);
    g.adicionarAresta(3, 5, 14);
    g.adicionarAresta(4, 5, 10);
    g.adicionarAresta(5, 6, 2);
    g.adicionarAresta(6, 7, 1);
    g.adicionarAresta(6, 8, 6);
    g.adicionarAresta(7, 8, 7);
  
    g.aplicaDijkstra(0);
  
    return 0;

}    
