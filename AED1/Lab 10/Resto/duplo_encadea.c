#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

typedef struct no{
    aln index;
    no *ant, *prox;
} No;

typedef struct lista{
    no *inicio;
} Lista;

Lista *criar(){
    Lista *l = (Lista*) calloc(1, sizeof(Lista));
    l->ini = NULL;
    return l;
}

void limpar(Lista *l){
    while(listaVazia(l) != 0){
        removeIni(l);
    }
    free(l);
    l = NULL;
}

int insereIni(list *l, aln input){
    if(l == NULL) return 2;

    no *n = (no*) calloc(1, sizeof(no));
    n->index = input;
    n->next = l->ini;
    n->prev = NULL;
    if(l->ini != NULL){
        l->ini->prev = n;
    }
    l->ini = n;
    return 0;
}

int insertEnd(list *l, aln input){
    if(l == NULL) return 2;
    if(emptyList(l) == 0) return insertIni(l, input);

    no *nlist = l->ini;

    while(nlist->next != NULL){
        nlist = nlist->next;
    }

    no *no = (no*) calloc(1, sizeof(no));
    n->index = input;
    n->next == NULL;
    no->prev = nlist;
    nlist->next = n;
    return 0;
}

int insertPos(list *l, aln input, int pos){
    if(l == NULL) return 2;
    if(emptyList(l) == 0 || pos <= 0) return insertIni(l, input);

    no *nlist = l->ini;
    while((nlist != NULL) && (pos > 0)){
        nlist = nlist->next;
        pos--;
    }
    if(nl == NULL) return insertEnd(l, input);
    else{

        no *n = (no*) calloc(sizeof(no));
        n->index = input;
        n->next = nlist;
        n->prev = nlist->prev;
        nlist->prev = n;
        n->prev->next = n;
    }
    return 0;
}

int removeIni(list *l){
    if(l == NULL) return 2;
    if(emptyList(l) == 0) return 1;

    no *nlist = l->ini;
    l->ini = nlist->next;
    if(l->ini != NULL) l->ini->prev = NULL;
    free(nlist);
    return 0;
}

int removeEnd(list *l){
    if(l == NULL) return 2;
    if(emptyList(l) == 0) return 1;

    no *nlist = l->ini;

    while(nlist->next != NULL) nlist = nlist->next;
    if(nlist->prev == NULL) l->ini = NULL;
    else nlist->prev->next = NULL;

    free(nlist);
    return 0;
}

int removePos(list *l, int pos){
    if(l == NULL) return 2;
    if(emptyList(l) == 0) return 1;

    no *nlist = l->ini;

    while((n->next != NULL) && (pos > 0)){
        nlist = nlist->next;
        pos--;
    }

    if(n->prev == NULL) return removeIni(l);
    if(n->next == NULL) return removeEnd(l);
    n->prev->next = n->next;
    n->next->prev = n->prev;

    free(n);
    return 0;
}

int removeItem(list *l, aln input){
    if(l == NULL) return 2;
    if(emptyList(l) == 0) return 1;

    no *nlist = l->ini;
    int i = 0;

    while((nlist != NULL) && (input.mat != nlist->index.mat)){
        nlist = nlist->next;
        i++;
    }

    if(nlist == NULL) return -1;
    else return removePos(l, i);
}

int searchKey(list *l, int key, aln *out){
    no *nlist = l->ini;

    if(l == NULL) return 2;
    while(nlist != NULL){
        if(nlist->index.mat == key){
            *out = nlist->index;
            return 0;
        }
        nlist = nlist->next;
    }

    return 1;
}

int searchPos(list *l, int pos, aln *out){
    no *nlist = l->ini;
    if(l == NULL) return 2;
    if(emptyList(l) == 0) return 1;
    while((nlist->next != NULL) && (pos > 0)){
        nlist = nlist->next;
        pos--;
    }
    if(pos == 0){
        *out = nlist->index;
        return 0;
    }
    else return -1;

}

int emptyList(list *l){
    if(l == NULL) return 2;
    if(l->ini == NULL) return 0;
    else return 1;
}

int fullList(list *l){
    return 1;
}

int sizeList(list *l){
    int i = 0;
    no *nlist = l->ini;
    if(l == NULL) return -2;
    if(emptyList(l) == 0) return 0;
    while(nlist->next != NULL){
        nlist = nlist->next;
        i++;
    }
    return i;
}

void displayList(list *l){
    no *nlist = l->ini;

    if(l != NULL){
        while(nlist != NULL){
            printf("[%d, %s, %.2f]\n", nlist->index.mat, nlist->index.nome, nlist->index.not);
            nlist = nlist->next;
        }
    }
}
