#include <stdio.h>
#include <stdlib.h>
#define LINHAS 3
#define COLUNAS 3

/*c) Faça um programa que crie duas matrizes 3x3, utilizando dois ponteiros.
Preencha as matrizes com valores inteiros. Crie uma terceira matriz, também
utilizando ponteiros, e preencha com o resultado da soma dos elementos respectivos
das outras matrizes. Mostre na tela as tres matrizes*/

void preencherMatriz(int *matriz, const char *nome) {
    printf("Preencha a matriz %s:\n", nome);
    for (int i=0;i<LINHAS;i++){
        for (int j=0;j<COLUNAS;j++){
            printf("Digite o valor para a posição [%d][%d]: ", i,j);
            scanf("%d", matriz+i * COLUNAS+j);
        }
    }
}
void somarMatrizes(const int *matriz1, const int *matriz2, int *resultado) {
    for (int i=0;i<LINHAS;i++) {
        for (int j=0;j<COLUNAS;j++) {
            resultado[i * COLUNAS+j] = matriz1[i * COLUNAS+j]+matriz2[i * COLUNAS+j];
        }
    }
}
void imprimirMatriz(const int *matriz, const char *nome) {
    printf("\nMatriz %s:\n", nome);
    for (int i=0;i<LINHAS;i++) {
        for (int j=0;j<COLUNAS;j++) {
            printf("%d ", matriz[i * COLUNAS+j]);
        }
        printf("\n");
    }
}

int main() {
    int matriz1[LINHAS][COLUNAS];
    int matriz2[LINHAS][COLUNAS];
    int matrizsoma[LINHAS][COLUNAS];
    preencherMatriz(&matriz1[0][0], "1");
    preencherMatriz(&matriz2[0][0], "2");
    somarMatrizes(&matriz1[0][0], &matriz2[0][0], &matrizsoma[0][0]);
    imprimirMatriz(&matriz1[0][0], "1");
    imprimirMatriz(&matriz2[0][0], "2");
    imprimirMatriz(&matrizsoma[0][0], "soma");
    return 0;
}
