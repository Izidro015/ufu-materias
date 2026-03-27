#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uniao.h"

int main(){
    printf("\nBem vindo ao programa de manipulacao de conjunto.");
    printf("\nCrie o conjunto 1: ");
    conjunto *c1, *c2, *u, *i, *d;
    c1 = criar();
    membro(c1);
    exibe(c1);
    inserir(c1);
    exibe(c1);
    remover(c1);
    exibe(c1);
    printf("\nCrie o conjunto 2: ");
    c2 = criar();
    membro(c2);
    exibe(c2);
    inserir(c2);
    exibe(c2);
    remover(c2);
    exibe(c2);
    printf("\nOperacoes: ");
    u = uniao(c1, c2);
    printf("\n Uniao: ");
    exibe(u);
    i = interseccao(c1, c2);
    printf("\n Interseccao: ");
    exibe(i);
    d = diferenca(c1, c2);
    printf("\n Diferenca: ");
    exibe(d);
    free (c1);
    free (c2);
    free (u);
    free (i);
    free (d);
    return 0;
}
