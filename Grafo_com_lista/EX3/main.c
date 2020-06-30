//Código da main da atividade 3 de grafos, que utiliza o TAD grafo com lista de adjacencia
//Feito por: Leonardo Fonseca Pinheiro
#include <stdio.h>
#include <stdlib.h>
#include "grafo_com_lista.h"

/* Funcao auxiliar que verifica se um vertice ja foi inserido no vetor.
 * Recebe como parametro o vetor, o indice do vertice e a quantidade de 
 * elementos no vetor. Tem retorno booleano. */

boolean verifica_vet(int* vet, int a, int qtd){
    for(int i = 0; i < qtd; i++){
        if(vet[i] == a){
            return true;
        }
    }
    return false;
}

/* Funcao que busca todos os vertices que nao tem dependencia, ou seja,
 * nao tem nada em sua lista de adjacencia. Recebe como parametro o grafo
 * g, a quantidade de vertices, um ponteiro para o inteiro quantidade e um
 * vetor onde armazena os vetores sem dependencia. Tem retorno void */

void busca_sem_depen(grafo* g, int v, int* qtd, int* vet){
    int a = *qtd;
    for(int i = 0; i < v; i++){
        if(verifica_adj(g, i) == false){
            if(verifica_vet(vet, i, a) == false){
                vet[a] = i; 
                a++; 
            }   
        }
    }
    *qtd = a;
    return;
}

int main(void){
    int v, a;//Numero de vertices e arestas
    scanf("%d %d", &v, &a);
    grafo* g = criar_grafo(v, true);
    int v1, v2; //Dois vértices
    for(int i = 0; i < a; i++){
        scanf("%d %d", &v1, &v2);
        insere_aresta(g, v2, v1); //Invertido para facilitar as dependencias
    }
    int* exec = malloc(v * sizeof(int)); //Vetor que armazena os vertices executados
    int qtd = 0; //Quantidade de execucoes
    int controle = 0; //Quantida de execucoes na passagem anterior
    int tempo = 1; 

    /* Verifica se existe algum ciclo no grafo antes de comecar
     * a producao. Caso exista, imprime -1 e encerra o programa */

    if(verifica_ciclo(g) == true){
        printf("-1");
        apaga_grafo(g);
        return 0;
    }

    /* Enquanto nao foram encerradas todas as dependencias, eh feita uma busca
     * por vertices sem dependencia, que pode ser executado. Depois, todos os
     * vertices que tem dependencia com o encontrado, tem essa dependencia removida,
     * por meio de uma funcao que remove todas as adjacencias de um vertice. */

    while(quantas_arestas(g) != 0){
        busca_sem_depen(g, v, &qtd, exec);
        tempo++;
        for(int i = controle; i < qtd; i++){
            remove_adj(g, exec[i]);
        }
        controle = qtd;
    }
    printf("%d", tempo);
    apaga_grafo(g);
    free(exec);
    return 0;
}
