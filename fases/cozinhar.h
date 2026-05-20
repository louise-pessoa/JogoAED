#ifndef COZINHAR_H
#define COZINHAR_H

#include "raylib.h"
#include "../dados/receitas.h"
#include "../dados/pilha.h"

#define COZ_MAX_ING_GRID 8

typedef enum {
    COZ_FASE_CLICAR,    // jogador precisa clicar o ingrediente correto
    COZ_FASE_TECLAS,    // jogador precisa digitar a sequencia de teclas
    COZ_FASE_FEEDBACK,  // exibe feedback rapido entre passos
    COZ_FASE_FIM        // todos os passos concluidos (ou desistiu)
} CozFase;

typedef struct {
    char nome[60];
    Rectangle area;
    int  destacado;
    int  usado;
} IngredienteIcone;

typedef struct {
    Receita *receita;

    IngredienteIcone grid[COZ_MAX_ING_GRID];
    int n_grid;

    int passo_idx;           // qual passo da receita estamos
    CozFase fase;

    int  pos_tecla;          // posicao atual na sequencia
    int  acertou_passo;

    float tempo_passo;       // segundos desde o inicio do passo
    float feedback_timer;
    int   feedback_acerto;

    int erros;
    int acertos;
    int pontos;

    int   terminou;
    int   venceu;            // 1 se concluiu todos os passos

    No   *pilha;             // pilha de passos da receita (topo = passo atual)
} EstadoCozinhar;

extern EstadoCozinhar cozinhar;

void cozinhar_iniciar(Receita *receita);
void tela_cozinhar(void);
int  cozinhar_terminou(void);
int  cozinhar_venceu(void);

#endif
