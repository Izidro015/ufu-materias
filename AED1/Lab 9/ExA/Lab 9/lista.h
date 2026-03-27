#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#define MAX 100

typedef struct aluno{
    int mat;
    char nome[30];
    float n1;
}Aluno;
typedef struct lista Lista;

Lista *criar();
void limpar(Lista *l);
int tamanho(Lista *l);
void mostrar(Lista *l);
int listavazia(Lista *l);
int listacheia(Lista *l);
int inserirfim(Lista *l, Aluno it);
int inseririnicio(Lista *l, Aluno it);
int removerfim(Lista *l);
int inserirposicao(Lista *l,Aluno it,int pos);
int removerinicio(Lista *l);
int removerposicao(Lista *l, int pos);
int removeritem(Lista *l, int it);
int buscaritem(Lista *l, int chave, Aluno *it);
int buscarposicao(Lista *l, int pos, int *it);
int removercentral(Lista *l);
Lista *interseccao(Lista *l1, Lista *l2);
int contaOcorrencias(Lista *l, Aluno it);
int inserirfimII(Lista *l, Aluno it);


#endif // LISTA_H_INCLUDED
