#include "pilha.h"
#include <stdlib.h>
#include <string.h>

No* _criar_no_passo(char* acao, char* ingrediente) {
    No* novo = (No*) malloc(sizeof(No));

    if (novo == NULL) {
        return NULL; 
    }

    strcpy(novo->dado.acao, acao);
    strcpy(novo->dado.ingrediente, ingrediente);

    novo->prox = NULL;

    return novo;
}

int pilha_vazia(No* topo) {
    return topo == NULL;
}

No* push_passo(No* topo, char* acao, char* ingrediente) {
    No* novo = _criar_no_passo(acao, ingrediente);

    if (novo == NULL) {
        return topo; 
    }

    novo->prox = topo; 
    topo = novo;       

    return topo;
}

No* pop_passo(No* topo) {
    if (topo == NULL) {
        return NULL; 
    }

    No* removido = topo;   
    topo = topo->prox;    
    free(removido);      

    return topo;
}

Passo ver_topo(No* topo) {
    if (topo == NULL) {
        Passo vazio = {"", ""};
        return vazio;
    }

    return topo->dado;
}

No* carregar_passos(No* topo, Receita* receita) {
    Receita* atual = receita;

    while (atual != NULL) {
        topo = push_passo(topo, atual->passo_acao, atual->ingrediente);
        atual = atual->prox;
    }

    return topo;
}