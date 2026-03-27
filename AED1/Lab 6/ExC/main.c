#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tad.h"

int main(){
    float e, minimo, maximo, auxiliar;
    int linhas, colunas, opcao;
    matriz *m, *n, *x;
    m = criar();
    printf("\nBem vindo ao programa para manipular matrizes.");
    while(1){
        printf("\nDigite as coordenadas do elemento que deseja atribuir valor: ");
        scanf("%d %d", &linhas, &colunas);
        atribuir(m, linhas, colunas);
        exibe(m);
        printf("\nGostaria de atribuir valor para outro elemento? Digite 1 para sim, qualquer coisa para nao: ");
        scanf("%d", &opcao);
        if (opcao != 1){
            break;
        }
    }
    printf("\nDigite as coordenadas do elemento que deseja visualizar o valor: ");
    scanf("%d %d", &linhas, &colunas);
    auxiliar = elemento(m, linhas, colunas);
    printf("\nO valor eh: %.2f\n", auxiliar);
    linhas = retorna_linhas(m);
    printf("\nO numero de linhas eh: %d\n", linhas);
    colunas = retorna_colunas(m);
    printf("\nO numero de colunas eh: %d\n", colunas);
    printf("\nDigite um intervalo(valor minimo e maximo) para preencher a matriz com valores aleatorios: \n");
    scanf("%f %f", &minimo, &maximo);
    printf("\nPreenchendo a matriz com valores aleatorios:\n");
    aleatorio(m, minimo, maximo);
    exibe(m);
    printf("\nPreencha a segunda matriz agora: ");
    n = criar();
    while(1){
        printf("\nDigite as coordenadas do elemento que deseja atribuir valor: ");
        scanf("%d %d", &linhas, &colunas);
        atribuir(n, linhas, colunas);
        exibe(n);
        printf("\nGostaria de atribuir valor para outro elemento? Digite 1 para sim, qualquer coisa para nao: ");
        scanf("%d", &opcao);
        if (opcao != 1){
            break;
        }
    }
    printf("\nDigite as coordenadas do elemento que deseja visualizar o valor: ");
    scanf("%d %d", &linhas, &colunas);
    auxiliar = elemento(n, linhas, colunas);
    printf("\nO valor eh: %.2f", auxiliar);
    linhas = retorna_linhas(n);
    printf("\nO numero de linhas eh: %d", linhas);
    colunas = retorna_colunas(n);
    printf("\nO numero de colunas eh: %d", colunas);
    printf("\nDigite um intervalo(valor minimo e maximo) para preencher a matriz com valores aleatorios: \n");
    scanf("%f %f", &minimo, &maximo);
    printf("\nPreenchendo a matriz com valores aleatorios:\n");
    aleatorio(n, minimo, maximo);
    exibe(n);
    printf("\nDigite as mesmas dimensoes das matrizes n e m: ");
    x = soma(m, n);
    exibe(x);
    destruir(n);
    destruir(m);
    destruir(x);
    return 0;
}
