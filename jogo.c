#include <stdio.h>
#include <time.h>
#include "jogo.h"
#include "lista.h"    /* funções públicas do módulo de lista   */
#include "pilha.h"    /* funções públicas do módulo de pilha   */
#include "logica.h"   /* funções públicas do módulo de lógica  */

// estado interno do timer
static clock_t _inicio_timer;

// estado global usado por outros modulos
EstadoJogo estado;

// inicia o cronometro do passo atual
void iniciar_timer(void) {
    _inicio_timer = clock();
}

// retorna segundos desde o ultimo iniciar_timer()
double tempo_decorrido(void) {
    clock_t agora = clock();
    return (double)(agora - _inicio_timer) / CLOCKS_PER_SEC;
}

// verifica se o tempo passou do limite
int tempo_esgotado(int limite) {
    if (limite <= 0) {
        // limite invalido, trata como esgotado
        fprintf(stderr, "[AVISO] tempo_esgotado: limite invalido (%d)\n", limite);
        return 1;
    }

    return tempo_decorrido() >= (double)limite;
}

// calcula o desconto por atraso (uso interno)
static int _calcular_penalidade_tempo(int tempo_gasto, int tempo_limite) {
    if (tempo_gasto <= tempo_limite) return 0;

    int atraso   = tempo_gasto - tempo_limite;
    int desconto = atraso * PENALIDADE_POR_SEGUNDO;

    return desconto;
}

// reinicia a partida e limpa a pilha de passos
void resetar_partida(void) {
    estado.pontuacao        = PONTUACAO_INICIAL;
    estado.rodada_atual     = 1;
    estado.em_execucao      = 0;
    estado.fase_final_ativa = 0;
    _inicio_timer           = 0;

    pilha_esvaziar();

    printf("[SISTEMA] Partida resetada. Pontuacao: %d\n", PONTUACAO_INICIAL);
}