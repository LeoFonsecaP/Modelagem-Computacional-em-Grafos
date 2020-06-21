//Tad que define as operações de um grafo representado por uma lista de adjacencia
//Feito por: Leonardo Fonseca Pinheiro
#ifndef GRAFO_COM_LISTA_H
    #define GRAFO_COM_LISTA_H
    #define TAM_MAX 100
    #define true 1
    #define false 0
    #define boolean int
    #define branco 1
    #define incolor 0
    #define cinza 2
    #define preto 3
    #define e 32000
    #define sucesso 0

    typedef struct item_ item;
    typedef struct lista_ LISTA;
    typedef struct grafo_ grafo;


    grafo* criar_grafo(int v, boolean dir); //Cria o grafo
    void insere_aresta(grafo* g, int a1, int a2); //Insere uma aresta
    void remove_aresta(grafo* g, int a1, int a2); //Remove uma aresta
    void apaga_grafo(grafo* g); //Apaga o grafo
    boolean verifica_aresta(grafo* g, int a1, int a2); //verifica a existencia de uma aresta entre dois vertices
    void imprime_grafo(grafo* g); //Imprime as listas de adjacencia
    boolean verifica_adj(grafo* g, int v); //Verifica se o vértice tem alguma adjacencia
    int caminho_euleriano(grafo *g, int *vertices, int *numvertices); //Identifica um caminho euleriano
    void coloracao(grafo*g);//Colore o grafo
    void busca_largura(grafo *g); //Faz a busca em largura em g
    void busca_profundidade(grafo* g); //Faz a busca em profundidade em g
    int quantas_arestas(grafo* g); //Retorna a quantidade de arestas do grafo
    void remove_adj(grafo* g, int v); //Remove todas as arestas de v
    int* ordenacao_topologica(grafo* g); //Faz a ordenacao topologica do grafo g
    boolean verifica_ciclo(grafo* g); //Verifica se o grafo possui um ciclo
    #endif

