//Alunos: Gustavo Daguer, Matheus Goncalves, Milton Neto
//implementacao utiliza o algoritmo de kruskal, que parte de varios conjuntos (floresta) ate que
//eles se conectam e passam a formar uma Arvore Geradora.
// a diferenca deste exercicio pra um problema de arvore geradora minima e que aqui ja existem estrada(s)
//ja construidas, entao e necessario fazer a uniao dos conjuntos das cidades de estradas ja existentes
// antes de realizar o kruskal de fato

#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
using namespace std;

typedef pair <int, int> meuPar; //vertices de uma aresta
typedef pair <int, int> coord; //pontox e pontoy

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

class Rodovia{
    
    private:
        int numVertices, custoNovasEstradas = 0;
        coord *verticesPlano; //vertice e posicao
        vector<pair<int, meuPar>> arestas; //peso e aresta
        ConjuntoDisjunto *conj; 

    public:

        Rodovia(int numVertices){
            this->numVertices = numVertices;
            verticesPlano = new coord[numVertices + 1];
            conj = new ConjuntoDisjunto(numVertices);
        }

        int distancia(int u, int v){ //calcula a distancia entre os vertices u e v no plano
            int x_de_U = verticesPlano[u].first;
            int y_de_U = verticesPlano[u].second;

            int x_de_V = verticesPlano[v].first;
            int y_de_V = verticesPlano[v].second;

            int deltaX = abs(x_de_V - x_de_U);
            int deltaY = abs(y_de_V - y_de_U);

            return round( sqrt( pow(deltaX, 2) + pow(deltaY, 2) ) );
        }
        
        void addVertice(int u, int posX, int posY){ //adiciona a cidade no plano
            verticesPlano[u].first = posX;
            verticesPlano[u].second = posY;
        }     

        void addAresta(int u, int v){   //transforma a linha reta de distancia de u ate v em uma aresta
            int dist = distancia(u, v);
            arestas.push_back(make_pair(dist, make_pair(u, v))); //distancia equivale ao peso
        }

        void possiveisEstradas(){ // simula as distancias como arestas
            for(int i = 1; i <= numVertices; i++){
                for(int j = 1; j <= numVertices; j++){
                    if(i != j){
                        if(conj->busca(i) != conj->busca(j)){ //deve considerar a distancia entre vertices que nao estao nas estradas ja construidas
                            addAresta(i, j);
                        }
                    }    
                }
            }
        }    

        void estradaPronta(int u, int v){ //estradas ja construidas sao arestas que devem ser consideradas ja parte da arvore
            int compU = conj->busca(u);
            int compV = conj->busca(v);
            conj->uniao(compU, compV);
        }

        void construirEstradas(){ //completa a rodovia com as arestas mais baratas, kruskal de fato

            sort(arestas.begin(), arestas.end());

            vector<pair <int, meuPar> >::iterator it;
            for(it = arestas.begin(); it != arestas.end(); it++){

                int u = it->second.first;
                int v = it->second.second;
  
                int componenteU = conj->busca(u);
                int componenteV = conj->busca(v);     
            
                if(componenteU != componenteV){
                    conj->uniao(componenteU, componenteV); 
                    custoNovasEstradas += it->first;               
                }  
            }
        }

        int getCustoNovasEstradas(){
            return custoNovasEstradas;
        }
};

int main()
{
    
    int n;
    cin >> n;

    Rodovia IslaBonita(n);
  
    for(int i = 1; i <= n; i++){
        int xi, yi;
        cin >> xi >> yi;
        IslaBonita.addVertice(i, xi, yi);
    }

    int m;
    cin >> m;

    for(int i = 1; i <= m; i++){
        int m1, m2;
        cin >> m1 >> m2;
        IslaBonita.estradaPronta(m1, m2);
    }

    IslaBonita.possiveisEstradas();
    IslaBonita.construirEstradas();

    cout << IslaBonita.getCustoNovasEstradas() << endl;
  
    return 0;
}


