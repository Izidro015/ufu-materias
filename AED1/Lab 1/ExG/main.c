#include <stdio.h>

/*g) Crie um programa que preencha uma matriz 5x10 com números inteiros e some cada uma das linhas,
armazenando o resultado das somas em um vetor. A seguir o programa deverá multiplicar cada elemento da matriz
pela soma da linha correspondente e mostrar a matriz resultante.*/

int main() {
    int matriz[5][10];
    int soma_linhas[5] = {0}; // Inicializa o vetor de soma de linhas com zeros.
    printf("Digite os elementos da matriz 5 x 10:\n");// Preenchendo a matriz com números inteiros.
    for (int i=0;i<5;i++){
        for (int j=0;j<10;j++){
            scanf("%d", &matriz[i][j]);
            soma_linhas[i]+=matriz[i][j]; // Somando os elementos da linha i.
        }
    }
    for (int i=0;i<5;i++){// Multiplicando cada elemento da matriz pela soma da linha correspondente.
        for (int j=0;j<10;j++){
            matriz[i][j]*=soma_linhas[i];
        }
    }
    printf("Matriz resultante:\n");// Exibindo a matriz resultante.
    for (int i=0;i<5;i++){
        for (int j=0;j<10;j++){
            printf("%d ",matriz[i][j]);
        }
        printf("\n");
    }
    return 0;
}
