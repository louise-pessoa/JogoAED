#include <stdio.h>
#include <time.h>
#include "jogo.h"
// #include "lista.h"    /* funções públicas do módulo de lista   */
#include "estruturas/pilha.h"    /* funções públicas do módulo de pilha   */
// #include "logica.h"   /* funções públicas do módulo de lógica  */

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
    estado.passos_acertados  = 0;   
    estado.passos_total      = 0;  
    _inicio_timer           = 0;

    // pilha_esvaziar();

    printf("[SISTEMA] Partida resetada. Pontuacao: %d\n", PONTUACAO_INICIAL);
}

void iniciar_jogo(void) {
    resetar_partida();
    printf("[SISTEMA] Jogo iniciado. Boa sorte!\n");
}
static void _aplicar_penalidade_error(int valor){
    if (valor <= 0) return;
    estado.pontuacao -= valor;
    if(estado.pontuacao < 0){
        estado.pontuacao = 0;
    }
    printf("[PENALIDADE] -%d pontos. Pontuacao atual: %d\n", valor, estado.pontuacao);

    }
int verificar_vitoria(void) {
    return estado.pontuacao >= META_FASE_FINAL;
}
void calcular_pontuacao(int acertou, int tempo_gasto, int tempo_limite) {
    if (!acertou) {
        _aplicar_penalidade_error(PENALIDADE_POR_ERROR);
    }
    int desconto_tempo = _calcular_penalidade_tempo(tempo_gasto, tempo_limite);
    if (desconto_tempo > 0) {
        _aplicar_penalidade_error(desconto_tempo);
    }
    if (acertou && desconto_tempo == 0) {
        printf("[PONTUACAO] Acerto perfeito! Pontuacao: %d\n", estado.pontuacao);
    }
}
void _avancar_progresso(void) {
    estado.passos_acertados++;
    printf("[PROGRESSO] Passo concluido (%d/%d)\n",
           estado.passos_acertados, estado.passos_total);
}
