//Tad que define as operações de uma fila
//Feito por: Leonardo Fonseca Pinheiro
#ifndef FILA_H
    #define FILA_H
    #define e 32000
    #define TRUE 1
    #define FALSE 0
    #define boolean int

    typedef struct fila_ FILA;
    typedef struct no_ NO;

    FILA *fila_criar(void); //função que cria a fila
    void fila_apagar(FILA **f); //função que apaga a fila da memória
    boolean fila_inserir(FILA *fila, int indice); //função que insere um item no fim da fila
    int fila_remover(FILA *fila); //função que remove o primeiro item da fila
    int fila_tamanho(FILA *fila); //função que retorna o tamanho da fila
    int fila_vazia(FILA *fila); //função que retorna 1 caso a fila esteja vazia e 0 caso não esteja
    //boolean fila_cheia(FILA *fila); //função que retona 1 se a fila já atingiu sua capacidade máxima e 0 caso contrário
    void fila_imprimir(FILA* fila); //função que imprime a fila
    int fila_ultimo(FILA *f); //função que retorna o último item da fila
    int fila_primeiro(FILA *f);  //função que retorna o primeiro item da fila
    int fila_busca(FILA *fila, int chave); //função de busca que se baseia na placa do item. caso encontrado, retorna o item. caso contrário, retorna NULL

    #endif