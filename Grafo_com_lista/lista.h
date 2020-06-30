//Tad que define as operações de uma lista
//Feito por: Leonardo Fonseca Pinheiro
#ifndef LISTA_H
    #define LISTA_H
    #define TAM_MAX 100
    #define true 1
    #define false 0
    #define boolean int

	typedef struct item_ item;
    typedef struct lista_ LISTA;

	LISTA* lista_criar(void);  //alocação de memória
    void inserir_lista(LISTA* l, int v); //inserção
    void inserir_lista_com_peso(LISTA* l, int v, int p, int d); //Insere com peso
    void remover_lista(LISTA* l, int v); //Remocao
    void remover_primeiro_lista(LISTA* l); //Remove o primeiro item da lista
    boolean lista_busca(LISTA* l, int v); //Busca
    void lista_imprimir(LISTA* l); //imprime toda a lista
    void lista_apagar(LISTA **l);  //apaga a lista da memória
    int lista_tamanho(LISTA* l); //descobrir o tamanho da lista
    int indice_lista(LISTA* l, int p); //Retorna o indice do item na posicao P
    item* ponteiro_lista(LISTA*l, item* p); //Retorna um ponteiro para o item seguinte a p
    int indice_item(item* i); //Retorna o indice de um item i
    int lista_getDist(LISTA* l, int p); //Retorna o peso do item na posicao P
    int lista_getPeso(LISTA* l, int v); //Retorna o peso do item v
	#endif