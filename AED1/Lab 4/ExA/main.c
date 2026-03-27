#include <stdio.h>
#include <stdlib.h>

/*a) Faça uma função que receba um vetor de números inteiros como parâmetro, e devolve:
o a média dos valores do vetor;
o o maior valor do vetor.
Esses valores devem ser retornados utilizando passagem de parâmetros por referência.*/

void func(int *vet, float *media, int *maior, int tamanho){
    *media=0;
    *maior=0;
    for(int i=0; i<tamanho; i++){
        *media+=vet[i];
        if(vet[i]>*maior){
            *maior=vet[i];
        }
    }
    *media/=tamanho;

}

int main(){
    int *vet, maior, tamanho;
    float media;
    printf("Digite o tamanho do vetor: ");
    scanf("%d", &tamanho);
    vet=(int *)malloc(tamanho*sizeof(int));
    for(int i=0;i<tamanho;i++){
        printf("Digite um valor: ");
        scanf("%d", &vet[i]);
    }
    func(vet,&media,&maior,tamanho);
    printf("O maior numero: %d\n", maior);
    printf("A media: %0.2f\n", media);
    free(vet);
    return 0;
}
