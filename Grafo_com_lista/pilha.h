#ifndef PILHA_H
    #define PILHA_H

    #define boolean int
    #define TRUE 1
    #define FALSE 0
    #define e 32000

    typedef struct pilha_ PILHA;
    typedef struct no_ NO;

    PILHA* pilha_criar(void); //função que cria a pilha
    void pilha_apagar(PILHA** pilha); //função que apaga a pilha da memória
    int pilha_vazia(PILHA* pilha); //função que retorna 1 caso a pilha esteja vazia e 0 caso não esteja
    int pilha_tamanho(PILHA* pilha); //função que retorna o tamanho da pilha
    int pilha_topo(PILHA* pilha); //função que retorna o primeiro item da pilha
    int pilha_empilhar(PILHA* pilha, int item); //função que insere um ITEM no começo da pilha
    int pilha_desempilhar(PILHA* pilha); //função que remove o primeiro ITEM da pilha
    void pilha_imprimir(PILHA* p); //função que imprime a pilha
    //boolean pilha_cheia(PILHA* p); //função que retona 1 se a pilha já atingiu sua capacidade máxima e 0 caso contrário
    NO* pilha_busca(PILHA* p, int chave); //função de busca que se baseia na letra do ITEM. caso encontrado, retorna o ITEM. caso contrário, retorna NULL

    #endif