typedef struct Passo {
    char acao[50];
    char ingrediente[50];
} Passo;

typedef struct No {
    Passo dado;
    struct No* prox;
} No;

