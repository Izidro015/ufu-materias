#ifndef TAD_H_INCLUDED
#define TAD_H_INCLUDED

typedef struct matriz matriz;

matriz *criar();

void destruir(matriz *m);

void atribuir(matriz *m, int linha, int coluna);

float elemento(matriz *m, int linha, int coluna);

int retorna_linhas(matriz *m);

int retorna_colunas(matriz *m);

void aleatorio(matriz *m, float minimo, float maximo);

matriz* soma(matriz *m, matriz *n);

void exibe(matriz *m);

#endif // TAD_H_INCLUDED
