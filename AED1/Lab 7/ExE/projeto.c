#include "projeto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lista{
    int total;
    char str[2000];
    tad *valores;
}lista;

lista *criar(){
    lista *l = (lista*)malloc(sizeof(lista));
    if (l != NULL){
        l->valores = (tad*)malloc(sizeof(tad));
        l->total = 0;
    }
}

void leitura(lista *l){
    printf("\nDigite uma string de ate 2000 caracteres: ");
    setbuf(stdin,NULL);
    fgets(l->str, 2000, stdin);
    l->str[strcspn(l->str, "\n")] = '\0';
}

void busca(lista *l){
    int i, j, k, cont;
    for (i = 0; l->str[i] != '\0'; i++){
        char caractere;
        int flag;
        caractere = l->str[i];
        cont = 0;
        flag = 0;
        for (j = 0; j < i; j++){
            if (l->str[j] == caractere){
                flag = 1;
                break;
            }
        }
        if (flag != 1){
            for (j = i; l->str[j] != '\0'; j++){
                if (l->str[j] == caractere){
                    cont++;
                    for (k = j; l->str[k] != '\0'; k++){
                        l->str[k] = l->str[k + 1];
                    }
                    j--;
                }
            }
            l->valores[l->total].letra = caractere;
            l->valores[l->total].contagem = cont;
            l->total++;
            l->valores = (tad *)realloc(l->valores, l->total * sizeof(tad));
        }
    }
}

void exibe(lista *l){
    int i;
    for(i = 0; i < l->total; i++){
        printf("\nO caracter %c aparece %d vezes", l->valores[i].letra, l->valores[i].contagem);
    }
}

