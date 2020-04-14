#ifndef GRAFO_COM_MATRIZ_H
    #define GRAFO_COM_MATRIZ_H
    #define boolean int
    #define true 1
    #define false 0
    typedef struct grafo_ grafo;
    grafo* criar_grafo(int a, int v);
    void apaga_grafo(grafo* g);
    void insere_aresta(grafo* g, int a1, int a2);
    void remove_aresta(grafo* g, int a1, int a2);
    boolean verfica_aresta(grafo* g, int a1, int a2);
    void imprime_grafo(grafo* g);
    boolean verifica_adj(grafo* g, int v);
    
    #endif