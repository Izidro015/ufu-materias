#include <stdlib.h>
#include <stdio.h>
#include "TAD.h"


typedef struct fila{
    int inicio,fim,qtd;
    int valores[MAX];
}Fila;

Fila *criar(){
    Fila *f =(Fila*)malloc(sizeof(Fila));
    f->inicio = 0;
    f->fim=0;
    f->qtd=0;
    return f;
}
void apagar(Fila *f){
    free(f);
    f = NULL;
}

void zerar(Fila *f){
    if(f != NULL){
        f->inicio = 0;
        f->fim = 0;
        f->qtd = 0;
    }

}

int inserir(Fila *f, int it){
    if (f==NULL) return 2;
    if (filaCheia(f)==0) return 1;
    f->valores[f->fim]=it;
    f->fim=(f->fim+1)%MAX;
    f->qtd++;
    return 0;
}

int remover(Fila *f){
    if(f == NULL) return 2;
    if(filaVazia(f)==0) return 1;
    f->qtd--;
    f->inicio=(f->inicio+1)%MAX;
    return 0;
}

int consultar(Fila *f, int *it){
    if(f==NULL) return 2;
    if(filaVazia(f)==0)return 1;
    *it=f->valores[f->inicio];
    return 0;
}

int tamanho(Fila *f){
    if(f==NULL) return -1;
    return f->qtd;
}

int filaVazia(Fila *f){
    if(f==NULL)return 2;
    if(f->qtd==0)return 0;
    else return 1;
}

int filaCheia(Fila *f){
    if(f==NULL)return 2;
    if(f->qtd==MAX)return 0;
    else return 1;
}

void mostrar(Fila *f){
    if (f != NULL){
    printf("\n[");
    int i = f->inicio;
    int q = f->qtd;
    while(q>0){
        printf(" %d ",f->valores[i]);
        i=(i+1)%MAX;
        q--;
    }
    printf("]\n");
    }
}

int intercalaFila(Fila *f1,Fila *f2,Fila *f3){
    if(f1==NULL) return f2;
    if(f2==NULL) return f1;
    int q=f1->qtd;
    int q2=f2->qtd;
    int q3=q+q2;
    int i=(f1->inicio);
    int i2=(f2->inicio);
    if(f1==NULL || f2==NULL)return 1;
    if(q3>MAX)return 1;
    while(q3>0){
        if(q>0){
           inserir(f3,f1->valores[i]);
        }
        if(q2>0){
           inserir(f3,f2->valores[i]);
        }
        i=(i+1)%MAX;
        i2=(i2+1)%MAX;
        q--;
        q2--;
        q3--;
    }
    return 0;
}

int remover_negativos(Fila *f){
    if(f == NULL) return -2;
    if(filaVazia(f)==0) return -1;
    int num;
    int q=tamanho(f);
    while (q>0){
        remover2(f, &num);
        if(num >= 0) inserir(f, num);
        q--;
    }
    return 0;
}

int remover2(Fila *f, int *retorno){
    if(f == NULL) return 2;
    if(filaVazia(f)==0) return 1;
    *retorno = f->valores[f->inicio];
    f->qtd--;
    f->inicio=(f->inicio+1)%MAX;
    return 0;
}

int atendimento(Fila *f){
    if(f == NULL) return 2;
    if(filaVazia(f)==0) return 1;
    int senha;
    for(senha=1;senha<f->qtd;senha++){
        f->inicio=senha;
    }
    return senha;
}

int altera_string(char *nome){
    int valor = 0;
    for (int i = 0; nome[i] != '\0'; i++) {
        valor += (int)nome[i];
    }
    return valor;
}
