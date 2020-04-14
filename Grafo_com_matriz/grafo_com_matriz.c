//Tad que define as operações de um grafo representado por uma matriz de adjacencia
//Leonardo Fonseca Pinheiro

#include <stdio.h>
#include <stdlib.h>
#include "grafo_com_matriz.h"

struct grafo_{
    int arestas;
    int vertices;
    int** mda; //Matriz De Adjacencia
};
//Função que cria um grafo, recebendo como parametros o número de arestas e o número de vértices
grafo* criar_grafo(int a, int v){
    grafo* g = malloc(sizeof(grafo));
    if(v == 0){
        return NULL;
    }
    g->arestas = a;
    g->vertices = v;
    int** aux = malloc(v * sizeof(int*));
    for(int i = 0; i<v; i++){
        aux[i] = malloc(v*sizeof(int));
    }
    g->mda = aux;
    return g;
}

//Função que apaga o grafo, recebendo-o como parametro e com retorno void
void apaga_grafo(grafo* g){
      for(int i = 0; i<g->vertices; i++){
        free(g->mda[i]);
    }
    free(g->mda);
    free(g);
    return;
}

//Função que insere uma aresta entre dois vertices, recebendo-os como parametro, junto com o grafo, e com retorno void
void insere_aresta(grafo* g, int a1, int a2){
    g->mda[a1][a2] = 1;
    g->mda[a2][a1] = 1;
    return;
}

//Função que retira uma aresta entre dois vertices, recebendo-os como parametro, junto com o grafo, e com retorno void
void remove_aresta(grafo* g, int a1, int a2){
    g->mda[a1][a2] = 0;
    g->mda[a2][a1] = 0;
    return;
}

//Função que verifica a existencia de uma aresta entre dois vertices, que recebe como parametro, junto com o grafo, e tem retorno booleano
boolean verfica_aresta(grafo* g, int a1, int a2){
    if(g->mda[a1][a2] == 1){
        return true;
    }
    else{
        return false;
    }
}

//Função que imprime o grafo, recebendo-o como parametro e com retorno void
void imprime_grafo(grafo* g){
    for(int i = 0; i<g->vertices; i++){
        for(int j = 0; j<g->vertices; j++){
            printf("%d ", g->mda[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    return;
}

//Função que verifica se o vertice recebido por parametro, junto com o grafo, tem alguma adjacencia e tem retorno booleano
boolean verifica_adj(grafo* g, int v){
    for(int i = 0; i<g->vertices; i++){
        if(g->mda[v][i] == 1){
            return true;
        }
    }
    return false;
}

