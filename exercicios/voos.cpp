//Gustavo Costa Daguer, Matheus Gonçalves, Milton Pereira Carvalhaes Neto
//Utilizando o algoritmo de warshall pra verificar a alcançabilidade das cidades
//de acordo com o catalogo de voos de cada aviação

#include <iostream> 
using namespace std;

class Grafo{
    private:
        int numMaximoCidades; //utlizado para alocar uma matriz mais proxima do tamanho necessario
        int** matrizAdj; 
        int** fecho; //matriz em que o warshall eh executado

    public:
        Grafo(int numMaximoCidades);
        void warshall(int numeroRealCidades);
        void addAresta(int u, int v);
        bool existeEscala(int u, int v);

};

Grafo::Grafo(int maxCidades){
    this->numMaximoCidades = maxCidades;     
    matrizAdj = new int*[numMaximoCidades];
    fecho = new int*[numMaximoCidades];
    
    for(int i = 0; i < numMaximoCidades; i++){
        matrizAdj[i] = new int[numMaximoCidades + 1];
        fecho[i] = new int[numMaximoCidades + 1];
    }

    for(int i = 0; i < numMaximoCidades; i++){
        for(int j = 0; j < numMaximoCidades; j++){
            matrizAdj[i][j] = fecho[i][j] = 0;
        }
    }
}

void Grafo::addAresta(int u, int v){
    matrizAdj[u][v] = fecho[u][v] = 1; 
}

void Grafo::warshall(int numeroRealCidades){ //o parametro nos dá os limites da matriz alocada, em que realmente existem cidades
    for (int k = 0; k <= numeroRealCidades; k++){
        for (int i = 0; i <= numeroRealCidades; i++){
            for (int j = 0; j <= numeroRealCidades; j++){
                fecho[i][j] = fecho[i][j] || (fecho[i][k] and fecho[k][j]);    
            }
        }
    }    
}

bool Grafo::existeEscala(int u, int v){
    return fecho[u][v];
}

int main(){
    
    int casosTeste;
    int numero_voos_A, numero_voos_B;
    int origem, destino;

    cin >> casosTeste;
    while(casosTeste != 0){
        
        bool equivalente = true; //assume equivalencia entre as duas aviacoes
        int aux;//utilizo na comparacao 

        cin >> numero_voos_A;
        Grafo *voeBem = new Grafo(2 * numero_voos_A); int ultimaCidadeA = 0; 
        //com dada quantidade de voos, o maximo de cidades que podem existir é 2 * o numero
        //de voos, no caso em que cada origem e destino fossem unicos.
        //a variavel ultimaCidade indica a cidade de maior indice na matriz de A e de B

        while(numero_voos_A != 0){
            cin >> origem >> destino;
            voeBem->addAresta(origem, destino);
            
            aux = max(origem,destino);//armazena o maior indice ate o instante do codigo
            ultimaCidadeA = max(aux, ultimaCidadeA);

            numero_voos_A--;
        }

        voeBem->warshall(ultimaCidadeA); //fecho transitivo do catalogo da aviacao voeBem

        cin >> numero_voos_B;
        Grafo *voeLivre = new Grafo(2 * numero_voos_B); int ultimaCidadeB = 0; 
        
        while((numero_voos_B != 0) and (equivalente)){ //construindo a matriz pra segunda aviacao
            cin >> origem >> destino;
            voeLivre->addAresta(origem, destino);
            
            int aux  = max(origem, destino);
            ultimaCidadeB = max(aux, ultimaCidadeB);
            
            if(ultimaCidadeB > ultimaCidadeA){
                equivalente = false;        
            } 
            //essa comparacao nos diz se existem mais cidades no catalogo de uma aviacao
            //do que no de outra, se sim eles claramente nao sao equivalentes, ja que existe
            //uma escala pra uma cidade, e nao existe uma escala pra essa mesma cidade no 
            //outro catalogo.
            
            numero_voos_B--;    
        }

        voeLivre->warshall(ultimaCidadeB);//fecho transitivo do catalogo da aviacao voeLivre

        if(ultimaCidadeB == ultimaCidadeA){ //ler comentario linha 100
            for(int i = 0; i <= ultimaCidadeA; i++){
                for(int j = 0; j <= ultimaCidadeB; j++){
                    int existeEmA = voeBem->existeEscala(i, j);
                    int existeEmB = voeLivre->existeEscala(i, j);

                    if( existeEmA != existeEmB){ //verifico se as mesmas cidades sao alcançaveis nos dois catalogos
                        equivalente = false;
                        break;
                    }
                }

                if(!equivalente) break;               
            }
        }

        cout << equivalente << endl;
        
        delete voeBem;
        delete voeLivre;
        
        casosTeste--;
    }

    return 0; 
}
