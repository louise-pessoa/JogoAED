#ifndef INTERFACE_H
#define INTERFACE_H

#include "receitas.h"
#include "jogo.h"

// menu principal
void exibir_menu(void);

// telas de navegacao
void exibir_tela_receitas(Receita *lista);
void exibir_tela_ingredientes(Receita *receita);
void exibir_tela_creditos(void);
void exibir_tela_pontuacao(void);

// feedback durante o jogo
void exibir_feedback_acerto(void);
void exibir_feedback_erro(void);
void exibir_feedback_tempo_esgotado(void);

// tela de resultado final
void exibir_resultado_final(int venceu);

// utilitarios de exibicao
void limpar_tela(void);
void exibir_separador(void);
void pausar(void);

#endif