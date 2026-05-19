#include <stdio.h>
#include "raylib.h"
#include "jogo.h"
#include "interface.h"
#include "receitas.h"
#include "groq.h"

static ResultadoJurados jurados;
static int jurados_prontos = 0;

int main(void) {
    iniciar_jogo();
    integrar_modulos();

    InitWindow(800, 600, "Receitas de Mainha");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_ONE))   tela_atual = TELA_MENU;
        if (IsKeyPressed(KEY_TWO))   tela_atual = TELA_RECEITAS;
        if (IsKeyPressed(KEY_THREE)) tela_atual = TELA_INGREDIENTES;
        if (IsKeyPressed(KEY_FIVE))  tela_atual = TELA_PILHA;
        if (IsKeyPressed(KEY_SIX))   tela_atual = TELA_FEEDBACK;
        if (IsKeyPressed(KEY_SEVEN)) {
            if (!jurados_prontos) {
                jurados = avaliar_com_jurados(estado);
                jurados_prontos = 1;
            }
            tela_atual = TELA_RESULTADO;
        }
        if (IsKeyPressed(KEY_EIGHT)) tela_atual = TELA_CREDITOS;

        BeginDrawing();

        switch (tela_atual) {
            case TELA_MENU:
                tela_menu();
                break;
            case TELA_RECEITAS:
                tela_receitas(receitas_disponiveis);
                break;
            case TELA_INGREDIENTES:
                tela_ingredientes(receitas_disponiveis);
                break;
            case TELA_PILHA:
                tela_pilha("Execute o proximo passo!", estado.passos_acertados + 1, estado.passos_total, tempo_decorrido());
                break;
            case TELA_FEEDBACK:
                tela_feedback(1);
                break;
            case TELA_RESULTADO:
                tela_resultado(verificar_vitoria(), &jurados);
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