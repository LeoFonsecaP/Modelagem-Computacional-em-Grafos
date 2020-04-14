//Tad que define as operações de um grafo representado por uma lista de adjacencia
//Feito por: Leonardo Fonseca Pinheiro
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo_com_lista.h"

struct item_{
    int indice;
    item* prox;
};

struct lista_ {
    item* ini;
    item* fim;
    int tamanho;
};

struct grafo_{
    int arestas;
    int vertices;
    LISTA** l; //Vetor das listas de adjacencia
};

LISTA* lista_criar(void){
    LISTA* l = malloc(sizeof(LISTA));
    if(l != NULL){
        l->ini = NULL;
        l->fim = NULL;
        l->tamanho = 0;
    }
    
    return l;
}

void lista_apagar(LISTA **l){
    if (*l == NULL)
        return;
    item* aux = (*l)->ini;
    for(int i = 0; i < (*l)->tamanho; i++){
        if (aux != NULL){            
            item* aux1;
            aux1 = aux->prox;
            aux->prox = NULL;
            free(aux);
            aux = aux1;
        }
    }
    free(*l);
}

void inserir_lista(LISTA* l, int v){
    if(l == NULL){
        return;
    }
    item* aux = malloc(sizeof(item));
    aux->indice = v;
    aux->prox = NULL;
    if(l->ini == NULL){
        l->ini = aux;
    }
    if(l->fim != NULL){
        l->fim->prox = aux;
    }
    l->fim = aux;
    l->tamanho++;
    return;
}

void remover_lista(LISTA* l, int v){
    if(l == NULL){
        return;
    }
    if(l->ini->indice == v){
        l->ini = l->ini->prox;
    }
    item* p = l->ini;
    item* aux = NULL;
    while(p != NULL){
        if(p->indice == v){
            aux->prox = p->prox;
            break;
        }
        else{
            aux = p;
            p = p->prox;
        }
    }
    if(p == l->fim){
        l->fim = aux;
    }
    return;
}
boolean lista_busca(LISTA* l, int v){
    if(l == NULL){
        return false;
    }
    item* aux = l->ini;
    while(aux != NULL){
        if(aux->indice == v){
            return true;
        }
        else{
            aux = aux->prox;
        }
    }
    return false;
}

void lista_imprimir(LISTA* l){
    if(l != NULL){
        if(l->tamanho == 0){
            return;
        }
        else{
            item* p = l->ini;
            while(p != NULL){
                printf("%d ", p->indice);
                p = p->prox;
            }
        }
    }
    return;
}

//Função que cria um grafo, recebendo como parametros o número de arestas e o número de vértices
grafo* criar_grafo(int v){
    if(v == 0){
        return NULL;
    }
    grafo* g = malloc(sizeof(grafo));
    if(g != NULL){
        g->arestas = 0;
        g->vertices = v;
        g->l = malloc(v* sizeof(LISTA*));
        for(int i = 0; i<v; i++){
            g->l[i] = lista_criar();
        }
    }
    return g;
}

//Função que apaga o grafo, recebendo-o como parâmetro e com retorno void
void apaga_grafo(grafo* g){
      for(int i = 0; i<g->vertices; i++){
        lista_apagar(&g->l[i]);
    }
    free(g);
    return;
}

//Função que insere uma aresta entre dois vertices, recebendo-os como parâmetro, junto com o grafo, e com retorno void
void insere_aresta(grafo* g, int a1, int a2){
    if(verfica_aresta(g, a1,a2) == false){
        inserir_lista(g->l[a1], a2);
        inserir_lista(g->l[a2], a1);
        g->arestas++;
    }
    return;
}

//Função que retira uma aresta entre dois vertices, recebendo-os como parâmetro, junto com o grafo, e com retorno void
void remove_aresta(grafo* g, int a1, int a2){
    remover_lista(g->l[a1], a2);
    remover_lista(g->l[a2], a1);
    g->arestas--;
    return;
}

//Função que verifica a existencia de uma aresta entre dois vertices, que recebe como parâmetro, junto com o grafo, e tem retorno booleano
boolean verfica_aresta(grafo* g, int a1, int a2){
    return lista_busca(g->l[a1], a2);
}

//Função que imprime o grafo, recebendo-o como parâmetro e com retorno void
void imprime_grafo(grafo* g){
    int tam = g->vertices;
    for(int i = 0; i<tam; i++){
        printf("%d: ", i);
        lista_imprimir(g->l[i]);
        printf("\n");
    }
    printf("\n");
    return;
}

//Função que verifica se o vertice recebido por parâmetro, junto com o grafo, tem alguma adjacencia e tem retorno booleano
boolean verifica_adj(grafo* g, int v){
    if(g->l[v]->tamanho != 0){
        return true;
    }
    else{
        return false;
    }
}
//Função auxiliar da função augoritmo de Fleury, verfica se existe algum vértice com grau ímpar. Recebe o grafo por parâmetro e tem retorno booleano
boolean verfica_vertice(grafo* g){
    for(int i = 0; i<g->vertices; i++){
        if(g->l[i]->tamanho%2 != 0){//verifica se o tamanho da lista de adjacencia de um vértice é diferente de 0
            return false;
        }
    }
    return true;
}

//Função recursiva auxiliar da função augoritmo de Fleury, recebe o grafo, o vetor caminho, vértice atual e quantos vértices ja estão no caminho como parâmetro. Tem retorno void
void acha_caminho(grafo* g, int* caminho, int v, int posicao){
    if(g->arestas == 0){
        return;
    }
    item* p = g->l[v]->ini;
    while (p != NULL){
        if(verifica_ponte(g, p->indice) == false){
            break;
        }
        else{
            p = p->prox;
        }
    }
    if(p == NULL){
        remove_aresta(g, v, g->l[v]->ini->indice);
        caminho[posicao] = g->l[v]->ini->indice;
        posicao++
        acha_caminho(g, caminho, g->l[v]->ini->indice, posicao);
    }
    else{
        remove_aresta(g, v, p->indice);
        caminho[posicao] = p->indice;
        posicao++;
        acha_caminho(g, caminho, p->indice, posicao);
    }
}
//Função que analisa o grafo, recebido por parâmetro e retorna um vetor com o caminho euclidiano
int* algoritmo_de_Fleury(grafo* g){
    if(verfica_vertice == true){
        return NULL;
    }
    else{
        grafo* aux = g;
        int* caminho = malloc((g->arestas+1)*sizeof(int));
        int posicao = 0;
        caminho[posicao] = 0;
        posicao++;
        acha_caminho(aux, caminho, 0, posicao);
    }
    return caminho;
}

