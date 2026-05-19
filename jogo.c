#include <stdio.h>
#include <time.h>
#include "jogo.h"
#include "receitas.h"
#include "estruturas/pilha.h"
#include "groq.h"

// estado interno do timer
static clock_t _inicio_timer;

// estado global usado por outros modulos
EstadoJogo estado;
// lista global de receitas disponiveis no jogo
Receita *receitas_disponiveis = NULL;
// receita escolhida pelo jogador no menu de receitas
Receita *receita_selecionada = NULL;
// tela ativa no momento
EstadoTela tela_atual = TELA_MENU;

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
    //jurados_prontos = 0;

    //pilha_esvaziar();

    printf("[SISTEMA] Partida resetada. Pontuacao: %d\n", PONTUACAO_INICIAL);
}

void iniciar_jogo(void) {
    resetar_partida();
    tela_atual = TELA_MENU;     // <-- ADICIONAR
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

void integrar_modulos(void) {
    // limpa lista anterior se existir
    if (receitas_disponiveis != NULL) {
        liberar_receitas(receitas_disponiveis);
        receitas_disponiveis = NULL;
    }

    // === cria as 3 receitas ===
    receitas_disponiveis = inserir_receita(receitas_disponiveis, "Tapioca",      2, 15, 50);
    receitas_disponiveis = inserir_receita(receitas_disponiveis, "Sururu",       4, 40, 80);
    receitas_disponiveis = inserir_receita(receitas_disponiveis, "Bolo de Rolo", 5, 60, 100);

    // === ingredientes da Tapioca ===
    Receita *tapioca = buscar_receita(receitas_disponiveis, "Tapioca");
    inserir_ingrediente(tapioca, "Tapioca granulada", "200g");
    inserir_ingrediente(tapioca, "Coco ralado",       "50g");
    inserir_ingrediente(tapioca, "Manteiga",          "1 colher");

    // === ingredientes do Sururu ===
    Receita *sururu = buscar_receita(receitas_disponiveis, "Sururu");
    inserir_ingrediente(sururu, "Sururu",         "500g");
    inserir_ingrediente(sururu, "Coentro",        "1 maco");
    inserir_ingrediente(sururu, "Cebola",         "1 unidade");
    inserir_ingrediente(sururu, "Leite de coco",  "200ml");

    // === ingredientes do Bolo de Rolo ===
    Receita *bolo = buscar_receita(receitas_disponiveis, "Bolo de Rolo");
    inserir_ingrediente(bolo, "Farinha de trigo", "300g");
    inserir_ingrediente(bolo, "Manteiga",         "200g");
    inserir_ingrediente(bolo, "Ovos",             "6 unidades");
    inserir_ingrediente(bolo, "Goiabada",         "300g");
    inserir_ingrediente(bolo, "Acucar",           "200g");

    // === passos jogaveis ===
    // tapioca: hidrata, mistura coco, derrete manteiga
    adicionar_passo_jogavel(tapioca, "Hidrate a tapioca peneirando",
                            "Tapioca granulada", "SSSS", 12);
    adicionar_passo_jogavel(tapioca, "Misture o coco ralado",
                            "Coco ralado", "ADAD", 10);
    adicionar_passo_jogavel(tapioca, "Derreta a manteiga na frigideira",
                            "Manteiga", "SPACE", 8);

    // sururu: limpa, corta cebola/coentro, refoga, finaliza com leite de coco
    adicionar_passo_jogavel(sururu, "Lave bem o sururu",
                            "Sururu", "WSWS", 12);
    adicionar_passo_jogavel(sururu, "Pique a cebola",
                            "Cebola", "QEQE", 10);
    adicionar_passo_jogavel(sururu, "Pique o coentro",
                            "Coentro", "QWE", 10);
    adicionar_passo_jogavel(sururu, "Refogue tudo com leite de coco",
                            "Leite de coco", "WASDW", 15);

    // bolo de rolo: cremeia manteiga+acucar, ovos, farinha, recheia
    adicionar_passo_jogavel(bolo, "Bata manteiga com acucar",
                            "Manteiga", "WASDW", 12);
    adicionar_passo_jogavel(bolo, "Adicione o acucar e bata",
                            "Acucar", "ASDF", 10);
    adicionar_passo_jogavel(bolo, "Acrescente os ovos um a um",
                            "Ovos", "SPACE", 8);
    adicionar_passo_jogavel(bolo, "Misture a farinha de trigo",
                            "Farinha de trigo", "QWERTY", 14);
    adicionar_passo_jogavel(bolo, "Espalhe a goiabada e enrole",
                            "Goiabada", "DDDD", 12);

    printf("[SISTEMA] Modulos integrados. 3 receitas disponiveis.\n");
}
