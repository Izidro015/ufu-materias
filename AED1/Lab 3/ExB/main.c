#include <stdio.h>
#include <stdlib.h>

 /*b) Faça uma função que calcule X elevado à Y (X^Y), sem utilizar a
 função pow. No programa principal, leia 2 valores de X e Y e exiba o
 resultado da chamada da sub-rotina na tela*/

 void calc(int a, int b){
    int result;
    if(a==0){
        printf("X elevado a Y eh: 0");
    }else if(b==0||a==1){
        printf("X elevado a Y eh: 1");
    }else if(b==1){
        printf("X elevado a Y eh: %d", a);
    }else{
        for(int i=1;i<b;i++){
            result=a*a;

        }
        printf("X elevado a Y eh: %d", result);
    }
 }

 int main(){
    int x, y;
    printf("Digite o valor de x: ");
    scanf("%d", &x);
    printf("Digite o valor de y: ");
    scanf("%d", &y);
    calc(x,y);
    return 0;
 }
