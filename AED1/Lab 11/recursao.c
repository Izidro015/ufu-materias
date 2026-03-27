#include <stdio.h>
#include <stdlib.h>
#include "TAD.h"

typedef struct no{
    int valor;
    struct no *prox;
}no;

lista *criar(){
    lista *l;
    l = (lista *) malloc (sizeof(lista));
    *l = NULL;
    return l;
}

int listavazia (lista *l){
    if (l == NULL)
        return 2;   //lista não alocada
    if (*l == NULL)
        return 0;   //lista vazia
    return 1;       //lista não vazia
}

int inseririnicio (lista *l, int valor){
    if (l == NULL)return 2;   //lista não alocada
    no *n = (no *) malloc (sizeof(no));
    n->valor = valor;
    n->prox = *l;
    *l = n;
    return 0;
}

int inserirfim(lista *l,int it){
    if(l==NULL)
        return 2;
    if(listavazia(l)==0)
        return inseririnicio(l,it);
    no *nolista = *l;
    while(nolista->prox  != NULL)
        nolista = nolista->prox;
    no *n=(no*)malloc(sizeof(no));
    n->valor = it;
    n->prox = nolista->prox;
    nolista->prox = n;
    return 0;
}

void mostrar(lista *l){
    if(l!=NULL){
        no *nolista = *l;
        while(nolista != NULL){
                printf("%d",nolista->valor);
                nolista = nolista->prox;
        }
    }
}

int recursaoA(lista *l, int *num){//ultimo elemento
    if(*l == NULL) return 2;
    if((*l)->prox == NULL){//o ultimo elemento for o ultimo
        *num=(*l)->valor;
        return 0;
    }else{
        return recursaoA(&((*l)->prox), num);//se nao for o ultimo
    }
}

int soma(lista *l){//retorna a soma
    if(listavazia(l)==0) return 0;//verifica se eh vazia
    return (*l)->valor + soma(&((*l)->prox));//pega o primeiro no da lista e soma com o proximo
}

void inverte(lista *l){//ordem reversa dos elementos
    if(listavazia(l)!=0){
        inverte(&((*l)->prox));
        printf("%d", (*l)->valor);//1,2,3 pra ele chegar no 3 ele tem que passar pelo 1 e 2, e dps faz esse processo pelo 2 e 1 e finalizando no 0
    }
}

int removeint(lista *l, int num){
    if(listavazia(l)==0) return 0;
    if(num==((*l)->valor)){
        no*temp=*l;
        *l=(*l)->prox;//como o numero é igual, tem que remover o igual e não perder o resto da lista
        free(temp);
        return removeint(l, num); //pega o proximo elemento e confere se eh = a num
    }else{
        return removeint(&((*l)->prox),num);
    }return 1;
}

int incrementa(lista *l){
    if(*l == NULL) return inserirfim(l,1);
    (*l)->valor++;
    if((*l)->valor == 2){
        (*l)->valor = 0;
        return incrementa(&((*l)->prox));
    }
    return 0;
}
