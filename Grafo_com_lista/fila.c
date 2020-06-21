#include <stdio.h>
#include <stdlib.h>
#include "fila.h"


struct no_{
    int indice;
    NO* proximo;
};

struct fila_{
    NO* inicio;
    NO* fim;
    int tamanho;
};


FILA *fila_criar(void){
    FILA *fila = (FILA *) malloc(sizeof(FILA));
    if(fila != NULL){
        fila->inicio = NULL;
        fila->fim = NULL;
        fila->tamanho = 0;    
    }
    else{
        return NULL;
    }
    return (fila);
}

void fila_apagar(FILA **f){
    NO* aux;
    if ( ((*f) != NULL) && (!fila_vazia(*f)) ) {
        while ( (*f)->inicio != NULL) {
            aux = (*f)->inicio;
            (*f)->inicio = (*f)->inicio->proximo;
            free(aux); 
            aux = NULL;
        }
    }
    free(*f);
    *f = NULL;
    return;
}

boolean fila_inserir(FILA *fila, int ind){
    if (fila != NULL){
        NO* n = (NO*) malloc(sizeof(NO));
        if(n != NULL){
            n->indice = ind;
            n->proximo = NULL;
            if(fila->inicio == NULL){
                fila->inicio = n;
            }
            if(fila->fim != NULL){
                fila->fim->proximo = n;
            }
            fila->fim = n;
            fila->tamanho++;
            return TRUE;
        }
    }
    return FALSE;
}

int fila_remover(FILA *fila){
    if (fila != NULL && (!fila_vazia(fila)) ) {
        NO* nret = fila->inicio;
        int ret = fila->inicio->indice;
        fila->inicio = fila->inicio->proximo;
        nret->proximo = NULL;
        if(nret == fila->fim){
            fila->fim == NULL;
        }
        free(nret);
        nret = NULL;
        fila->tamanho --;
        return (ret);
    }
    return (e);
}

int fila_tamanho(FILA *fila){
    if (fila != NULL)
        return (fila->tamanho);
    return (e);
}

/*
boolean fila_cheia(FILA *fila){
    if(fila->tamanho > 10){
        return TRUE;
    }
    return FALSE;
}
*/

int fila_vazia(FILA *fila){
    return (fila->tamanho == 0);
}

void fila_imprimir(FILA* fila){
    NO* aux = fila->inicio;
    while(aux != NULL){
        printf("%d\n", aux->indice);
        aux = aux->proximo;
    }
    return;
}

int fila_ultimo(FILA* f){
    if(f->fim != NULL){
        return (f->fim->indice);
    }
    return e;
}

int fila_primeiro(FILA* f){
    if(f->inicio != NULL){
        return (f->inicio->indice);
    }
    return e;
}