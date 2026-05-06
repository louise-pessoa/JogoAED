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

