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