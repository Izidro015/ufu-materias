#include <stdio.h>
#include <stdlib.h>

/*d) Faça uma função para multiplicar um vetor por um escalar (um número).
Mostre, no programa principal, o vetor antes e depois da multiplicação.*/

void func(float *vet, int quant, float mult){
    for(int i=0;i<quant;i++){
        vet[i]=mult*vet[i];
    }
}

int main(){
    float *vet, mult;
    int quant;
    printf("Digite a quantidade de numeros do vetor: ");
    scanf("%d", &quant);
    vet=(float *)malloc(quant*sizeof(float));
    for(int i=0;i<quant;i++){
        printf("Digite um valor: ");
        scanf("%f", &vet[i]);
    }
    printf("Antes da mudanca: \n");
    for(int j=0;j<quant;j++){
        printf("%.2f ", vet[j]);
    }
    printf("\nDigite um numero para multiplicar: ");
    scanf("%f", &mult);
    func(vet,quant,mult);
    printf("Vetor depois da multiplicacao: \n");
    for (int j=0;j<quant;j++){
        printf("%.2f ", vet[j]);
    }
    free(vet);
    return 0;
}
