#include <stdio.h>
#include "jogo.h"
#include "receitas.h"

int main(void) {
    iniciar_jogo();
    integrar_modulos();

    // lista todas as receitas cadastradas
    listar_receitas(receitas_disponiveis);

    // mostra ingredientes de cada uma
    Receita *aux = receitas_disponiveis;
    while (aux != NULL) {
        listar_ingredientes(aux);
        aux = aux->prox;
    }

    // libera memoria no final
    liberar_receitas(receitas_disponiveis);

    return 0;
}