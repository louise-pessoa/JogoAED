#include "receitas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
Receita *_criar_no_receita(const char *nome, int dificuldade,int tempo, int pontuacao) {
    Receita *novo = (Receita *) malloc(sizeof(Receita));
    if (novo == NULL) return NULL;

    strncpy(novo->nome, nome, sizeof(novo->nome) - 1);
    novo->nome[sizeof(novo->nome) - 1] = '\0';
    novo->dificuldade = dificuldade;
    novo->tempo = tempo;
    novo->pontuacao = pontuacao;
    novo->ingredientes = NULL;

    novo->passo_acao[0]  = '\0';
    novo->ingrediente[0] = '\0';

    novo->passos       = NULL;  
    novo->prox         = NULL;
    return novo;
}

Ingrediente *_criar_no_ingrediente(const char *nome, const char *quantidade) {
    Ingrediente *novo = (Ingrediente *) malloc(sizeof(Ingrediente));
    if (novo == NULL) {
        return NULL;
    }

    strncpy(novo->nome, nome, sizeof(novo->nome) - 1);
    novo->nome[sizeof(novo->nome) - 1] = '\0';

    strncpy(novo->quantidade, quantidade, sizeof(novo->quantidade) - 1);
    novo->quantidade[sizeof(novo->quantidade) - 1] = '\0';

    novo->prox = NULL;
    return novo;
}

// Lista de receitas

// Insere no final da lista e retorna o inicio da lista (pode ser o novo no se a lista tava vazia).
Receita *inserir_receita(Receita *lista, const char *nome,int dificuldade, int tempo, int pontuacao) {
    Receita *novo = _criar_no_receita(nome, dificuldade, tempo, pontuacao);
    if (novo == NULL) return lista;

    if (lista == NULL) {
        return novo;
    }

    Receita *aux = lista;
    while (aux->prox != NULL) {
        aux = aux->prox;
    }
    aux->prox = novo;
    return lista;
}

void listar_receitas(Receita *lista) {
    if (lista == NULL) {
        printf("Nenhuma receita cadastrada.\n");
        return;
    }

    printf("\n=== Receitas Disponiveis ===\n");
    int i = 1;
    Receita *aux = lista;
    while (aux != NULL) {
        printf("%d. %-20s | dificuldade: %d | tempo: %3d min | pontos: %d\n",i, aux->nome, aux->dificuldade, aux->tempo, aux->pontuacao);
        aux = aux->prox;
        i++;
    }
    printf("============================\n");
}

// Busca por nome 

Receita *buscar_receita(Receita *lista, const char *nome) {
    Receita *aux = lista;
    while (aux != NULL) {
        if (strcmp(aux->nome, nome) == 0) {
            return aux;
        }
        aux = aux->prox;
    }
    return NULL;
}

// Busca por indice 
Receita *buscar_receita_idx(Receita *lista, int indice) {
    if (indice < 1) return NULL;
    int i = 1;
    Receita *aux = lista;
    while (aux != NULL) {
        if (i == indice) return aux;
        aux = aux->prox;
        i++;
    }
    return NULL;
}