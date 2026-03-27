#ifndef TAD2_H_INCLUDED
#define TAD2_H_INCLUDED

typedef struct aluno {
    int mat;
    char nome[30];
    float n1;
} aluno;

typedef struct lista lista;

lista *criar(int capacidade_maxima);

void limpar(lista *l);

int inseririnicio(lista *l, aluno it);

void leraluno(aluno *it);

int inserirfim(lista *l, aluno it);

int inserirposicao(lista *l, aluno it, int pos);

int removerinicio(lista *l);

int removerfim(lista *l);

int removerposicao(lista *l, int pos);

int removeritem(lista *l, aluno it);

int buscaritemchave(lista *l, int chave, aluno *retorno);

int buscarposicao(lista *l, int posicao, aluno *it);

int listavazia(lista *l);

int listacheia(lista *l);

int tamanho(lista *l);

void mostrar (lista *l);

int contemitem(lista *l, aluno *it);

lista* reversa(lista *l);

int contaitem(lista *l, aluno *it);

#endif // TAD2_H_INCLUDED
