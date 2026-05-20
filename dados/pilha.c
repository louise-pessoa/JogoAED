#include "pilha.h"
#include "receitas.h"
#include <stdlib.h>
#include <string.h>

// cria um no com o passo informado
No* _criar_no_passo(char* acao, char* ingrediente) {
    No* novo = (No*)malloc(sizeof(No));

    if (novo == NULL) return NULL;

    strcpy(novo->dado.acao, acao);
    strcpy(novo->dado.ingrediente, ingrediente);

    novo->prox = NULL;

    return novo;
}

// verifica se a pilha esta vazia
int pilha_vazia(No* topo) {
    return topo == NULL;
}

// empilha um novo passo
No* push_passo(No* topo, char* acao, char* ingrediente) {
    No* novo = _criar_no_passo(acao, ingrediente);

    if (novo == NULL) {
        return topo; 
    }

    novo->prox = topo; 
    topo = novo;       

    return topo;
}

// desempilha o topo
No* pop_passo(No* topo) {
    if (topo == NULL) {
        return NULL; 
    }

    No* removido = topo;   
    topo = topo->prox;    
    free(removido);      

    return topo;
}

// retorna o passo do topo sem remover
Passo ver_topo(No* topo) {
    if (topo == NULL) {
        Passo vazio = {"", ""};
        return vazio;
    }

    return topo->dado;
}

// empilha todos os passos da receita
No* carregar_passos(No* topo, Receita* receita) {
    Receita* atual = receita;

    while (atual != NULL) {
        topo = push_passo(topo, atual->passo_acao, atual->ingrediente);
        atual = atual->prox;
    }

    return topo;
}