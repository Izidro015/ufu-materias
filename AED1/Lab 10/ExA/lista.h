#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

typedef struct aluno{
    int mat;
    char nome[30];
    float nota;
} aluno;

typedef struct lista Lista;

Lista *criar ();
int listavazia(Lista *l);
int cadastraraluno(Lista *l, aluno a);
int removeraluno(Lista *l, int matricula);
void listarcadastrados(Lista *l);
int maiornota(Lista *l, aluno *a);
void limparlista (Lista *l);
int trocaposicao(Lista *l, int pos1, int pos2);
int analisa_listas (Lista *la, Lista *lb);
int tirarepetido(Lista *l);
int tamanho (Lista *l);

#endif // LISTA_H_INCLUDED
