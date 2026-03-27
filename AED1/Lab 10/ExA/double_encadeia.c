#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

typedef struct No{
    aluno valor;
    struct No *prox;
    struct No *ant;
}No;

typedef struct lista{
    No *inicio;
}Lista;

Lista *criar (){
    Lista *l = (Lista *) malloc (sizeof(Lista));
    l->inicio = NULL;
    return l;
}

int listavazia(Lista *l){
    if (l == NULL) return 2;
    if (l->inicio == NULL)
        return 0;
    else
        return 1;
}

int cadastraraluno(Lista *l, aluno a){
    if (l == NULL) return 2;
    No *n = (No *) malloc (sizeof(No));
    n->valor = a;
    n->prox = NULL;
    n->ant = NULL;
    if (l->inicio == NULL){
        l->inicio = n;
        return 0;
    }
    No *nolista = l->inicio;
    if (a.mat < nolista->valor.mat){
        n->prox = nolista;
        nolista->ant = n;
        l->inicio = n;
        return 0;
    }
    while (nolista->prox != NULL){
        if (a.mat > nolista->prox->valor.mat){
            nolista = nolista->prox;
        }else{
            n->prox = nolista->prox;
            n->ant = nolista;
            nolista->prox->ant = n;
            nolista->prox = n;
            return 0;
        }
    }
    nolista->prox = n;
    n->ant = nolista;
    return 0;
}

int removeraluno(Lista *l, int matricula){
    if (l == NULL) return 2;
    if(listavazia(l) == 0) return 1;
    No *nolista = l->inicio;
    while(nolista->prox != NULL){
        if(matricula == nolista->valor.mat){
            nolista->prox->ant = nolista->ant;
            nolista->ant->prox = nolista->prox;
            free(nolista);
            return 0;
        }
        nolista = nolista->prox;
    }
    return 1;
}

void listarcadastrados(Lista *l){
    if (listavazia(l) != 0){
        No *nolista = l->inicio;
        while (nolista != NULL){
            printf("\nNome: %s", nolista->valor.nome);
            printf("\nMatricula: %d", nolista->valor.mat);
            printf("\nNota: %.2f\n", nolista->valor.nota);
            nolista = nolista->prox;
        }
    }else{
        printf("A lista de alunos cadastrados está vazia.\n");
    }
}

int maiornota(Lista *l, aluno *a){
    if (l == NULL) return 2;
    if (listavazia(l) == 0) return 1;
    No *nolista = l->inicio;
    aluno maior = nolista->valor;
    while(nolista->prox != NULL){
        if(nolista->valor.nota > maior.nota){
            maior = nolista->valor;
        }
        nolista = nolista->prox;
    }
    *a = maior;
    return 0;
}

void limparlista (Lista *l){
    while (listavazia (l) != 0){
        No *nolista = l->inicio;
        l->inicio = nolista->prox;
        if (l->inicio != NULL)
            l->inicio->ant = NULL;
        free(nolista);
    }
}

int trocaposicao(Lista *l, int pos1, int pos2){
    int p1 = 0, p2 = 0;
    if (l == NULL) return 2;
    if (listavazia(l) == 0) return 1;
    if (pos1 < 0 || pos2 < 0) return 1;
    No *nolista1 = l->inicio;
    while (nolista1->prox != NULL && p1 > 0){
        nolista1 = nolista1->prox;
        p1--;
    }
    No *nolista2 = l->inicio;
    while (nolista2->prox != NULL && p2 > 0){
        nolista2 = nolista2->prox;
        p2--;
    }
    if (nolista1 == NULL || nolista2 == NULL) return 1;
    aluno temp = nolista1->valor;
    nolista1->valor = nolista2->valor;
    nolista2->valor = temp;
    return 0;
}

int analisa_listas (Lista *la, Lista *lb){
    if ((la == NULL) || (lb == NULL))
        return 2;
    if ((listavazia(la) == 0) || (listavazia(lb) == 0))
        return 3;
    int tam_a = tamanho (la), tam_b = tamanho (lb);
    int mat_a[tam_a], mat_b[tam_b];
    int rep_a[tam_a], rep_b[tam_b];
    Lista *temp1 = la;
    Lista *temp2 = lb;
    No *na = temp1->inicio;
    No *nb = temp2->inicio;
    No *aux = (No *) malloc (sizeof(No));
    int i, j, k;
    for (i = 0; i < tam_a; i++){
        mat_a[i] = na->valor.mat;
        rep_a[i] = 0;
        aux = na->prox;
        while (aux != NULL){
            if (mat_a[i] == na->valor.mat){
                rep_a[i]++;
                k = removeraluno (temp1, mat_a[i]);
                if (k != 0) return -1;
            }
            aux = aux->prox;
        }
        na = na->prox;
    }
    free (temp1);
    for (i = 0; i < tam_b; i++){
        mat_b[i] = nb->valor.mat;
        rep_b[i] = 0;
        aux = nb->prox;
        while (aux != NULL){
            if (mat_b[i] == nb->valor.mat){
                rep_b[i]++;
                k = removeraluno (temp2, mat_b[i]);
                if (k != 0) return -1;
            }
            aux = aux->prox;
        }
        nb = nb->prox;
    }
    free (temp2);
    int flag;
    for (i = 0; i < tam_a; i++){
        flag = 0;
        for (j = 0; j < tam_b; j++){
            if (mat_a[i] == mat_b[j]){
                flag = 1;
                if (rep_a[i] != rep_b[j]) return 1;
            }
        }
        if (flag == 0) return 1;
    }
    return 0;
}

int tirarepetido(Lista *l){
    if (l == NULL) return 2;
    if (listavazia(l) == 0) return 1;
    No *nolista = l->inicio;
    while(nolista->prox != NULL){
        No *noaux = nolista->prox;
        while(noaux->prox != NULL){
            if(nolista->valor.mat == noaux->valor.mat){
                removeraluno(l, noaux->valor.mat);
            }
            noaux = noaux->prox;
        }
        nolista = nolista->prox;
    }
    return 0;
}

int tamanho (Lista *l){
    if (l == NULL) return 2;
    int cont = 0;
    No *nolista = l->inicio;
    while(nolista != NULL){
        nolista = nolista->prox;
        cont++;
    }
    return cont;
}
