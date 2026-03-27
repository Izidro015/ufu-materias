#ifndef IMPLET2_H_INCLUDED
#define IMPLET2_H_INCLUDED

#define MAX 100

typedef struct aluno
{
	int mat;
	char nome[30];
	float n1;
}aluno;

typedef struct lista lista;

lista *criar();

void limpar(lista *l);

int inseririnicio(lista *l, aluno it);

void leraluno(aluno *it);

int inserirfim(lista *l, aluno it);

int inserirposicao(lista *l, aluno it, int pos);

int removerinicio(lista *l);

int removerfim(lista *l);

#endif // IMPLET2_H_INCLUDED
