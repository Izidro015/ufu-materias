#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

typedef struct aluno{
    int mat;
    char nom[30];
    float n1;
} aluno;

typedef struct lista Lista;

Lista *criar();
void limpar(Lista *l);
int insereIni(Lista *l, Aluno input);
int insereFim(Lista *l, Aluno input);
int inserePos(Lista *l, Aluno input, int pos);
int removeIni(Lista *l);
int removeEnd(Lista *l);
int removePos(Lista *l, int pos);
int removeItem(Lista *l, Aluno input);
int itemChave(Lista *l, int key, Aluno *out);
int prucuraPos(Lista *l, int pos, Aluno *out);
int listaVazia(Lista *l);
int listaCheia(Lista *l);
int tamanho(Lista *l);
void mostrar(Lista *l);

#endif // LISTA_H_INCLUDED
