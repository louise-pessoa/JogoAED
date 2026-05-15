#include <stdio.h>
#include "interface.h"
#include "jogo.h"

void exibir_menu(void) {

    int opcao;

    do {

        printf("\n");
        printf("====================================\n");
        printf("         comida de mainha\n");
        printf("====================================\n");
        printf("[1] jogar\n");
        printf("[2] testar receita\n");
        printf("[3] ver pontuacao\n");
        printf("[4] creditos\n");
        printf("[0] sair\n");
        printf("====================================\n");

        printf("escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {

            case 1:
                // inicia uma nova partida
                iniciar_jogo();
                printf("\npartida iniciada.\n");
                break;

            case 2:
                // teste rapido da mecanica
                estado.passos_total = 3;

                _avancar_progresso();
                _avancar_progresso();
                _avancar_progresso();
                break;

            case 3:
                printf("\npontuacao atual: %d\n", estado.pontuacao);
                break;

            case 4:
                printf("\nprojeto de aed - comida de mainha\n");
                break;

            case 0:
                printf("\nencerrando jogo...\n");
                break;

            default:
                printf("\nopcao invalida.\n");
                break;
        }

    } while(opcao != 0);

}