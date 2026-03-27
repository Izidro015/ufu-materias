#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

typedef struct aluno{
    int mat;
    char nome[30];
    float n1;
}Aluno;

typedef struct lista Lista;

Lista *criar();

void limpar (Lista *l);
int inserirInicio (Lista *l,struct aluno it);
int inserirFim (Lista *l,struct aluno it);
int inserirPosicao( Lista *l,struct aluno it,int pos);
int removerItem (Lista *l,int it);
int buscarItemChave (Lista *l, int chave struct aluno *retorno);
int buscarPosicao (Lista *l,int posicao,int *retorno);
int listaVazia (Lista *l);
int listaCheia (Lista *l);
int tamanho (Lista *l);
void mostrar (Lista *l);

#endif // LISTA_H_INCLUDED
