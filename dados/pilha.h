#ifndef PILHA_H
#define PILHA_H

// passo de receita armazenado na pilha
typedef struct Passo {
    char acao[50];
    char ingrediente[50];
} Passo;

// no da pilha
typedef struct No {
    Passo dado;
    struct No* prox;
} No;

// funcoes da pilha
int   pilha_vazia(No *topo);
No   *push_passo(No *topo, char *acao, char *ingrediente);
No   *pop_passo(No *topo);
Passo ver_topo(No *topo);

#endif
