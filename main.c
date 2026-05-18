#include <stdio.h>
#include "raylib.h"
#include "jogo.h"
<<<<<<< HEAD
#include "interface.h"
=======
#include "receitas.h"

// nomes das telas (so pra debug, vai sumir quando o Pedro fizer as telas reais)
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
>>>>>>> ceb8ec7131cc0f5fe4b7ef90827bd46e199fbb66

int main(void) {
    // setup do jogo
    iniciar_jogo();
<<<<<<< HEAD
    exibir_menu();
=======
    integrar_modulos();

    // setup do raylib
    InitWindow(800, 600, "Receitas de Mainha");
    SetTargetFPS(60);

    // loop principal
    while (!WindowShouldClose()) {
        // === ATUALIZAR ===
        // troca de tela com teclado (TEMPORARIO, pra teste)
        if (IsKeyPressed(KEY_ONE))   tela_atual = TELA_MENU;
        if (IsKeyPressed(KEY_TWO))   tela_atual = TELA_RECEITAS;
        if (IsKeyPressed(KEY_THREE)) tela_atual = TELA_INGREDIENTES;
        if (IsKeyPressed(KEY_FOUR))  tela_atual = TELA_CATCHER;
        if (IsKeyPressed(KEY_FIVE))  tela_atual = TELA_PILHA;
        if (IsKeyPressed(KEY_SIX))   tela_atual = TELA_FEEDBACK;
        if (IsKeyPressed(KEY_SEVEN)) tela_atual = TELA_RESULTADO;
        if (IsKeyPressed(KEY_EIGHT)) tela_atual = TELA_CREDITOS;

        // === DESENHAR ===
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // titulo
        DrawText("Receitas de Mainha", 200, 40, 36, MAROON);

        // qual tela estamos
        DrawText("Tela atual:", 50, 150, 24, DARKGRAY);
        DrawText(nome_da_tela(tela_atual), 200, 150, 24, DARKBLUE);

        // instrucoes
        DrawText("Pressione 1-8 para trocar de tela:", 50, 250, 18, GRAY);
        DrawText("1=Menu  2=Receitas  3=Ingredientes  4=Catcher", 50, 280, 16, GRAY);
        DrawText("5=Pilha  6=Feedback  7=Resultado  8=Creditos", 50, 305, 16, GRAY);

        // info do estado
        DrawText(TextFormat("Pontuacao: %d", estado.pontuacao), 50, 400, 20, DARKGRAY);
        DrawText(TextFormat("Passos: %d/%d", estado.passos_acertados, estado.passos_total), 50, 430, 20, DARKGRAY);

        DrawText("ESC para sair", 50, 550, 16, GRAY);

        EndDrawing();
    }

    // cleanup
    liberar_receitas(receitas_disponiveis);
    CloseWindow();
>>>>>>> ceb8ec7131cc0f5fe4b7ef90827bd46e199fbb66
    return 0;
}
