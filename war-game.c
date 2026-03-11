#include <stdio.h>
#include <string.h>

/*
    Struct Territorio:
    Armazena os dados básicos de um território do jogo WAR.
    Campos:
        - nome: nome do território
        - cor: cor do exército associado
        - tropas: quantidade de tropas posicionadas
*/
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

int main() {
    Territorio territorios[5];  // Vetor para armazenar 5 territórios
    int i;

    printf("=== Cadastro de Territorios (WAR) ===\n\n");

    // Entrada dos dados
    for (i = 0; i < 5; i++) {
        printf("Cadastro do territorio %d:\n", i + 1);

        // Leitura do nome
        printf("Digite o nome do territorio: ");
        scanf(" %29[^\n]", territorios[i].nome);  // Lê até 29 caracteres ou até o Enter

        // Leitura da cor
        printf("Digite a cor do exercito: ");
        scanf(" %9s", territorios[i].cor);  // Lê até 9 caracteres

        // Leitura das tropas
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);

        printf("\n");
    }

    // Exibição dos dados cadastrados
    printf("\n=== Territorios Cadastrados ===\n\n");

    for (i = 0; i < 5; i++) {
        printf("Territorio %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do exercito: %s\n", territorios[i].cor);
        printf("Tropas: %d\n", territorios[i].tropas);
        printf("-----------------------------\n");
    }

    return 0;
}
