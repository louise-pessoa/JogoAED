#ifndef RECEITAS_H
#define RECEITAS_H

struct No;

typedef struct ingrediente {
    char nome[60];
    char quantidade[30];         
    struct ingrediente *prox;
} Ingrediente;


typedef struct receita {
    char nome[60];
    int  dificuldade;             
    int  tempo;                   
    int  pontuacao;               
    Ingrediente *ingredientes;    

    char passo_acao[50];
    char ingrediente[50];

    struct No  *passos;           
    struct receita *prox;
} Receita;


// Lista de receitas 
Receita *inserir_receita(Receita *lista, const char *nome,int dificuldade, int tempo, int pontuacao);
void listar_receitas(Receita *lista);
Receita *buscar_receita(Receita *lista, const char *nome);     
Receita *buscar_receita_idx(Receita *lista, int indice);

// Lista de ingredientes 
Receita *inserir_ingrediente(Receita *receita, const char *nome, const char *quantidade);
void listar_ingredientes(const Receita *receita);


void definir_passo(Receita *no, const char *acao, const char *ing);

Receita *_criar_no_receita(const char *nome, int dificuldade, int tempo, int pontuacao);

Ingrediente *_criar_no_ingrediente(const char *nome, const char *quantidade);

void liberar_receitas(Receita *lista);

#endif 