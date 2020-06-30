//Implementacao de um TAD Lista
//Feito por: Leonardo Fonseca Pinheiro

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

struct item_{
    int indice;
    int peso;
    int dist;
    item* prox;
};

struct lista_ {
    item* ini;
    item* fim;
    int tamanho;
};


//Cria uma lista
//Nao tem parametros e Retorna a lista
LISTA* lista_criar(void){
    LISTA* l = malloc(sizeof(LISTA));
    if(l != NULL){
        l->ini = NULL;
        l->fim = NULL;
        l->tamanho = 0;
    }  
    return l;
}
//Apaga uma lista, recebida por parametro
//Retorno void
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

//Insere um elemento v, recebido por parametro, na lista l,
//que tambem e um parametro. Retorno void.
void inserir_lista(LISTA* l, int v){
    if(l == NULL){
        return;
    }
    item* aux = malloc(sizeof(item));
    aux->indice = v;
    aux->dist = 1;
    aux->peso = 1;
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

/* Insere um elemento v, com peso p e distancia d, recebidos por parametro, 
 * na lista l, que tambem e um parametro. Retorno void. */
void inserir_lista_com_peso(LISTA* l, int v, int p, int d){
    if(l == NULL){
        return;
    }
    item* aux = malloc(sizeof(item));
    aux->indice = v;
    aux->dist = d;
    aux->peso = p;
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

//Remove um elemento v, recebido por parametro, da lista l,
//que tambem e um parametro. Retorno void.
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
    l->tamanho--;
    return;
}

//Remove o primeiro elemento da lista l, recebida por parametro.
//Retorno void
void remover_primeiro_lista(LISTA* l){
    if(l == NULL){
        return;
    }
    l->ini = l->ini->prox;
    return;
}

//Busca um elemento v, recebido por parametro, na lista l,
//que tambem e um parametro. Retorno booleano.
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

//Imprime uma lista l, recebida por parametro. Retorno void.
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

//Funcao para passar o tamanho da lista
int lista_tamanho(LISTA* l){
    return l->tamanho;
}

//Retorna o indice do item na posicao P
int indice_lista(LISTA* l, int p){
    if(p > l->tamanho){
        return -1;
    }
    if(p == l->tamanho){
        return l->fim->indice;
    }
    item* aux = l->ini;
    for(int i = 0; i < p; i++){
        aux = aux->prox;
    }
    return aux->indice;
}

item* ponteiro_lista(LISTA*l, item* p){
    if(p == NULL){
        return l->ini;
    }
    else{
        return p->prox;
    }
}

int indice_item(item* i){
    return (i->indice);
}

//Retorna a distancia do item na posicao P
int lista_getDist(LISTA* l, int p){
    if(p > l->tamanho){
        return -1;
    }
    if(p == l->tamanho){
        return l->fim->indice;
    }
    item* aux = l->ini;
    for(int i = 0; i < p; i++){
        aux = aux->prox;
    }
    return aux->dist;
}

//Retorna o peso do item v
int lista_getPeso(LISTA* l, int v){
    if(l == NULL){
        return -1;
    }
    item* aux = l->ini;
    while(aux != NULL){
        if(aux->indice == v){
            break;
        }
        else{
            aux = aux->prox;
        }
    }
    if(aux != NULL){
        return aux->peso;
    }
    return -1;
}