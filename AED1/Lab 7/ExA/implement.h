#ifndef IMPLEMENT_H_INCLUDED
#define IMPLEMENT_H_INCLUDED

#define MAX 100

typedef struct aluno{
	int mat;
	char nome[30];
	float n1;
}aluno;

typedef struct lista lista;

lista *criar();

void limpar(lista *l);

void leraluno(aluno *it);

int inseririnicio(lista *l, aluno it);

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

#endif // LISTAS_H_INCLUDED
