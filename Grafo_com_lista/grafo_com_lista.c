//Tad que define as operações de um grafo representado por uma lista de adjacencia
//Feito por: Leonardo Fonseca Pinheiro
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "fila.h"
#include "grafo_com_lista.h"

struct lista_ {
    item* ini;
    item* fim;
    int tamanho;
};

struct grafo_{
    int arestas;
    int vertices;
    int* cor;
    boolean direcionado;
    LISTA** l; //Vetor das listas de adjacencia
};

//Função que cria um grafo, recebendo como parametros o número de arestas e o número de vértices
grafo* criar_grafo(int v, boolean d){
    if(v == 0){
        return NULL;
    }
    grafo* g = malloc(sizeof(grafo));
    if(g != NULL){
        g->arestas = 0;
        g->vertices = v;
        g->direcionado = d;
        g->cor = malloc(v * sizeof(int));
        g->l = malloc(v * sizeof(LISTA*));
        for(int i = 0; i<v; i++){
            g->l[i] = lista_criar();
            g->cor[i] = incolor;
        }
    }
    return g;
}

//Função que apaga o grafo, recebendo-o como parâmetro e com retorno void
void apaga_grafo(grafo* g){
    for(int i = 0; i<g->vertices; i++){
        lista_apagar(&g->l[i]);
    }
    free(g->l);
    free(g->cor);
    free(g);
    return;
}

//Função que insere uma aresta entre dois vertices, recebendo-os como parâmetro, junto com o grafo, e com retorno void
void insere_aresta(grafo* g, int a1, int a2){
    if(verifica_aresta(g, a1,a2) == false){
        inserir_lista(g->l[a1], a2);
        if(g->direcionado == false){
            inserir_lista(g->l[a2], a1);
        }
        g->arestas++;
    }
    return;
}

/* Função que insere uma aresta entre dois vertices, com peso, recebendo-os como parâmetro,
 * junto com o grafo e com o peso. Tem retorno void */
void insere_aresta_com_peso(grafo* g, int a1, int a2, int p, int d){
    if(verifica_aresta(g, a1,a2) == false){
        inserir_lista_com_peso(g->l[a1], a2, p, d);
        if(g->direcionado == false){
            inserir_lista_com_peso(g->l[a2], a1, p, d);
        }
        g->arestas++;
    }
    return;
}

//Função que retira uma aresta entre dois vertices, recebendo-os como parâmetro, junto com o grafo, e com retorno void
void remove_aresta(grafo* g, int a1, int a2){
    remover_lista(g->l[a1], a2);
    if(g->direcionado == false){
        remover_lista(g->l[a2], a1);
    }
    g->arestas--;
    return;
}

//Função que verifica a existencia de uma aresta entre dois vertices, que recebe como parâmetro, junto com o grafo, e tem retorno booleano
boolean verifica_aresta(grafo* g, int a1, int a2){
    return lista_busca(g->l[a1], a2);
}

//Funcao que retorna a quantidade de arestas do grafico
int quantas_arestas(grafo* g){
    return g->arestas;
}

//Funcao que remove todas as adjacencias com um vertice
void remove_adj(grafo* g, int v){
    for(int i = 0; i < g->vertices; i++){
        if(verifica_aresta(g, i, v) == true){
            remove_aresta(g, i, v);
        }
    }
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

/* Funcao para retornar o peso de uma aresta em um grafo g, 
 * entre v1 e v2, que sao recebidos por parametros.
 * Retorna o peso. */

int grafo_getPeso(grafo* g, int v1, int v2){
    return lista_getPeso(g->l[v1], v2);
}

//Funcao auxiliar a funcao algoritmo de fleury
//Recebe o grafico como parametro
//Tem como retorno o primeiro vertice de um caminho valido. Se nao houver, retorna -1
int acha_caminho(grafo* g){
    int vertices_impares = 0;
	int primeiro_vertice = -1;
    int tamanho;

	/* Verifica se a quantidade de vertices impares e 0 ou 2 */
	for (int i = 0; i < g->vertices; i++) {
		if (vertices_impares >= 3){ 
			break;
        }
        tamanho = lista_tamanho(g->l[i]);
		if (tamanho % 2 != 0) {
			vertices_impares++;
			primeiro_vertice = i;
        } 
        else if ((primeiro_vertice == -1) && (lista_tamanho != 0)) {
            primeiro_vertice = i;
        }
	}
	if (primeiro_vertice == -1) {
		primeiro_vertice = 0;
	}
	if ((vertices_impares != 0) && (vertices_impares != 2)){
        primeiro_vertice = -1;
    }
	return primeiro_vertice; 
}

/* Passa por todos os vertices de um grafo e marca-os como visitados */
void marca_vertices(grafo *g, int v, boolean *visitado){
	int *aux; 	/* Armazena, temporariamente, o indice dos vertices */
	if (lista_tamanho(g->l[v]) == 0){
		return;
    }
	visitado[v] = true;
	for (int i = 0; i < lista_tamanho(g->l[v]); i++) {
		aux[i] = indice_lista(g->l[i], i);
		if (!visitado[*aux]) {
			marca_vertices(g, *aux, visitado);
		}
	}
	return;
}

/* Verifica se um grafico g esta conectado partindo de v */
boolean verifica_conexao(grafo *g, int v){
	boolean *visitado;
	visitado = (boolean *)calloc(g->vertices, sizeof(boolean));
	marca_vertices(g, v, visitado);
	for (int i = 0; i < g->vertices; i++) {
		if (!visitado[i] && (lista_tamanho(g->l[i]) != 0)) {
			free(visitado);
			return false;
		}
	}
	free(visitado);
	return true;
}

/* Verifica se uma aresta entre dois vertices é ponte de um grafo g */
boolean verifica_ponte(grafo *g, int v1, int v2){
	boolean resultado;
    remove_aresta(g, v1, v2);
	resultado = !verifica_conexao(g, v2);
    insere_aresta(g, v1, v2);
	return resultado;
}

/* Retorna um vertice que e adjacente a v e nao passa por uma
 * ponte. Se nao for possivel, retorna -1 */
int vertice_nao_ponte(grafo *g, int v){
	int aux;

	for (int i = 0; i < lista_tamanho(g->l[v]); i++) {
		/* Na funcao verifica ponte, a aresta e removida e adicionada
		 * entao sempre verificamos o primeiro elemento, na posicao 0 */
		aux = indice_lista(g->l[v], 0);
		if (!verifica_ponte(g, v, aux)) {
			return aux;
		}
	}
	return -1;
}

/* Executa o algoritmo de Fleury pra achar caminhos eulerianos */
int Algoritmo_de_Fleury(grafo *g, int v, LISTA *arestas){
	int *aux;
	if (lista_tamanho(g->l[v])) {
		return 0;
	}
    int y;
	if (lista_tamanho(g->l[v]) == 1) {
		*aux = indice_lista(g->l[v], 0);
		y = *aux;
	} 
    else {
		y = vertice_nao_ponte(g, v);
		if (y == -1) {
			return e;
		}
	}
    inserir_lista(arestas, y);
	remove_aresta(g, v, y);
	return Algoritmo_de_Fleury(g, y, arestas);
}

/* Funcao para restaurar as arestas do grafo que foram removidas no algoritmo */
void restaura_grafo(grafo *g, LISTA *arestas) {
	int x;
    int y;
	for (int i = 0; i < lista_tamanho(arestas); i++) {
		x = indice_lista(arestas, i);
        y = indice_lista(arestas, i+1);
		insere_aresta(g, x, y);
	}
	return;
}

/* Funcao para achar um caminho euleriano no grafo.
 * Recebe por parametro um grafo g, um vetor de vertices
 * e o endereco de um inteiro com o numero de vertices do caminho.
 * Retorna erro ou sucesso. */
int caminho_euleriano(grafo *g, int *vertices, int *numvertices){
	LISTA *arestas;
	int v;
	v = acha_caminho(g);
	if ((v == -1) || 
	    !verifica_conexao(g, v)) {
		return e;
	}
	arestas = lista_criar();
	Algoritmo_de_Fleury(g, v, arestas);
	restaura_grafo(g, arestas);
	if (lista_tamanho(arestas) == 0) {
		*numvertices = 0;
		return sucesso;
	}
	*numvertices = lista_tamanho(arestas) + 1;
	vertices[0] = v;
	for (int i = 1; lista_tamanho(arestas) != 0; i++) {
        vertices[i] = indice_lista(arestas,0);
		remover_primeiro_lista(arestas);
	}
	lista_apagar(&arestas);
	return sucesso;
}


/* Função auxiliar à função coloração. Recebe um grafo por parâmetro e retorna
 * um vetor com os índices ordenados de forma decrescente de acordo com o grau */
int* grau_ordenado(grafo* g){
    int* grau = malloc(g->vertices* sizeof(int));
    int aux;
    for(int i = 0; i<g->vertices; i++){
        grau[i] = i;
    }
    for(int i = 0; i<g->vertices; i++){
        for(int j = i+1; j<g->vertices; j++){
            if(g->l[j]->tamanho > g->l[i]->tamanho){
                aux = i;
                i = j;
                j = i;
            }
        }
    }
    return grau;
}

//Funcao para deixar o grafo inteiro incolor
void pinta_grafo(grafo* g, int cor){
    for(int i = 0; i < g->vertices; i++){
        g->cor[i] = cor;
    }
}

//Função que colore o grafo recebido por parâmetro de modo que vértices adjacentes tenham cores diferentes
void coloracao(grafo*g){
    pinta_grafo(g, incolor); //Caso a busca em largura tenha sido utilizada
    int* ordenado = grau_ordenado(g);
    int i = 0; //índice do vetor
    int colorido = 0; //Conta quantos vértices ja foram coloridos para condição de parada
    int aux = 0; //Usado para análise de adjacentes
    int c = 0; //índice da cor
    while(colorido < g->vertices){
        if(g->cor[ordenado[i]] == incolor){ //Verifica se aquele vértice ja foi colorido
            g->cor[ordenado[i]] = c;
            colorido++;
            for(int j = i + 1; j<g->vertices; j++){
                //Verifica se o vértice ja foi colorido ou tem adjacencia ao vértice que foi colorido inicialmente
                if(g->cor[ordenado[j]] == -1 && verifica_aresta(g, i, j) == false){
                    for(int k = i+1; k<j; k++){
                        //Verifica se algum vértice daquela cor tem adjacencia com o vértice que queremos colorir
                        if(g->cor[k] == c && verifica_aresta(g, j, k)){
                            aux = 1;
                            break;
                        }
                    }
                    if(aux == 0){
                        g->cor[ordenado[i]] == c;
                        colorido++;
                    }
                }
            }
            aux = 0;
            c++;
        }
        i++;
    }
}

/* Funcao auxiliar a busca por largura. Recebe o grafo, uma variavel para controle de erro e
 * um vertice por parametro. Retorna um ponteiro para o primeiro item da lista de adjacencia */
item* PrimeiroListaAdj(grafo *G, int V, int *erro) {
    if (V>G->vertices) {
       *erro=1;
       return(NULL);
    }
    else {
         *erro=0;
         return(ponteiro_lista(G->l[V], NULL));
    }
}

/* Retorna o item seguinte ao item atual. Recebe o grafo, o item atual, o local do proximo
 * item, uma variavel de controle para o fim da lista e uma para erro. Tem retorno void */
void ProxAdj(grafo *G, item **Adj, item **Prox, int *FimListaAdj, int *erro) {
     *erro=0;
     *Adj=*Prox;
     int v = indice_item(*Adj);
     *Prox = ponteiro_lista(G->l[v], *Adj);
     if (*Prox==NULL)
        *FimListaAdj=1;
}

/* Funcao que efetivamente faz a busca em largura. Recebe por parametro
 * o grafo g, o vertice inicial v, o vetor de distancias, cores e antecessores.
 * Tem retorno void. */
void visita_bfs(grafo *G, int V, int distancia[], int cor[], int antecessor[]) {
     int FimListaAdj, erro;
     item *Adj, *Aux;
     int indice;
     FILA* F = fila_criar();
     cor[V] = cinza;
     distancia[V] = 0;
     erro = fila_inserir(F, V);
     if(erro = false){
         return;
     }
     printf("No %d, distancia=%d, antecessor=%d\n",V,distancia[V],antecessor[V]);

     while (!fila_vazia(F)) {
           V = fila_remover(F);
           if (lista_tamanho(G->l[V]) != 0) {
              Aux = PrimeiroListaAdj(G,V,&erro);
              FimListaAdj = 0;
              while (!FimListaAdj) {
                    ProxAdj(G,&Adj,&Aux,&FimListaAdj,&erro);
                    indice = indice_item(Adj);
                    if (cor[indice]==branco) {
                        cor[indice]=cinza;
                        distancia[indice]=distancia[V]+1;
                        antecessor[indice]=V;
                        erro = fila_inserir(F, indice);
                        if(erro = false){
                            return;
                        }
                        printf("No %d, distancia=%d, antecessor=%d\n",indice,distancia[indice],antecessor[indice]);
                    }
              }
           }
           cor[V]=preto;
     }
}

/*Funcao que faz a busca em largura em um grafo g
 * recebido por parametro. Tem retorno void */
void busca_largura(grafo *g) {
     int v, distancia[g->vertices], antecessor[g->vertices]; 
     printf("*** Sequencia de nos visitados na busca em largura ***\n\n");
     pinta_grafo(g, branco);
     for (v=0; v < g->vertices ; v++) {
         distancia[v]=-1;
         antecessor[v]=-1;
     }
     for (v=0; v < g->vertices ; v++) {
         if (g->cor[v]==branco){
               visita_bfs(g,v,distancia,g->cor,antecessor);
         }
     }
}

/* Funcao que efetivamente faz a busca em profundidade. Recebe por parametro
 * o grafo g, o vertice inicial v, o endereco do tempo, o vetor de distancias,
 * cores e antecessores. Alem disso, recebe um ponteiro para o inteiro ciclo,
 * que recebe true se um ciclo eh detectado, um vetor de inteiro que ordena
 * topologicamente o grafo e um ponteiro para quantidade de elementos
 * desse vetor. Tem retorno void. 
 * Essa funcao eh utilizada para fazer a busca de profundidade, para fazer a 
 * ordenacao topologica e para verificar um ciclo. Em cada uma dessas funcoes,
 * sao utilizados apenas alguns dos parametros passados, o resto eh ignorado e,
 * se alocados dinamicamente, sao liberados da memoria.*/

void visita_dfs(grafo* g, int v, int* tempo, int* d, int* t, int* cor, 
                int* ant, int* ciclo, int* vet, int* qtd){

    int FimListaAdj, erro, indice;
    item *Adj, *Aux;

    cor[v] = cinza;
    (*tempo)++;
    d[v] = *tempo;
    
    if(lista_tamanho(g->l[v]) != 0){
        Aux = PrimeiroListaAdj(g,v,&erro);
        FimListaAdj = 0;
        while (!FimListaAdj) {
            ProxAdj(g,&Adj,&Aux,&FimListaAdj,&erro);
            indice = indice_item(Adj);
            if (cor[indice]==branco) {
                ant[indice]=v;
                visita_dfs(g, indice, tempo, d, t, g->cor, ant, ciclo, vet, qtd);
            }
            else if(cor[indice] == cinza){
                *ciclo = true;
            }
        }
    }
    cor[v] = preto;
    vet[*qtd] = v;
    (*qtd)++;
    (*tempo)++;
    d[v] = *tempo;

}

/* Funcao que faz a busca em profundidade de um
 * grafo g, recebido por parametro. Retorno Void */
void busca_profundidade(grafo* g){
    int v, tempo, ciclo, qtd;
    int distancia[g->vertices], antecessor[g->vertices], t[g->vertices];
    int* vet = malloc(g->vertices * sizeof(int));

    tempo = 0;
    pinta_grafo(g, branco);
     for (v=0; v < g->vertices ; v++) {
         antecessor[v]=-1;
     }

    for (v=0; v < g->vertices ; v++) {
        if (g->cor[v]==branco){
            visita_dfs(g,v, &tempo, distancia, t, g->cor, antecessor, &ciclo, vet, &qtd);
        }
    }
    free(vet);
}

/* Funcao que faz a ordenacao topologica de um grafo g recebido por parametro.
 * Retorna um vetor de inteiros com os indices ordenados. */

int* ordenacao_topologica(grafo* g){
    int v, tempo, ciclo, qtd;
    int* distancia = malloc(g->vertices * sizeof(int));
    int* antecessor = malloc(g->vertices * sizeof(int));
    int* t = malloc(g->vertices * sizeof(int));
    int* vet = malloc(g->vertices * sizeof(int));

    pinta_grafo(g, branco);
     for (v=0; v < g->vertices ; v++) {
         antecessor[v]=-1;
     }

    for (v=0; v < g->vertices ; v++) {
        if (g->cor[v]==branco){
            visita_dfs(g,v, &tempo, distancia, t, g->cor, antecessor, &ciclo, vet, &qtd);
        }
    }

    free(distancia);
    free(antecessor);
    free(t);

    return vet;
}

/* Funcao que verifica se existe um ciclo no grafo g,
 * recebido por parametro. Tem retorno booleano. */

boolean verifica_ciclo(grafo* g){
    int v, tempo, qtd;
    int* distancia = malloc(g->vertices * sizeof(int));
    int* antecessor = malloc(g->vertices * sizeof(int));
    int* t = malloc(g->vertices * sizeof(int));
    int* vet = malloc(g->vertices * sizeof(int));

    int ciclo = false;
    pinta_grafo(g, branco);
     for (v=0; v < g->vertices ; v++) {
         antecessor[v]=-1;
     }

    for (v=0; v < g->vertices ; v++) {
        if (g->cor[v]==branco){
            visita_dfs(g,v, &tempo, distancia, t, g->cor, antecessor, &ciclo, vet, &qtd);
        }
    }

    free(vet);
    free(distancia);
    free(antecessor);
    free(t);

    return ciclo;
}

/* Funcao auxiliar ao algoritmo de Bellman.
 * Recebe os dois vertices de uma aresta, o peso dela,
 * o vetor de antecessores e de distancias por parametro.
 * Tem retorno void*/

void relaxar_aresta(int v1, int v2, int peso, int* ant, int* d){
    if(d[v2] > d[v1] + peso){
        d[v2] = d[v1] + peso;
        ant[v2] = v1;
    }
    return;
}

/* Funcao que realiza o algoritmo de Bellman. Recebe o grafo, o vertice inicial, 
 * o vetor das distancias e o vetor de antecessores por parametro. Tem retorno
 * void. */

void algoritmo_de_Bellman(grafo*g, int v, int* d, int* ant){
    int p;
    int v2;
    
    for(int i = 0; i < g->vertices; i++){
        d[i] = infinito;
        ant[i] = -1;
    }
    d[v] = 0;

    for(int i = 0; i < (g->vertices - 1); i++){
        for(int j = 0; j < g->vertices; j++){
            for(int k = 0; k < lista_tamanho(g->l[j]); k++){
                v2 = indice_lista(g->l[j], k);
                p = lista_getDist(g->l[j], k);
                relaxar_aresta(j, v2, p, ant, d);
            }
        }
    }
}

/*
void algoritmo_de_dijkstra(grafo* g, int v){
    int* d = malloc(g->vertices * sizeof(int));
    int* ant = malloc(g->vertices * sizeof(int));
    int aux = 0;
    
    for(int i = 0; i < g->vertices; i++){
        d[i] = infinito;
        ant[i] = -1;
    }
    d[v] = 0;
    LISTA* l = lista_criar();
    inserir_lista(l, v);

}
*/