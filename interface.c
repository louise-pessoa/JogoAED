#include <stdio.h>
#include <string.h>
#include "interface.h"

// limpa o terminal (funciona no windows e linux)
void limpar_tela(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// linha separadora padrao do projeto
void exibir_separador(void) {
    printf("====================================\n");
}

// pausa e espera o usuario apertar enter
void pausar(void) {
    printf("\npressione enter para continuar...");
    // limpa buffer antes de ler
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    getchar();
}

// tela de creditos
void exibir_tela_creditos(void) {
    limpar_tela();
    exibir_separador();
    printf("       projeto aed - grupo 5\n");
    exibir_separador();
    printf("  disciplina: algoritmos e estruturas\n");
    printf("  tema: comida de mainha\n");
    printf("\n");
    printf("  integrantes:\n");
    printf("   - louise pessoa\n");
    printf("   - marilia liz alves\n");
    printf("   - mateus lins\n");
    printf("   - pedro david oliveira\n");
    printf("   - victor martins\n");
    exibir_separador();
    pausar();
}

// exibe pontuacao atual da partida
void exibir_tela_pontuacao(void) {
    limpar_tela();
    exibir_separador();
    printf("           pontuacao atual\n");
    exibir_separador();
    printf("  pontos: %d\n", estado.pontuacao);
    printf("  passos acertados: %d / %d\n",
           estado.passos_acertados, estado.passos_total);

    // barra de progresso simples
    if (estado.passos_total > 0) {
        int progresso = (estado.passos_acertados * 20) / estado.passos_total;
        printf("  progresso: [");
        for (int i = 0; i < 20; i++) {
            printf(i < progresso ? "#" : "-");
        }
        printf("]\n");
    }

    exibir_separador();
    pausar();
}

// lista todas as receitas disponiveis
void exibir_tela_receitas(Receita *lista) {
    limpar_tela();
    exibir_separador();
    printf("       receitas disponiveis\n");
    exibir_separador();

    if (lista == NULL) {
        printf("  nenhuma receita cadastrada.\n");
        exibir_separador();
        pausar();
        return;
    }

    int i = 1;
    Receita *aux = lista;
    while (aux != NULL) {
        printf("  [%d] %-20s | dif: %d | %d min\n",
               i, aux->nome, aux->dificuldade, aux->tempo);
        aux = aux->prox;
        i++;
    }

    exibir_separador();
    pausar();
}

// exibe ingredientes de uma receita especifica
void exibir_tela_ingredientes(Receita *receita) {
    limpar_tela();

    if (receita == NULL) {
        printf("  receita invalida.\n");
        pausar();
        return;
    }

    exibir_separador();
    printf("  ingredientes: %s\n", receita->nome);
    exibir_separador();

    if (receita->ingredientes == NULL) {
        printf("  (nenhum ingrediente cadastrado)\n");
    } else {
        Ingrediente *aux = receita->ingredientes;
        int i = 1;
        while (aux != NULL) {
            printf("  %d. %-25s - %s\n", i, aux->nome, aux->quantidade);
            aux = aux->prox;
            i++;
        }
    }

    exibir_separador();
    pausar();
}

// feedback visual quando o jogador acerta
void exibir_feedback_acerto(void) {
    printf("\n");
    exibir_separador();
    printf("  *** acertou! muito bem! ***\n");
    printf("  passos: %d/%d\n",
           estado.passos_acertados, estado.passos_total);
    exibir_separador();
}

// feedback visual quando o jogador erra
void exibir_feedback_erro(void) {
    printf("\n");
    exibir_separador();
    printf("  !!! passo errado! -20 pontos !!!\n");
    printf("  pontuacao atual: %d\n", estado.pontuacao);
    exibir_separador();
}

// feedback quando o tempo esgota
void exibir_feedback_tempo_esgotado(void) {
    printf("\n");
    exibir_separador();
    printf("  !!! tempo esgotado! penalidade aplicada !!!\n");
    printf("  pontuacao atual: %d\n", estado.pontuacao);
    exibir_separador();
}

// tela final mostrando vitoria ou derrota
void exibir_resultado_final(int venceu) {
    limpar_tela();
    exibir_separador();

    if (venceu) {
        printf("     parabens! voce venceu!\n");
        printf("     pontuacao final: %d\n", estado.pontuacao);
        printf("\n");
        printf("  os jurados do marco zero aprovam!\n");
    } else {
        printf("     fim de jogo. tente de novo!\n");
        printf("     pontuacao final: %d\n", estado.pontuacao);
        printf("\n");
        printf("  precisa de %d pontos para vencer.\n", META_FASE_FINAL);
    }

    exibir_separador();
    pausar();
}

// menu principal do jogo
void exibir_menu(void) {
    int opcao;

    do {
        limpar_tela();
        exibir_separador();
        printf("         comida de mainha\n");
        exibir_separador();
        printf("[1] jogar\n");
        printf("[2] ver receitas\n");
        printf("[3] ver pontuacao\n");
        printf("[4] creditos\n");
        printf("[0] sair\n");
        exibir_separador();

        printf("escolha uma opcao: ");
        if (scanf("%d", &opcao) != 1) {
            opcao = -1;
            // limpa buffer em caso de entrada invalida
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }

        switch (opcao) {
            case 1:
                printf("\niniciando partida...\n");
                pausar();
                break;
            case 2:
                // passa NULL por ora, a integracao com lista vem depois
                exibir_tela_receitas(NULL);
                break;
            case 3:
                exibir_tela_pontuacao();
                break;
            case 4:
                exibir_tela_creditos();
                break;
            case 0:
                printf("\nencerrando jogo. ate logo!\n");
                break;
            default:
                printf("\nopcao invalida. tente de novo.\n");
                pausar();
                break;
        }
    } while (opcao != 0);
}