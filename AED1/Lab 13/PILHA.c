#include <stdio.h>
#include <stdlib.h>
#include "TAD.h"

typedef struct no {
    int valor;
    struct no *prox;
}No;

typedef struct pilha {
    No *topo;
}Pilha;

Pilha *criar() {
    Pilha *p = (Pilha *)malloc(sizeof(Pilha));
    p->topo = NULL;
return p;
}

void limpar(Pilha *p) {
    if (p == NULL) return;
    while (pilhaVazia(p)!=0) pop(p,NULL);
    free(p);
    p = NULL;
}

int push(Pilha *p, int it){
    if (p == NULL) return 2;
    No *no = (No *)malloc(sizeof(No));
    no->valor = it;
    no->prox = p->topo;
    p->topo = no;
    return 0;
}

int pop(Pilha *p, int *num){
    if (p == NULL) return 2;
    if (pilhaVazia(p) == 0)return 1;
    No *temp = p->topo;
    *num=temp->valor;
    p->topo = temp->prox;
    free(temp);
    return 0;
}

int consultar(Pilha *p, int *it){
    if (p == NULL) return 2;
    if (pilhaVazia(p) == 0)return 1;
    No *temp = p->topo;
    *it = temp->valor;
    return 0;
}

int tamanho(Pilha *p){
    if (p == NULL) return-1;
    int ct = 0;
    No *no = p->topo;
    while (no != NULL){
        ct++;
        no = no->prox;
    }
    return ct;
}

int pilhaVazia(Pilha *p){
    if (p == NULL) return 2;
    if (p->topo == NULL) return 0;
    else return 1;
}
int pilhaCheia(Pilha *p){
    return 1;
}

void mostrar(Pilha *p){
    if (p != NULL){
    printf("[");
    No *no = p->topo;
    while (no != NULL){
        printf(" %d ", no->valor);
        no = no->prox;
    }
    printf("]\n");
    }
}

int compare(Pilha *p1, Pilha *p2){
    if((p1==NULL)||(p2==NULL))return 3;
    if(tamanho(p1)!=tamanho(p2))return 2;
    while(pilhaVazia(p1)!=0){
        char conteudoP1, conteudoP2;
        pop(p1,&conteudoP1);
        pop(p2,&conteudoP2);
        if(conteudoP1!=conteudoP2)return 1;
    }
    return 0;
}

int testar(char *str){

    char *p=str;
    int n;

    Pilha *parenteses = criar(500);
    Pilha *colchetes = criar(500);
    Pilha *chaves = criar(500);

    for(int i=0; i<500; i++){
        if(*p == '\0') break;
        switch(*p){
            case '(':
                n = push(parenteses, 1);
                break;
            case '[':
                n = push(colchetes, 1);
                break;
            case '{':
                n = push(chaves, 1);
                break;
            case ')':
                n = pop(parenteses,0);
                break;
            case ']':
                n = pop(colchetes,0);
                break;
            case '}':
                n = pop(chaves,0);
                break;
        }
        p++;
        if(n != 0) return 1;
    }
    if(pilhaVazia(parenteses) != 0) return 1;
    if(pilhaVazia(colchetes) != 0) return 1;
    if(pilhaVazia(chaves) != 0) return 1;
    return 0;
}


/*void decimalParaBinario(Pilha *p, int num) {
    if(pilhaVazia(p)==NULL) return 2;
    if (numero == 0) {
        printf("O numero em binario é: 0");
        return;
    }
    int binario[32]; // Array para armazenar os dígitos binários
    int i = 0;
    while (numero > 0) {
        binario[i] = numero % 2;
        numero = numero / 2;
        i++;
    }
    printf("O numero em binario eh: ");
    for (int j = i - 1; j >= 0; j--) {
        printf("%d", binario[j]);
    }
}

int main() {
    int numero;
    printf("Digite um numero inteiro: ");
    scanf("%d", &numero);
    decimalParaBinario(numero);
    return 0;
}

void decimaBinario(Pilha *p, int *num);*/
