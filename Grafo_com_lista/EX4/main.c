//Código da main da atividade 4 de grafos, que utiliza o TAD grafo com lista de adjacencia
//Feito por: Leonardo Fonseca Pinheiro
#include <stdio.h>
#include <stdlib.h>
#include "grafo_com_lista.h"

int main(void){
    int v, a;//Numero de vertices e arestas
    scanf("%d %d", &v, &a);
    grafo* g = criar_grafo(v, true);
    int v1, v2, dist, p; //Dois vértices
    for(int i = 0; i < a; i++){
        scanf("%d %d %d %d", &v1, &v2, &dist, &p);
        insere_aresta_com_peso(g, v1, v2, p, dist); 
    }

	scanf("%d %d", &v1, &v2);
	int* d = malloc(v * sizeof(int)); //Guarda as distancias
	int* ant = malloc(v * sizeof(int)); //Guarda os antecessores
	int aux = 0;
	int* caminho = malloc(v * sizeof(int)); //Guarda o caminho percorrido, de trás pra frente
	int valor = 0;  //Preco

	algoritmo_de_Bellman(g, v1, d, ant);

	caminho[0] = v2; //Fim da viagem
	while(caminho[aux] != v1){ //Enquanto nao chega no comeco
		aux++;
		caminho[aux] = ant[caminho[aux - 1]];
		valor += grafo_getPeso(g, caminho[aux], caminho[aux - 1]); //Soma o preco daquela aresta
	}

	for(int i = aux; i >= 0; i--){
		printf("%d ",caminho[i]);
	}
	printf("\n");
	printf("%d %d\n", d[v2], valor);

	apaga_grafo(g);
	free(d);
	free(ant);
	free(caminho);
	
	return 0;
}


