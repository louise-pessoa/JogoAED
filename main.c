#include <stdio.h>
#include "raylib.h"
#include "jogo.h"
#include "interface.h"
#include "receitas.h"

int main(void) {
    iniciar_jogo();
    integrar_modulos();

    InitWindow(800, 600, "Receitas de Mainha");
    SetTargetFPS(60);

    int ultimo_acertou = 1;

    while (!WindowShouldClose()) {

        // === ATUALIZAR (input por estado) ===
        switch (tela_atual) {

            case TELA_MENU:
                if (IsKeyPressed(KEY_ONE))   tela_atual = TELA_RECEITAS;
                if (IsKeyPressed(KEY_THREE)) tela_atual = TELA_CREDITOS;
                break;

            case TELA_RECEITAS:
                for (int k = 0; k < 8; k++) {
                    if (IsKeyPressed(KEY_ONE + k)) {
                        Receita *r = buscar_receita_idx(receitas_disponiveis, k + 1);
                        if (r) { receita_ativa = r; tela_atual = TELA_INGREDIENTES; }
                    }
                }
                if (IsKeyPressed(KEY_ESCAPE)) tela_atual = TELA_MENU;
                break;

            case TELA_INGREDIENTES:
                if (IsKeyPressed(KEY_ENTER) && receita_ativa) {
                    iniciar_receita(receita_ativa);
                    tela_atual = TELA_PILHA;
                }
                if (IsKeyPressed(KEY_B) || IsKeyPressed(KEY_ESCAPE))
                    tela_atual = TELA_RECEITAS;
                break;

            case TELA_PILHA:
                if (!pilha_vazia(pilha_ativa)) {
                    if (IsKeyPressed(KEY_ENTER)) {
                        int limite = receita_ativa ? receita_ativa->tempo : 30;
                        calcular_pontuacao(1, (int)tempo_decorrido(), limite);
                        _avancar_progresso();
                        pilha_ativa = pop_passo(pilha_ativa);
                        iniciar_timer();
                        ultimo_acertou = 1;
                        tela_atual = TELA_FEEDBACK;
                    }
                    if (IsKeyPressed(KEY_ESCAPE)) {
                        calcular_pontuacao(0, 999, 30);
                        tela_atual = TELA_RESULTADO;
                    }
                } else {
                    tela_atual = TELA_RESULTADO;
                }
                break;

            case TELA_FEEDBACK:
                if (IsKeyPressed(KEY_ENTER)) {
                    tela_atual = pilha_vazia(pilha_ativa) ? TELA_RESULTADO : TELA_PILHA;
                }
                break;

            case TELA_RESULTADO:
                if (IsKeyPressed(KEY_ENTER)) {
                    resetar_partida();
                    tela_atual = TELA_MENU;
                }
                break;

            case TELA_CREDITOS:
                if (IsKeyPressed(KEY_ESCAPE)) tela_atual = TELA_MENU;
                break;

            default: break;
        }

        // === DESENHAR ===
        BeginDrawing();

        switch (tela_atual) {
            case TELA_MENU:
                tela_menu();
                break;
            case TELA_RECEITAS:
                tela_receitas(receitas_disponiveis);
                break;
            case TELA_INGREDIENTES:
                tela_ingredientes(receita_ativa);
                break;
            case TELA_PILHA: {
                char passo_str[110] = "Execute o proximo passo!";
                if (!pilha_vazia(pilha_ativa)) {
                    Passo p = ver_topo(pilha_ativa);
                    if (p.ingrediente[0] != '\0')
                        snprintf(passo_str, sizeof(passo_str), "%s: %s", p.acao, p.ingrediente);
                    else
                        snprintf(passo_str, sizeof(passo_str), "%s", p.acao);
                }
                tela_pilha(passo_str, estado.passos_acertados + 1, estado.passos_total, tempo_decorrido());
                break;
            }
            case TELA_FEEDBACK:
                tela_feedback(ultimo_acertou);
                break;
            case TELA_RESULTADO:
                tela_resultado(verificar_vitoria());
                break;
            case TELA_CREDITOS:
                tela_creditos();
                break;
            default:
                ClearBackground(RAYWHITE);
                break;
        }

        EndDrawing();
    }

    liberar_receitas(receitas_disponiveis);
    CloseWindow();
    return 0;
}