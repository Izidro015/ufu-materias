#ifndef TAD_H_INCLUDED
#define TAD_H_INCLUDED
#define MAX 100

typedef struct no *lista;

lista *criar();

int listavazia(lista *l);

int inseririnicio(lista *l,int num);

int inserirfim(lista *l,int it);

void mostrar(lista *l);

int recursaoA(lista *encadeada, int *num);

int soma(lista *l);

void inverte(lista *l);

int removeint(lista *l, int num);

int incrementa(lista *l);

#endif // TAD_H_INCLUDED
