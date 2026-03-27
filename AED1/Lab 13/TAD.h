#ifndef TAD_H_INCLUDED
#define TAD_H_INCLUDED
#define MAX 100


typedef struct pilha Pilha;

Pilha *criar();

void limpar(Pilha *p);

int push(Pilha *p, int num);

int pop(Pilha *p, int *num);

int consultar(Pilha *p, int *num);

int tamanho(Pilha *p);

int pilhaVazia(Pilha *p);

int pilhaCheia(Pilha *p);

void mostrar(Pilha *p);

int compare(Pilha *p1, Pilha *p2);

#endif // TAD_H_INCLUDED
