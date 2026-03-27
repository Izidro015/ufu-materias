#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "string.h"

int main(){
    int tamanho, count, caracter;
    printf("\nBem vindo ao programa de manipulacao de string.");
    manipulastring *s = criar();
    associa(s);
    tamanho = calculatamanho(s);
    printf("\nO tamanho da string eh: %d", tamanho);
    printf("\nDigite um caractere para procurar na string: ");
    scanf(" %c", &caracter);
    count = contagem(s, caracter);
    printf("\nO caracter desejado apareceu %d vezes", count);
    exibe(s);
    return 0;
}
