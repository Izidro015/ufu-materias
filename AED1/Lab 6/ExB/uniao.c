#include "uniao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct conjunto{
    int *vet;
    int tamanho;
};
typedef conjunto conjunto;

conjunto *criar(){
    conjunto *c=(conjunto *) malloc(sizeof(conjunto));
    return c;
}

void membro(conjunto *c){
    int aux, i=0, k, jorge;
    c->vet=(int *)calloc(1, sizeof(int));
    c->tamanho=0;
    while (1){
        printf("\nDigite um valor para o vetor (Digite negativo para parar): ");
        scanf("%d", &aux);
        if (aux<0){
            break;
        }
        jorge=0;
        for(k=0;k<i;k++){
            if(c->vet[k]==aux){
                jorge=1;
                break;
            }
        }
        if(jorge==0&&aux >= 0){
            c->tamanho++;
            c->vet = (int *)realloc(c->vet, c->tamanho * sizeof(int));
            c->vet[i] = aux;
            i++;
        }
    }
}

void inserir(conjunto *c){
    int opcao;
    while (1)
    {
        printf("\nGostaria de inserir valores novos? Digite 1 para sim, qualquer coisa para nao. ");
        scanf("%d", &opcao);

        if(opcao == 1)
        {
            c->tamanho++;
            c->vet = (int*)realloc(c->vet, c->tamanho * sizeof(int));

            printf("\nDigite o valor que deseja inserir: ");
            scanf("%d", &(c->vet[c->tamanho - 1]));
        }
        else
        {
            break;
        }
    }
}


void remover(conjunto *c){
    int opcao, i, j, valor;
    while (1){
        printf("\nGostaria de remover algum valor? Digite 1 para sim, qualquer coisa para nao. ");
        scanf("%d", &opcao);
        if (opcao != 1){
            break;
        }
        printf("\nDigite o valor que gostaria de remover: ");
        scanf("%d", &valor);
        for (i = 0; i < c->tamanho; i++){
            if (c->vet[i] == valor){
               for (j = i; j < c->tamanho - 1; j++){
                   c->vet[j] = c->vet[j + 1];
               }
               c->tamanho--;
               c->vet = (int*) realloc (c->vet, c->tamanho * sizeof(int));
               i--;
            }
        }
    }
}

conjunto *uniao(conjunto *c1, conjunto *c2){
    int i, j;
    conjunto *u=criar();
    u->tamanho=0;
    u->vet=(int *)malloc(u->tamanho * sizeof(int));
    for(i = 0; i < c1->tamanho; i++){
        int elemento=c1->vet[i];
        int duplicado=0;
        for(j = 0; j < u->tamanho; j++){
            if(u->vet[j] == elemento){
                duplicado = 1;
                break;
            }
        }
        if (!duplicado){
            u->tamanho++;
            u->vet = (int *)realloc(u->vet, u->tamanho * sizeof(int));
            u->vet[u->tamanho - 1]=elemento;
        }
    }
    for(int i = 0; i < c2->tamanho; i++){
        int elemento = c2->vet[i];
        int duplicado = 0;
        for(int j = 0; j < u->tamanho; j++){
            if (u->vet[j] == elemento){
                duplicado = 1;
                break;
            }
        }
        if(!duplicado){
            u->tamanho++;
            u->vet = (int *)realloc(u->vet, u->tamanho * sizeof(int));
            u->vet[u->tamanho - 1] = elemento;
        }
    }
    return u;
}

conjunto *interseccao(conjunto *c1, conjunto *c2){
    conjunto *isc = criar();
    isc->tamanho = 0;
    for (int i = 0; i < c1->tamanho; i++){
        int elemento = c1->vet[i];
        for (int j = 0; j < c2->tamanho; j++){
            if (c2->vet[j] == elemento){
                isc->tamanho++;
                isc->vet = (int *)realloc(isc->vet, isc->tamanho * sizeof(int));
                isc->vet[isc->tamanho - 1] = elemento;
                break;
            }
        }
    }
    return isc;
}

conjunto *diferenca(conjunto *c1, conjunto *c2){
    conjunto *d = criar();
    d->tamanho = 0;
    for (int i = 0; i < c1->tamanho; i++){
        int elemento = c1->vet[i];
        int verifica_c2 = 0;
        for (int j = 0; j < c2->tamanho; j++){
            if (c2->vet[j] == elemento){
                verifica_c2 = 1;
                break;
            }
        }
        if (!verifica_c2){
            d->tamanho++;
            d->vet = (int *)realloc(d->vet, d->tamanho * sizeof(int));
            d->vet[d->tamanho - 1] = elemento;
        }
    }
    return d;
}

void exibe(conjunto *c){
    int i;
    printf("\nVetor: [");
    for (i = 0; i < c->tamanho; i++){
        printf(" %d ", c->vet[i]);
    }
    printf("]");
}
