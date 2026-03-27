#include <stdio.h>

/*b) Faça um programa que receba o ano de nascimento de uma pessoa e o ano atual, calcule e mostre a idade desta
pessoa, e quantos anos essa pessoa terá em 2030.*/

int main(){
    int ano_nasc,ano_atual,idade,idade_fut;
    printf("Digite o seu ano de nascimento: ");
    scanf("%d",&ano_nasc);
    printf("Digite o ano atual: ");
    scanf("%d",&ano_atual);
    idade=ano_atual-ano_nasc;
    idade_fut=2030-ano_nasc;
    printf("Sua idade: %d\nVoce tera %d anos em 2030", idade,idade_fut);
    return 0;
}
