#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* ============================
        CORES ANSI
============================ */
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define BLUE    "\033[34m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define WHITE   "\033[37m"

/* ============================
        ENUM DE CORES
============================ */
typedef enum {
    VERMELHO,
    AZUL,
    VERDE,
    AMARELO,
    PRETO
} CorExercito;

/* ============================
        STRUCT TERRITÓRIO
============================ */
typedef struct {
    char nome[30];
    CorExercito cor;
    int tropas;
} Territorio;

/* ============================
   CONVERTE ENUM → TEXTO COLORIDO
============================ */
const char* corParaTexto(CorExercito c) {
    switch(c) {
        case VERMELHO: return RED "Vermelho" RESET;
        case AZUL:     return BLUE "Azul" RESET;
        case VERDE:    return GREEN "Verde" RESET;
        case AMARELO:  return YELLOW "Amarelo" RESET;
        case PRETO:    return WHITE "Preto" RESET;
        default:       return "Desconhecido";
    }
}

/* ============================
        ROLA VÁRIOS DADOS
============================ */
int rolarDados(int qtd) {
    int soma = 0;
    for (int i = 0; i < qtd; i++)
        soma += (rand() % 6) + 1;
    return soma;
}

/* ============================
        EXIBE TERRITÓRIOS
============================ */
void exibirTerritorios(Territorio* mapa, int qtd) {
    printf("\n===== ESTADO DOS TERRITÓRIOS =====\n");
    for (int i = 0; i < qtd; i++) {
        printf("%d - %s | Cor: %s | Tropas: %d\n",
               i,
               mapa[i].nome,
               corParaTexto(mapa[i].cor),
               mapa[i].tropas);
    }
}

/* ============================
        FUNÇÃO DE ATAQUE
============================ */
void atacar(Territorio* atacante, Territorio* defensor) {
    printf("\n%s (%s) está atacando %s (%s)!\n",
           atacante->nome, corParaTexto(atacante->cor),
           defensor->nome, corParaTexto(defensor->cor));

    int dadosA = atacante->tropas >= 3 ? 3 : atacante->tropas;
    int dadosD = defensor->tropas >= 3 ? 3 : defensor->tropas;

    int ataque = rolarDados(dadosA);
    int defesa = rolarDados(dadosD);

    ataque += atacante->tropas / 5;  // bônus por tropas
    defesa += defensor->tropas / 5;

    printf("Ataque (%d dados): %d\n", dadosA, ataque);
    printf("Defesa (%d dados): %d\n", dadosD, defesa);

    if (ataque > defesa) {
        printf(GREEN "Atacante venceu!\n" RESET);

        int dano = (ataque - defesa) / 2;
        defensor->tropas -= dano;

        if (defensor->tropas <= 0) {
            printf(RED "Território conquistado!\n" RESET);
            defensor->cor = atacante->cor;
            defensor->tropas = atacante->tropas / 2;
        }

    } else {
        printf(BLUE "Defensor resistiu!\n" RESET);

        int dano = (defesa - ataque) / 2;
        atacante->tropas -= dano;

        if (atacante->tropas < 1)
            atacante->tropas = 1;
    }
}

/* ============================
        LIBERA MEMÓRIA
============================ */
void liberarMemoria(Territorio* mapa) {
    free(mapa);
}

/* ============================
        MENU DE CORES
============================ */
CorExercito escolherCor() {
    int opc;
    printf("\nEscolha a cor do exército:\n");
    printf("0 - Vermelho\n");
    printf("1 - Azul\n");
    printf("2 - Verde\n");
    printf("3 - Amarelo\n");
    printf("4 - Preto\n");
    printf("Opção: ");
    scanf("%d", &opc);
    return opc;
}

/* ============================
        PROGRAMA PRINCIPAL
============================ */
int main() {
    srand(time(NULL));

    int qtd;
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &qtd);

    Territorio* mapa = calloc(qtd, sizeof(Territorio));

    for (int i = 0; i < qtd; i++) {
        printf("\n--- Cadastro do Território %d ---\n", i + 1);

        printf("Nome: ");
        scanf(" %[^\n]", mapa[i].nome);

        mapa[i].cor = escolherCor();

        printf("Tropas: ");
        scanf("%d", &mapa[i].tropas);
    }

    int opcao;
    do {
        exibirTerritorios(mapa, qtd);

        int a, d;
        printf("\nEscolha o território atacante (índice): ");
        scanf("%d", &a);

        printf("Escolha o território defensor (índice): ");
        scanf("%d", &d);

        if (mapa[a].cor == mapa[d].cor) {
            printf(RED "\nERRO: Não pode atacar um território da mesma cor!\n" RESET);
        } else {
            atacar(&mapa[a], &mapa[d]);
        }

        printf("\nDeseja realizar outro ataque? (1 = sim / 0 = não): ");
        scanf("%d", &opcao);

    } while (opcao == 1);

    liberarMemoria(mapa);

    printf("\nPrograma finalizado.\n");
    return 0;
}


