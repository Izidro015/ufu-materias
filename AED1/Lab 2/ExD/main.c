#include <stdio.h>
#include <stdlib.h>

/*d) Escreva um programa em C que crie um vetor de n números inteiros
(n informado pelo usuário). Faça a leitura dos elementos desse vetor. Depois,
exclua os elementos ímpares desse vetor, e redimensione-o, utilizando alocação
dinâmica de memória, para que não haja buracos no resultado final*/

int main() {
    int n;
    int *vetor = (int *)malloc(n * sizeof(int));
    printf("Digite o tamanho do vetor: ");
    scanf("%d",&n);
    if (vetor==NULL){
        printf("Erro na alocação de memória.\n");
        return 1;
    }
    printf("Digite os elementos do vetor:\n");
    for (int i=0;i<n;i++) {
        scanf("%d",&vetor[i]);
    }
    int elementosPares=0;// Exclui os impares
    for (int i=0;i<n;i++) {
        if (vetor[i]%2==0) {
            elementosPares++;
        }
    }
    int *vetorRed = (int *)malloc(elementosPares * sizeof(int));
    if (vetorRed==NULL) {
        printf("Erro na alocação de memória.\n");
        free(vetor);
        return 1;
    }
    int idx=0;
    for (int i=0;i<n;i++) {
        if (vetor[i]%2==0) {
            vetorRed[idx]=vetor[i];
            idx++;
        }
    }
    free(vetor);
    printf("Vetor resultante:\n");
    for (int i=0;i<elementosPares;i++) {
        printf("%d ",vetorRed[i]);
    }
    printf("\n");
    free(vetorRed);// Liberando memória do vetor redimensionado
    return 0;
}
