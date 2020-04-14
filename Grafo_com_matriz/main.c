//Código da main da atividade 1 de grafos, que utiliza o TAD grafo com matriz de adjacencia
//Leonardo Fonseca Pinheiro
#include <stdio.h>
#include <stdlib.h>
#include "grafo_com_matriz.h"

int main(void){
    int v, a;//Numero de vertices e arestas
    scanf("%d %d", &v, &a);
    grafo* g = criar_grafo(a, v);
    int v1, v2; //Dois vértices
    for(int i = 0; i < a; i++){//Insere todas as arestas iniciais
        scanf("%d %d", &v1, &v2);
        insere_aresta(g, v1, v2);
    }
    int num_op, op; //Quantas operações serão feitas e o indice da operação
    scanf("%d", &num_op);
    for(int i = 0; i<num_op; i++){
        scanf("%d", &op);
        switch(op){
            case 1:
                scanf("%d %d", &v1, &v2);
                insere_aresta(g, v1, v2);
                break;
            case 2:
                scanf("%d %d", &v1, &v2);
                remove_aresta(g, v1, v2);
                break;
            case 3:
                imprime_grafo(g);
                break;
        }
    }


}
