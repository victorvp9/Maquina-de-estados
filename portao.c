#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

typedef enum {
    FECHADO,
    FECHANDO,
    ABERTO,
    ABRINDO,
    EMERG
} Estado;

/* A enumeração Comando não está sendo utilizada e foi removida */

void verificarEmergencia(Estado *estado) {
    int chance = rand() % 100; // Gera um numero entre 0 e 99
    if (chance < 3) { // Probabilidade de 3% de entrar em emergencia
        *estado = EMERG;
        printf("\n** Emergencia detectada! **\n");
    }
}

void executarTransicao(Estado *estadoAtual, Estado estadoDestino) {
    if(*estadoAtual == ABRINDO){
        printf("Iniciando abertura...\n");
    } else if(*estadoAtual == FECHANDO){
        printf("Iniciando fechamento...\n");
    }
    for (int i = 0; i < 5; i++) {
        Sleep(500); // Delay de 0.5 segundo
        verificarEmergencia(estadoAtual);
        if (*estadoAtual == EMERG) {
            printf("Transicao interrompida devido a emergencia.\n");
            return;
        }
        if(*estadoAtual == ABRINDO){
            printf("Abrindo, ");
        } else if(*estadoAtual == FECHANDO){
            printf("Fechando, ");
        }
        printf("passo %d/5 concluido.\n", i + 1);
    }
    *estadoAtual = estadoDestino;
    printf("Transicao concluida. Novo estado: ");
    switch (*estadoAtual) {
        case FECHADO:
            printf("FECHADO\n");
            break;
        case FECHANDO:
            printf("FECHANDO\n");
            break;
        case ABERTO:
            printf("ABERTO\n");
            break;
        case ABRINDO:
            printf("ABRINDO\n");
            break;
        case EMERG:
            printf("EMERGENCIA\n");
            break;
        default:
            break;
    }
}

int main() {
    Estado estadoAtual = FECHADO;
    int opcao;
    srand(time(NULL)); // Inicializa o gerador de numeros aleatorios

    while (1) {
        printf("\nEstado atual: ");
        switch (estadoAtual) {
            case FECHADO:
                printf("FECHADO\n");
                break;
            case FECHANDO:
                printf("FECHANDO\n");
                break;
            case ABERTO:
                printf("ABERTO\n");
                break;
            case ABRINDO:
                printf("ABRINDO\n");
                break;
            case EMERG:
                printf("EMERGENCIA\n");
                break;
            default:
                break;
        }

        printf("Selecione um comando:\n");
        if (estadoAtual == EMERG) {
            printf("2 - ABRIR\n");
        } else {
            printf("1 - FECHAR\n");
            printf("2 - ABRIR\n");
            printf("3 - EMERGENCIA\n");
        }
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        if (opcao == 0) {
            printf("Encerrando o programa.\n");
            break;
        }

        if (estadoAtual == EMERG && opcao != 2) {
            printf("Comando invalido no estado de emergencia. Voce so pode ABRIR.\n");
            continue;
        }

        switch (opcao) {
            case 1:
                if (estadoAtual == ABERTO) {
                    estadoAtual = FECHANDO;
                    executarTransicao(&estadoAtual, FECHADO);
                } else if(estadoAtual == EMERG){
                    printf("Nao e possivel FECHAR a partir da EMERGENCIA.\n");
                } else{
                    printf("Ja esta fechado.\n");
                }
                break;
            case 2:
                if (estadoAtual == FECHADO || estadoAtual == EMERG) {
                    estadoAtual = ABRINDO;
                    executarTransicao(&estadoAtual, ABERTO);
                } else {
                    printf("Ja esta aberto.\n");
                }
                break;
            case 3:
                estadoAtual = EMERG;
                break;
            default:
                printf("Comando invalido.\n");
                break;
        }
    }

    return 0;
}
