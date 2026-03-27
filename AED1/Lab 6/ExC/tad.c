#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tad.h"

struct matriz{
    float **mat;
    int linhas;
    int colunas;
};
typedef matriz matriz;

matriz *criar(){
    int i;
    matriz *m = (matriz*) malloc (sizeof(matriz));
    printf("\nDigite o numero de linhas e colunas desejado: ");
    scanf("%d %d", &m->linhas, &m->colunas);
    if (m!= NULL){
        m->mat = (float**) calloc (m->linhas, sizeof(float*));
        for (i = 0; i < m->linhas; i++){
            m->mat[i] = (float*) calloc (m->colunas, sizeof(float));
        }
    }
    return m;
}

void destruir(matriz *m){
    int i;
    for (i = 0; i < m->linhas; i++){
        free(m->mat[i]);
    }
    free(m->mat);
}

void atribuir(matriz *m, int linha, int coluna){
    printf("\nDigite o valor que deseja colocar nessa posicao: ");
    scanf("%f", &m->mat[linha][coluna]);
}

float elemento(matriz *m, int linha, int coluna){
    return m->mat[linha][coluna];
}

int retorna_linhas(matriz *m){
    return m->linhas;
}

int retorna_colunas(matriz *m){
    return m->colunas;
}

void aleatorio(matriz *m, float minimo, float maximo){
    int i, j;
    float numero_aleatorio;
    srand(time(NULL));
    for (i = 0; i < m->linhas; i++){
        for (j = 0; j < m->colunas; j++){
            numero_aleatorio = ((float)rand() / RAND_MAX) * (maximo - minimo) + minimo;
            m->mat[i][j] = numero_aleatorio;
        }
    }
}

matriz* soma(matriz *m, matriz *n){
    int i, j;
    matriz *aux;
    aux = criar();
    if((m->linhas != n->linhas) || (m->colunas != n->colunas)){
        printf("\nVoce nao pode somar matrizes de dimensões diferentes!");
        return 0;
    }
    else{
        for (i = 0; i < m->linhas; i++){
            for (j = 0; j < m->colunas; j++){
                aux->mat[i][j] = m->mat[i][j] + n->mat[i][j];
            }
        }
        return aux;
    }
}

void exibe(matriz *m){
    int i, j;
    printf("\n Matriz atualizada:\n");
    for (i = 0; i < m->linhas; i++){
        for (j = 0; j < m->colunas; j++){
            printf(" %.2f ", m->mat[i][j]);
        }
        printf("\n");
    }
}
