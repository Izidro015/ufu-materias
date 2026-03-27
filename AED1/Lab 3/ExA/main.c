#include <stdio.h>
#include <stdlib.h>

 /*a) Escreva uma função que receba como parâmetro um número inteiro positivo
 N e retorne a soma de todos os números inteiros de 1 a N.*/

 int numero(int N){
    int soma=0;
    for(int i=0;i<=N;i++){
        soma=soma+i;
    }
    return soma;
 }

 int main(){
    int num,result;
    printf("Digite um numero inteiro e positivo: ");
    scanf("%d", &num);
    if(num<0){
        printf("numero invalido");
        return 0;
    }else{
        result=numero(num);
        printf("A soma dos elementos deu: %d", result);
    }
    return 0;
 }
