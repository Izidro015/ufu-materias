#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct No{
    struct No *prox;
    Aluno valor;
}No;

struct lista{
    No *fim;
};

Lista *criar(){
    Lista *l=(Lista*) malloc (sizeof(Lista));
    l->fim=NULL;
    return l;
}

void limpar(Lista *l){
    while(listavazia(l) != 0){
        removerinicio(l);
    }
    free(l);
    l=NULL;
}

int tamanho(Lista *l){
    if (l == NULL){
        return -1;
    }
    if(listavazia(l) == 0){
        return 0;
    }
    No *nolista = l->fim;
    int cont = 0;
    do{
        cont ++;
        nolista = nolista->prox;
    }while(nolista != l->fim);
    return cont;
}

void mostrar(Lista *l){
    if (l != NULL){
        printf("[");
        if(listavazia(l) != 0){
            No *nolista = l->fim;
            do{
                printf(" {%d, ", nolista->valor.mat);
                printf("%s, ", nolista->valor.nome);
                printf("%.2f} ", nolista->valor.n1);
                nolista = nolista->prox;
            }while(nolista != l->fim);
        }
        printf("]\n");
    }
}

int listavazia(Lista *l){
    if (l == NULL){
        return 2;
    }
    if(l->fim == NULL){
        return 0;
    }else{
        return 1;
    }
}

int listacheia(Lista *l){
    return 1;
}

int inserirfim(Lista *l, Aluno it){
    if (l == NULL) return 2;
    No *no = (No*) malloc (sizeof(No));
    no->valor = it;
    if(listavazia(l) == 0){
        l->fim = no;
        no->prox = no;
    }else{
        no->prox = l->fim->prox;
        l->fim->prox = no;
    }
    return 0;
}

int inseririnicio(Lista *l, Aluno it){
    if (l == NULL) return 2;
    No *no = (No*) malloc (sizeof(No));
    no->valor = it;
    if(listavazia(l) == 0){
        l->fim = no;
        no->prox = no;
    }else{
        no->prox = l->fim->prox;
        l->fim->prox = no;
    }
    return 0;
}

int removerfim(Lista *l){
    if (l == NULL) return 2;
    if(listavazia(l) == 0) return 1;
    if(l->fim->prox == l->fim){
        free(l->fim);
        l->fim = NULL;
        return 0;
    }
    No *noaux = l->fim->prox;
    No *no = noaux->prox;
    l->fim->prox = no;
    free (noaux);
    return 0;
}

int inserirposicao(Lista *l,Aluno it,int pos){
    if(l == NULL) return 2;
    int p = 1, tam = tamanho(l);
    No *no = (No*)malloc(sizeof(No));
    no->valor = it;
    No *nolista = l->fim->prox;
    No *noaux = l->fim->prox;
    if(listavazia(l) == 0){
        l->fim = no;
        no->prox=no;
        return 0;
    }if(pos == 1){
        inseririnicio(l,it);
        return 0;
    }if(pos == tam){
        inserirfim(l,it);
        return 0;
    }while(nolista != l->fim || p==pos){
        noaux = nolista;
        nolista = nolista->prox;
        p++;
    }
    no->prox = nolista;
    noaux->prox = no;
    return 0;
}

int removerinicio(Lista *l){
    if (l == NULL) return 2;
    if (listavazia(l) == 0) return 1;
    if (l->fim->prox == l->fim){
        free(l->fim);
        l->fim = NULL;
        return 0;
    }
    No *no = l->fim;
    No *noaux = l->fim->prox;
    while (noaux->prox != l->fim){
        noaux = noaux->prox;
    }
    noaux->prox = l->fim->prox;
    free(l->fim);
    l->fim = noaux;
    return 0;
}

int removerposicao(Lista *l, int pos){
    if (l == NULL) return 2;
    if (listavazia(l) == 0) return 1;
    int tam = tamanho(l);
    if (pos < 1 || pos > tam){
        return 1;
    }if (pos == 1){
        removerinicio(l);
        return 0;
    }if (pos == tam){
        removerfim(l);
        return 0;
    }
    No *no = l->fim;
    No *noaux = l->fim->prox;
    int p = 1;
    while (p < pos){
        noaux = no;
        no = no->prox;
        p++;
    }
    noaux->prox = no->prox;
    free(no);
    return 0;
}

int removeritem(Lista *l, int it){
    if (l == NULL) return 2;
    int p = 1;
    No *no = l->fim->prox;
    while (no != l->fim){
        if (no->valor.mat == it){
            removerposicao(l, p);
        }
        no = no->prox;
        p++;
    }
    return 0;
}

int buscaritem(Lista *l, int chave, Aluno *it){
    if (l == NULL) return 2;
    No *no = l->fim->prox;
    while (no != l->fim){
        if (no->valor.mat == chave){
            *it = no->valor;
            return 0;
        }
        no = no->prox;
    }
    return -1;
}

int buscarposicao(Lista *l, int pos, int *it){
    if (l == NULL) return 2;
    No *no = l->fim->prox;
    int p = 1;
    while (no != l->fim){
        if (p == pos){
            *it = no->valor.mat;
            return 0;
        }
        no = no->prox;
        p++;
    }
    return -1;
}

int removercentral(Lista *l){
    if(l == NULL) return 2;
    int tam, tamanhomeio;
    tam = tamanho(l);
    if(tam == 1){
        removerinicio(l);
    }
    tamanhomeio = tam/2;
    removerposicao(l,tamanhomeio);
    return 0;
}

Lista *interseccao(Lista *l1, Lista *l2){
    Lista *resultado = criar();
    No* nolista1 = l1->fim->prox;
    while (nolista1 != l1->fim){
        No* nolista2 = l2->fim->prox;
        while (nolista2 != l2->fim){
            if (nolista1->valor.mat == nolista2->valor.mat){
                inseririnicio(resultado, nolista1->valor);
                break;
            }
            nolista2 = nolista2->prox;
        }
        nolista1 = nolista1->prox;
    }
    return resultado;
}

int contaOcorrencias(Lista *l, Aluno it){
    if (l == NULL) return 2;
    int cont = 0;
    No *nolista = l->fim->prox;
        while(nolista != l->fim){
            if (nolista->valor.mat == it.mat){
                cont++;
            }
            nolista = nolista->prox;
        }
        return cont;
}

int inserirfimII(Lista *l, Aluno it){
    if (l == NULL) return 2;
    int meajudapeloamordedeus = contaOcorrencias(l, it);
    if(listavazia(l) == 0) return 1;
    if((meajudapeloamordedeus) >= 1){
        return -1;
    }else{
        inserirfim(l, it);
        return 0;
    }
}
