#include <stdio.h>
#include "raylib.h"
#include "jogo.h"
#include "interface.h"
#include "receitas.h"

const char* nome_da_tela(EstadoTela t) {
    switch (t) {
        case TELA_MENU:         return "Menu Principal";
        case TELA_RECEITAS:     return "Lista de Receitas";
        case TELA_INGREDIENTES: return "Ingredientes da Receita";
        case TELA_CATCHER:      return "Mini-game Catcher";
        case TELA_PILHA:        return "Cozinhando (Pilha)";
        case TELA_FEEDBACK:     return "Feedback";
        case TELA_RESULTADO:    return "Resultado Final";
        case TELA_CREDITOS:     return "Creditos";
        default:                return "Desconhecida";
    }
}

int main(void) {
    iniciar_jogo();
    integrar_modulos();

    InitWindow(800, 600, "Receitas de Mainha");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_ONE))   tela_atual = TELA_MENU;
        if (IsKeyPressed(KEY_TWO))   tela_atual = TELA_RECEITAS;
        if (IsKeyPressed(KEY_THREE)) tela_atual = TELA_INGREDIENTES;
        if (IsKeyPressed(KEY_FOUR))  tela_atual = TELA_CATCHER;
        if (IsKeyPressed(KEY_FIVE))  tela_atual = TELA_PILHA;
        if (IsKeyPressed(KEY_SIX))   tela_atual = TELA_FEEDBACK;
        if (IsKeyPressed(KEY_SEVEN)) tela_atual = TELA_RESULTADO;
        if (IsKeyPressed(KEY_EIGHT)) tela_atual = TELA_CREDITOS;

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Receitas de Mainha", 200, 40, 36, MAROON);
        DrawText("Tela atual:", 50, 150, 24, DARKGRAY);
        DrawText(nome_da_tela(tela_atual), 200, 150, 24, DARKBLUE);
        DrawText("Pressione 1-8 para trocar de tela:", 50, 250, 18, GRAY);
        DrawText("1=Menu  2=Receitas  3=Ingredientes  4=Catcher", 50, 280, 16, GRAY);
        DrawText("5=Pilha  6=Feedback  7=Resultado  8=Creditos", 50, 305, 16, GRAY);
        DrawText(TextFormat("Pontuacao: %d", estado.pontuacao), 50, 400, 20, DARKGRAY);
        DrawText(TextFormat("Passos: %d/%d", estado.passos_acertados, estado.passos_total), 50, 430, 20, DARKGRAY);
        DrawText("ESC para sair", 50, 550, 16, GRAY);

        EndDrawing();
    }

    liberar_receitas(receitas_disponiveis);
    CloseWindow();
    return 0;
}