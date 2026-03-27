#include <stdio.h>
#include <stdlib.h>

/*b) Crie um programa que:
o Aloque dinamicamente um vetor de 5 números inteiros,
o Peça para o usuário digitar os 5 números no espaço alocado,
o Mostre na tela os 5 números,
o Libere a memoria alocada.*/

int main()
{
    int i, *p;
    p=(int *) malloc(5*sizeof(int));
    for(i=0;i<5;i++){
        printf("Digite um numero: ");
        scanf("%d", (p+i));
    }
    for(i=0;i<5;i++){
        printf("\n%d", (*p+i));
    }
    free (p);
    return 0;
}
