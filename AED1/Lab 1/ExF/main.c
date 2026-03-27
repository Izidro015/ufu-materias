#include <stdio.h>
#include <stdlib.h>

/*f) Faça um programa que calcule a área de um triângulo, cuja base e altura são fornecidas pelo usuário. Esse
programa não pode permitir a entrada de dados inválidos, ou seja, medidas menores ou iguais a 0.*/

void verif(float x, float y){
    if(x<=0||y<=0){
        printf("\nValores invalidos");
    }else{
        float resultado;
        resultado=(x*y)/2;
        printf("\nA area do triangulo eh: %0.2f", resultado);
    }
}

int main(){
    float base,altura;
    printf("Digite a base do triangulo: ");
    scanf("%f", &base);
    printf("Digite a altura do triangulo: ");
    scanf("%f", &altura);
    verif(base,altura);
    return 0;
}
