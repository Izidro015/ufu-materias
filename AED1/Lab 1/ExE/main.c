#include <stdio.h>
#include <stdlib.h>

/*e) Faça o programa que lê X números e soma os maiores que 10 e conta os menores que 10. Considere que a leitura dos números encerra quando o usuário digita dez.*/

int main(){
    float num,num_maiores=0;
    int num_menores=0;
    printf("Digite os numeros(encerre a contagem com 10): \n");
    while(1){
        scanf("%f", &num);
        if(num==10){
            break;
        }else if(num>10){
            num_maiores+=num;
        }else{
            num_menores++;
        }
    }
    printf("Soma dos números maiores que 10: %0.2f\n", num_maiores);
    printf("Quantidade de números menores que 10: %d\n", num_menores);
    return 0;
}
