//Código da main da atividade 1 de grafos, que utiliza o TAD grafo com lista de adjacencia
//Feito por: Leonardo Fonseca Pinheiro
#include <stdio.h>
#include <stdlib.h>
#include "grafo_com_lista.h"

void menu(){
    printf("***************MENU***************\n");
    printf("1 - Insere Aresta\n");
    printf("2 - Remove Aresta\n");
    printf("3 - Imprime grafo\n");
    printf("4 - Busca por largura\n");
    printf("0 - Sair\n");
}

int main(void){
    int v, a;//Numero de vertices e arestas
    scanf("%d %d", &v, &a);
    grafo* g = criar_grafo(v, true);
    int v1, v2; //Dois vértices
    for(int i = 0; i < a; i++){
        scanf("%d %d", &v1, &v2);
        insere_aresta(g, v2, v1);
    }
    int op;
    do{
        menu();
        scanf("%d", &op);
        switch(op){
            case 1:
                scanf("%d %d", &v1, &v2);
                insere_aresta(g, v2, v1);
                printf("Arresta inserida\n");
                break;
            case 2:
                scanf("%d %d", &v1, &v2);
                remove_aresta(g, v1, v2);
                break;
            case 3:
                imprime_grafo(g);
                break;
            case 4: 
                busca_largura(g);
                break;
            case 0:
                apaga_grafo(g);
        }
    }while(op != 0);
    apaga_grafo(g);
}
