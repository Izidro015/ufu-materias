#include <stdio.h>
#include <stdlib.h>

/*c) Faça uma função para aproximar a função exponencial pela série de Taylor
(DICA: utilize a função de exponenciação criada no exercício b)*/


double calcTaylor(double x, int n){
    double result=1.0;//o primeiro termo da série é sempre 1
    double termo=1.0;
    for(int i=1;i<=n;i++){
        termo*=x/i;//calcula o próximo termo usando o anterior
        result+=termo;
    }
    return result;
}

int main() {
    double x;
    int n;
    printf("Digite o valor de x: ");
    scanf("%lf", &x);
    printf("Digite o numero de termos na serie (n): ");
    scanf("%d", &n);
    double expAprox = calcTaylor(x, n);
    double expReal = exp(x);
    printf("Exponencial aproximada: %0.8lf\n", expAprox);
    printf("Exponencial real: %0.8lf\n", expReal);
    return 0;
}
