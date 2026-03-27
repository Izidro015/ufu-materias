#include <stdio.h>
#include <stdlib.h>
#include "tad.h"

struct no
{
    aluno info;
    struct no *ant;
    struct no *prox;
};
typedef struct no no;

struct lista
{
    no *inicio;
};
typedef struct lista lista;

lista *criar ( )
{
    lista *l = (lista *) malloc (sizeof(lista));
    l->inicio = NULL;
    return l;                                         //lista criada
}

int lista_vazia (lista *l)
{
    if (l == NULL)
        return 2;                                     //lista não alocada
    if (l->inicio == NULL)
        return 0;                                     //lista vazia
    else
        return 1;                                     //lista não vazia
}

int inserir_aluno (lista *l, aluno a)
{
    if (l == NULL) return 2;                          //lista não alocada

    no *n = (no *) malloc (sizeof(no));
    n->info = a;
    n->prox = NULL;
    n->ant = NULL;

    //lista vazia
    if (l->inicio == NULL)
    {
        l->inicio = n;
        return 0;                                    //aluno inserido
    }

    no *nolista = l->inicio;

    //inicio da lista
    if (a.mat < nolista->info.mat)
    {
        n->prox = nolista;
        nolista->ant = n;
        l->inicio = n;
        return 0;                                    //aluno inserido
    }

    //meio da lista
    while (nolista->prox != NULL)
    {
        if (a.mat > nolista->prox->info.mat)
        {
            nolista = nolista->prox;
        } else {
            n->prox = nolista->prox;
            n->ant = nolista;
            nolista->prox->ant = n;
            nolista->prox = n;
            return 0;                                //aluno inserido
        }
    }

    //final da lista
    nolista->prox = n;
    n->ant = nolista;
    return 0;                                        //aluno inserido
}

int remover_aluno (lista *l, int mat)
{
    if (l == NULL) return 2;                         //lista não alocada
    if (lista_vazia (l) == 0) return 1;              //lista vazia

    no *nolista = l->inicio;

    while (nolista->prox != NULL)
    {
        if (mat == nolista->info.mat)
        {
            nolista->prox->ant = nolista->ant;
            nolista->ant->prox = nolista->prox;

            free(nolista);
            return 0;                               //aluno removido
        }

        nolista = nolista->prox;
    }

    return -2;                                      //aluno não encontrado
}

void mostrar (lista *l)
{
    if (l != NULL)
    {
        no *nolista = l->inicio;

        while (nolista != NULL)
        {
            printf("\nnome: %s", nolista->info.nome);
            printf("\nmatricula: %d", nolista->info.mat);
            printf("\nnota: %.2f\n", nolista->info.nota);

            nolista = nolista->prox;
        }
    }
}

int maior_nota (lista *l, aluno *retorno)
{
    if (l == NULL) return 2;                        //lista não alocada
    if (lista_vazia (l) == 0) return 1;             //lista vazia

    no *nolista = l->inicio;
    aluno maior = nolista->info;

    while (nolista != NULL)
    {
        if (nolista->info.nota > maior.nota)
            maior = nolista->info;

        nolista = nolista->prox;
    }

    *retorno = maior;
    return 0;                                       //aluno encontrado
}

void limpar (lista *l)
{
    while (lista_vazia (l) != 0)
    {
        no *nolista = l->inicio;
        l->inicio = nolista->prox;

        if (l->inicio != NULL)
            l->inicio->ant = NULL;
        free(nolista);
    }
}

int trocar_posicao (lista *l, int p1, int p2)
{
    if (l == NULL) return 2;                        //lista não alocada

    no *n1 = l->inicio;

    while ((n1->prox != NULL) && (p1 > 0))
    {
        n1 = n1->prox;
        p1--;
    }

    no *n2 = l->inicio;

    while ((n2->prox != NULL) && (p2 > 0))
    {
        n2 = n2->prox;
        p2--;
    }

    aluno temp;

    temp = n1->info;
    n1->info = n2->info;
    n2->info = temp;

    return 0;                                       //posições trocadas
}

int tamanho (lista *l)
{
    if (l == NULL) return 2;                        //lista não alocada

    no *nolista = l->inicio;
    int cont = 0;

    while (nolista != NULL)
    {
        nolista = nolista->prox;
        cont++;
    }

    return cont;                                    //tamanho da lista
}

int analisa_listas (lista *la, lista *lb)
{
    if ((la == NULL) || (lb == NULL))
        return 2;                                   //lista(s) não alocada(s)
    if ((lista_vazia(la) == 0) || (lista_vazia(lb) == 0))
        return 3;                                   //lista(s) vazia(s)

    int tam_a = tamanho (la), tam_b = tamanho (lb);
    int mat_a[tam_a], mat_b[tam_b];
    int rep_a[tam_a], rep_b[tam_b];

    no *na = la->inicio;
    no *nb = lb->inicio;
    no *aux = (no *) malloc (sizeof(no));

    int i, j, k;

    for (i = 0; i < tam_a; i++)
    {
        mat_a[i] = na->info.mat;
        rep_a[i] = 0;
        aux = na->prox;
        while (aux != NULL)
        {
            if (mat_a[i] == na->info.mat)
                rep_a[i]++;
            aux = aux->prox;
        }
        na = na->prox;
    }

    for (i = 0; i < tam_a; i++)
    {
        for (j = (i + 1); j < tam_a; j++)
        {
            if (mat_a[i] == mat_a[j])
            {
                for (k = j; k < tam_a; k++)
                {
                    mat_a[k] = mat_a[(k + 1)];
                    rep_a[k] = rep_a[(k + 1)];
                }
                j--;
                tam_a--;
            }
        }
    }

    for (i = 0; i < tam_b; i++)
    {
        mat_b[i] = nb->info.mat;
        rep_b[i] = 0;
        aux = nb->prox;
        while (aux != NULL)
        {
            if (mat_b[i] == nb->info.mat)
                rep_b[i]++;
            aux = aux->prox;
        }
        nb = nb->prox;
    }

    for (i = 0; i < tam_b; i++)
    {
        for (j = (i + 1); j < tam_b; j++)
        {
            if (mat_b[i] == mat_b[j])
            {
                for (k = j; k < tam_b; k++)
                {
                    mat_b[k] = mat_b[(k + 1)];
                    rep_b[k] = rep_b[(k + 1)];
                }
                j--;
                tam_b--;
            }
        }
    }

    int flag;

    for (i = 0; i < tam_a; i++)
    {
        flag = 0;
        for (j = 0; j < tam_b; j++)
        {
            if (mat_a[i] == mat_b[j])
            {
                flag = 1;
                if (rep_a[i] != rep_b[j]) return 1; //divergência encontrada
            }
        }
        if (flag == 0) return 1;                    //divergência encontrada
    }

    return 0;                                       //listas iguais
}

int remover_repetido (lista *l, int mat)
{
    if (l == NULL) return 2;                        //lista não alocada
    if (lista_vazia (l) == 0) return 1;             //lista vazia

    no *nolista = l->inicio;
    no *apaga = (no *) malloc (sizeof(no));
    int flag = 0;

    while (nolista != NULL)
    {
        if ((nolista->info.mat == mat) && (flag == 0))
        {
            flag = 1;
            nolista = nolista->prox;
        }

        if ((nolista->info.mat == mat) && (flag == 1))
        {
            apaga = nolista;
            nolista = nolista->prox;
            nolista->ant->prox = nolista->prox;
            nolista->prox->ant = nolista->ant;
            free (apaga);
        }
    }

    return 0;                                       //repetições removidas
}
