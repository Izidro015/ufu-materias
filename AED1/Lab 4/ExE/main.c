#include <stdio.h>
#include <stdlib.h>

/*e) Crie uma função que retorne um vetor alocado dinamicamente e preenchido com um valor passado como parâmetro.*/

int* criarVetor(int tamanho, int valor) {
    int* vetor = (int*)malloc(tamanho * sizeof(int));
    if (vetor == NULL) {
        printf("Erro na alocação de memória.\n");
        exit(1);
    }
    for (int i = 0; i < tamanho; i++) {
        vetor[i] = valor; //preenche o vetor com o valor passado como parâmetro
    }
    return vetor;
}

int main() {
    int tamanho, valor;
    printf("Digite o tamanho do vetor: ");
    scanf("%d", &tamanho);
    printf("Digite o valor para preencher o vetor: ");
    scanf("%d", &valor);
    int *vetor = criarVetor(tamanho, valor);
    printf("Vetor preenchido:\n");
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", vetor[i]);
    }
    free(vetor);
    return 0;
}
