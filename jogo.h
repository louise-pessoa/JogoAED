#ifndef JOGO_H
#define JOGO_H

#include <time.h>
#include "receitas.h"

// constantes do jogo
#define PONTUACAO_INICIAL      100
#define PENALIDADE_POR_SEGUNDO  10
#define META_FASE_FINAL         70
#define PENALIDADE_POR_ERROR   20


// estado da partida
typedef struct {
    int pontuacao;
    int rodada_atual;
    int em_execucao;
    int fase_final_ativa;
    int passos_acertados;   
    int passos_total;
} EstadoJogo;

// estado global definido em jogo.c
extern EstadoJogo estado;
extern Receita *receitas_disponiveis;

// funcoes publicas
void   iniciar_timer(void);
double tempo_decorrido(void);
int    tempo_esgotado(int limite);
void   resetar_partida(void);
void   iniciar_jogo(void);
int verificar_vitoria(void);
void calcular_pontuacao(int acertou, int tempo_gasto, int tempo_limite);
void _avancar_progresso(void);
void integrar_modulos(void);
// funcoes internas nao devem aparecer no .h (_aplicar_penalidade_tempo)

#endif