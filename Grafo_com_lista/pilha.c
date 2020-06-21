#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"


struct pilha_{
    NO* topo;
    int tamanho;
};

struct no_ {
    int indice;
    NO *anterior;
};

PILHA* pilha_criar(void){
    PILHA* pilha = (PILHA *) malloc(sizeof (PILHA));
    if (pilha != NULL) {
        pilha->topo = NULL;
        pilha->tamanho = 0;
    }
    return (pilha);
}
int pilha_empilhar(PILHA* pilha, int item){
    NO* pnovo = (NO *) malloc(sizeof (NO));
    if (pnovo != NULL) {
        pnovo->item = item;
        pnovo->anterior = pilha->topo;
        pilha->topo = pnovo;
        pilha->tamanho++;
        return (1);
    }
    return (e);
}
void pilha_apagar(PILHA** pilha){
    NO* paux;
    if ( ((*pilha) != NULL) && (!pilha_vazia(*pilha)) ) {
        while ( (*pilha)->topo != NULL) {
            paux = (*pilha)->topo;
            (*pilha)->topo = (*pilha)->topo->anterior;
            item_apagar(&paux->item);
            //paux->anterior = NULL;
            //free(paux); 
            paux = NULL;
        }
    }
    free(*pilha);
    *pilha = NULL;
    return;
}
    
boolean pilha_vazia(PILHA* pilha){
    if(pilha != NULL){
        if(pilha->tamanho == 0){
            return TRUE;
        }
    }
    return FALSE;

}

int pilha_tamanho(PILHA* pilha){
    if(pilha != NULL){
        return pilha->tamanho;
    }
}

int pilha_topo(PILHA* pilha){
    if ((pilha != NULL) && (pilha_vazia(pilha) == 0) ){
        return (pilha->topo->indice);
    }
    return (NULL);
}

int pilha_desempilhar(PILHA* pilha){
    if ((pilha != NULL)){
        if(pilha->topo != NULL){
            NO* pno = pilha->topo;
            int item = pilha->topo->indice;
            pilha->topo = pilha->topo->anterior;
            pno->anterior=NULL;
            pilha->tamanho--;
            return (item);
        }
    }
    return (NULL);
}

void pilha_imprimir(PILHA* p){
    NO* aux = malloc(sizeof(NO));
    aux = p->topo;
    if(p->topo == NULL){
        return;
    }
    while(aux != NULL){
        printf("%d\n", aux->indice);
        aux = aux->anterior;
    }
    printf("\n");
    return;
}

/*
boolean pilha_cheia(PILHA* p){
    if(p->tamanho >= 5){
        return TRUE;
    }
    return FALSE;
}
*/

NO* pilha_busca(PILHA* p, int chave){
    NO* aux = p->topo;
    while(aux != NULL){
        if(aux->indice == chave){
            return aux;
        }
        else{
            aux = aux->anterior;
        }
    }
    return NULL;
}