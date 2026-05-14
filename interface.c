#include <stdio.h>
#include "interface.h"
#include "jogo.h"

void exibir_menu() {

    int opcao;

    do {

        printf("\n");
        printf("================================\n");
        printf("       comida de mainha\n");
        printf("================================\n");
        printf("1 - jogar\n");
        printf("2 - testar receita\n");
        printf("3 - ver pontuacao\n");
        printf("0 - sair\n");
        printf("================================\n");

        printf("escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {

            case 1:

                // inicia uma nova partida
                iniciar_jogo();

                printf("\njogo iniciado!\n");
                break;

            case 2:

                // simula uma receita simples
                estado.passos_total = 3;

                _avancar_progresso();
                _avancar_progresso();
                _avancar_progresso();

                break;

            case 3:

                printf("\npontuacao atual: %d\n", estado.pontuacao);
                break;

            case 0:

                printf("\nencerrando...\n");
                break;

            default:

                printf("\nopcao invalida.\n");

        }

    } while(opcao != 0);

}