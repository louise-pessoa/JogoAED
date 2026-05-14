#include <stdio.h>
#include "jogo.h"

int main(void) {
    iniciar_jogo();

    // simula uma receita de 3 passos
    estado.passos_total = 3;

    printf("\n=== Simulando execucao de receita ===\n");
    _avancar_progresso();  // passo 1 concluido
    _avancar_progresso();  // passo 2 concluido
    _avancar_progresso();  // passo 3 concluido (receita terminou)

    printf("\nResumo final:\n");
    printf("  passos_total:     %d\n", estado.passos_total);
    printf("  passos_acertados: %d\n", estado.passos_acertados);

    return 0;
}