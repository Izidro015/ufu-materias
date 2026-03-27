#ifndef TAD_H_INCLUDED
#define TAD_H_INCLUDED
#define MAX 100

typedef struct fila Fila;

Fila *criar();

void apagar(Fila *f);

int inserir(Fila *f, int it);

int remover(Fila *f);

int remover2(Fila *f, int *valor);

int consultar(Fila *f, int *it);

int tamanho(Fila *f);

int filaVazia(Fila *f);

int filaCheia(Fila *f);

int intercalaFila(Fila *f1,Fila *f2,Fila *f3);

int remover_negativos(Fila *f);

int atendimento(Fila *f);

int altera_string(char *nome);

#endif // TAD_H_INCLUDED
