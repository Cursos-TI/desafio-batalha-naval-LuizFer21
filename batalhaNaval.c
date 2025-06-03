#include <stdio.h>

#define TAM_TABULEIRO 10
#define TAM_HABILIDADE 5
#define VALOR_AGUA 0
#define VALOR_NAVIO 3
#define VALOR_HABILIDADE 5

// Inicializa todo o tabuleiro com água
void inicializarTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = VALOR_AGUA;
        }
    }
}

// Cria uma matriz de habilidade com formato de cone (↓)
void criarCone(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            habilidade[i][j] = 0;
            if (j >= (TAM_HABILIDADE - 1) / 2 - i && j <= (TAM_HABILIDADE - 1) / 2 + i) {
                habilidade[i][j] = 1;
            }
        }
    }
}

// Cria uma matriz de habilidade com formato de cruz (+)
void criarCruz(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            habilidade[i][j] = (i == TAM_HABILIDADE / 2 || j == TAM_HABILIDADE / 2) ? 1 : 0;
        }
    }
}

// Cria uma matriz de habilidade com formato de octaedro (losango)
void criarOctaedro(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            habilidade[i][j] = (abs(i - centro) + abs(j - centro) <= centro) ? 1 : 0;
        }
    }
}

// Sobrepõe a matriz de habilidade ao tabuleiro com origem centrada
void aplicarHabilidade(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO],
                       int habilidade[TAM_HABILIDADE][TAM_HABILIDADE],
                       int origemLinha, int origemColuna) {
    int offset = TAM_HABILIDADE / 2;

    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (habilidade[i][j] == 1) {
                int linha = origemLinha + i - offset;
                int coluna = origemColuna + j - offset;

                if (linha >= 0 && linha < TAM_TABULEIRO && coluna >= 0 && coluna < TAM_TABULEIRO) {
                    // Não sobrescreve navios
                    if (tabuleiro[linha][coluna] != VALOR_NAVIO) {
                        tabuleiro[linha][coluna] = VALOR_HABILIDADE;
                    }
                }
            }
        }
    }
}

// Posiciona navios manualmente
void posicionarNavios(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    // Horizontal
    for (int i = 0; i < 3; i++)
        tabuleiro[1][2 + i] = VALOR_NAVIO;

    // Vertical
    for (int i = 0; i < 3; i++)
        tabuleiro[4 + i][4] = VALOR_NAVIO;

    // Diagonal ↘
    for (int i = 0; i < 3; i++)
        tabuleiro[0 + i][0 + i] = VALOR_NAVIO;

    // Diagonal ↙
    for (int i = 0; i < 3; i++)
        tabuleiro[0 + i][9 - i] = VALOR_NAVIO;
}

// Imprime o tabuleiro com legendas visuais
void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    printf("Legenda: 0 = Água, 3 = Navio, 5 = Área de habilidade\n\n");
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];
    int cone[TAM_HABILIDADE][TAM_HABILIDADE];
    int cruz[TAM_HABILIDADE][TAM_HABILIDADE];
    int octaedro[TAM_HABILIDADE][TAM_HABILIDADE];

    // Inicializa estruturas
    inicializarTabuleiro(tabuleiro);
    posicionarNavios(tabuleiro);

    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(octaedro);

    // Define pontos de origem e aplica habilidades
    aplicarHabilidade(tabuleiro, cone, 6, 2);      // Cone centrado em (6,2)
    aplicarHabilidade(tabuleiro, cruz, 5, 5);      // Cruz centrada em (5,5)
    aplicarHabilidade(tabuleiro, octaedro, 8, 8);  // Octaedro centrado em (8,8)

    // Exibe o resultado final
    exibirTabuleiro(tabuleiro);

    return 0;
}
