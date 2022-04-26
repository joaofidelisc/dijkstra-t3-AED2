// TRABALHO 3 DE ALGORITMOS E ESTRUTURAS DE DADOS 2
//Informacoes do estudante
// Nome: Joao Vitor Fidelis Cardozo
// RA: 769719

//CRUSH

/*O trabalho, foi realizado utilizando matriz de adjacência. */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct grafo *Grafo;

struct grafo{
    int **A;
    int n; //numero de vertices
    int m; //numero de arestas
};

Grafo inicializaGrafo (int n);
void insereArcoGrafo(Grafo G, int v, int w);
Grafo liberaGrafo (Grafo G);
int **inicializaMatrizPesos (int **mpesos, int n);
int **liberaMatrizPesos(int **mpesos, int n);
int dijkstra(Grafo G, int n, int origem, int **mpesos);

/*A função abaixo é responsável por inicializar o grafo. */
Grafo inicializaGrafo(int n){
    int i, j;
    Grafo G = malloc(sizeof*G);
    G->n = n;
    G->m = 0;
    G->A = malloc(n * sizeof(int *)); //Alocando um vetor com n posições de apontadores
    for (i=0; i<n; i++)
        G->A[i] = malloc(n * sizeof(int)); //Aloca um vetor para cada posição
    for (i=0; i<n; i++)
        for (j=0; j<n; j++)
            G->A[i][j] = 0; //Preenche com 0 todos os elementos da matriz de adjacência
    return G;
}

/*Insere arco v-w no grafo G, supondo que v e w são inteiros distintos
entre 0 e n-1. Se o grafo já tem arco v-w, não faz nada. */

void insereArcoGrafo(Grafo G, int origem, int destino){
    if (G->A[origem][destino] == 0){
        G->A[origem][destino] = 1;
        G->m++;
    }
}

/*A função abaixo, cria uma matriz de pesos, inicializa todos os valores para 9999 (valor admitido como infinito) e devolve o endereço da mesma.*/
int **inicializaMatrizPesos (int **mpesos, int n){
    int i=0, j=0;
    mpesos = calloc(n, sizeof(int*)); //Aloca um vetor de apontadores;

    for (i=0; i<n; i++){
        mpesos[i] = calloc(n, sizeof(int)); //Aloca um vetor para cada posição;
    }
    
    for (i=0; i<n; i++){
        for (j=0; j<n; j++){
            mpesos[i][j] = 9999; //Inicializa com um valor "infinito" (9999);
        }
    }
    return mpesos;
}

/*A função abaixo libera a memória alocada para o grafo G e devolve NULL*/
Grafo liberaGrafo (Grafo G){
    int i;
    for (i=0; i<G->n; i++){
        free(G->A[i]);
        G->A[i] = NULL;
    }
    free(G->A);
    G->A = NULL;
    free(G);
    return NULL;
}

/*A função abaixo libera a memória alocada para a matriz de pesos e devolve NULL*/
int **liberaMatrizPesos(int **mpesos, int n){
    int i;
    for (i=0; i<n; i++){
        free(mpesos[i]);
        mpesos[i] = NULL;
    }
    free(mpesos);
    mpesos = NULL;
    return NULL;
}

/*A função abaixo, é responsável por retornar o peso do menor caminho da origem (vértice 0), até o destino (vértice v-1).*/
int dijkstra(Grafo G, int n, int origem, int **mpesos){
    int contador, dist_min, prox_no, i, j;
	
    int **custo = calloc(n, sizeof(int*)); //Aloca um vetor de apontadores;
    
    for (i=0; i<n; i++){
        custo[i] = calloc(n, sizeof(int)); //Aloca um vetor para cada posição;
    }
    int *distancia = malloc(n * sizeof(int));
    int *pred = malloc(n * sizeof(int)); //Armazena o predecessor de cada nó;
    int *visitado = malloc(n * sizeof(int));

    //Contador fornece o número de nós vistos até o momento;
    //Cria a matriz de custo;
    //Se nao houver caminho de i para j, a matriz de custo na posicao ij (custo[i][j]), eh preenchida com um valor "infinito" 9999;
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			if(G->A[i][j] == 0) //Se G->A[i][j] = 0, implica em não haver caminho (aresta) de i para j;
				custo[i][j]= 9999;
            else
                custo[i][j] = mpesos[i][j];

	//Inicializa valores;
	for(i=0;i<n;i++)
	{
		distancia[i]=custo[origem][i];
		pred[i]=origem;
		visitado[i]=0;
	}
	
	distancia[origem]=0;
	visitado[origem]=1;
	contador=1;
	
	while(contador< n){
		dist_min=9999;
		for(i=0;i<n;i++)
			if(distancia[i]<dist_min&&!visitado[i])
			{
				dist_min=distancia[i];
				prox_no=i;
			}
            //Verifica se existe um caminho melhor através do próximo nó;			
			visitado[prox_no]=1;
			for(i=0;i<n;i++)
				if(!visitado[i])
					if(dist_min+custo[prox_no][i]<distancia[i])
					{
						distancia[i]=dist_min+custo[prox_no][i];
						pred[i]=prox_no;
					}
		contador++;
	}
    return distancia[n-1];
}

int main (){

    Grafo G = NULL;
    int **mpesos = NULL;
    int n = 0, e = 0; //numero de vertices e numero de arestas;
    int a = 0, v = 0, w = 0; //origem, destino e peso;
    scanf("%d %d", &n, &e); //Lê número de vértices e número de arestas;
    
    G = inicializaGrafo(n); //Inicializa grafo;
    mpesos = inicializaMatrizPesos(mpesos, n); //Inicializa matriz de pesos;
    
    for (int i=0; i<e; i++){
        scanf("%d %d %d", &a, &v, &w); //(origem, destino, peso);
        insereArcoGrafo(G, a, v);
        if (w < mpesos[a][v]) mpesos[a][v] = w; //Teste se o peso que eu vou inserir para um caminho x, eh menor do que o peso ja inserido;
    }

    printf("%d\n", dijkstra(G, n, 0, mpesos));

    //Libera memoria utilizada para o grafo e para a matriz de pesos
    liberaGrafo(G);
    liberaMatrizPesos(mpesos, n);
    

    return 0;
}