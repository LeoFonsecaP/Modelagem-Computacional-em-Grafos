//Tad que define as operações de um grafo representado por uma lista de adjacencia
//Feito por: Leonardo Fonseca Pinheiro
#ifndef GRAFO_COM_LISTA_H
    #define GRAFO_COM_LISTA_H
    #define TAM_MAX 100
    #define true 1
    #define false 0
    #define boolean int

    typedef struct item_ item;
    typedef struct lista_ LISTA;
    typedef struct grafo_ grafo;


    LISTA* lista_criar(void);  //alocação de memória
    grafo* criar_grafo(int v); //Cria o grafo
    void inserir_lista(LISTA* l, int v); //inserção do vertice
    void remover_lista(LISTA* l, int v); //remove vertice
    boolean lista_busca(LISTA* l, int v); //Busca uma aresta
    void lista_imprimir(LISTA* l); //imprime toda a lista
    void lista_apagar(LISTA **l);  //apagar a lista da memória
    void insere_aresta(grafo* g, int a1, int a2); //Insere uma aresta
    void remove_aresta(grafo* g, int a1, int a2); //Remove uma aresta
    void apaga_grafo(grafo* g); //Apaga o grafo
    boolean verfica_aresta(grafo* g, int a1, int a2); //verifica a existencia de uma aresta entre dois vertices
    void imprime_grafo(grafo* g); //Imprime as listas de adjacencia
    boolean verifica_adj(grafo* g, int v); //Verifica se o vértice tem alguma adjacencia
    #endif

