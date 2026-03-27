#include "TAD1.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct lista{
    int total;
    int capacidade_maxima;
    aluno *valores;
} lista;

lista *criar(int capacidade_maxima){
    lista *l = (lista *)malloc(sizeof(lista));
    if (l != NULL){
        l->total = 0;
        l->capacidade_maxima = capacidade_maxima;
        l->valores = (aluno *)malloc(capacidade_maxima * sizeof(aluno));
    }
    return l;
}

void limpar(lista *l){
    if (l != NULL) l->total = 0;
}

void leraluno(aluno *it){
    printf("Digite a matricula do aluno: ");
    scanf("%d", &(it->mat));
    printf("Digite o nome do aluno: ");
    setbuf(stdin,NULL);
    fgets(it->nome, 30, stdin);
    it->nome[strcspn(it->nome, "\n")] = '\0';
    printf("Digite a nota do aluno: ");
    scanf("%f", &(it->n1));
}

int inseririnicio(lista *l, aluno it){
    int i;
    if (l == NULL){
        return 2;
    }
    if (l->total >= l->capacidade_maxima){
        return 1;
    }
    for (i = l->total; i > 0; i--){
        l->valores[i] = l->valores[i - 1];
    }
    l->valores[0] = it;
    l->total++;
    return 0;
}

int inserirfim(lista *l, aluno it){
    if (l == NULL){
        return 2;
    }
    if (l->total >= l->capacidade_maxima){
        return 1;
    }
    l->valores[l->total] = it;
    l->total++;
    return 0;
}

int buscaritemchave(lista *l, int chave,aluno *retorno){
    int i;
    if (l == NULL) return 2;
    if (listavazia(l) == 0) return 1;
    for (i=0;i<l->total;i++){
        if (l->valores[i].mat == chave){
            *retorno = l->valores[i];
            return 0;
        }
    }
    return -1;
}

int listavazia(lista *l){
    if (l == NULL) return 2;
    if (l->total == 0) return 0;
    else return 1;
}

int removerinicio(lista *l){
    int i;
    if (l == NULL) return 2;
    if (listavazia(l) == 0) return 1;
    for (i=0;i<l->total-1;i++)
    l->valores[i] = l->valores[i+1];l->total--;
    return 0;
}

int removerfim(lista *l){
    if (l == NULL) return 2;
    if (listavazia(l) == 0) return 1;l->total--;
    return 0;
}

int listacheia(lista *l){
    if (l == NULL) return 2;
    if (l->total == l->capacidade_maxima) return 0;
    else return 1;
}

void mostrar(lista *l){
    int i;
    if (l != NULL){
        printf("[");
        for (i=0;i<l->total;i++){
            printf(" {%d, ",l->valores[i].mat);
            printf("%s, ",l->valores[i].nome);
            printf("%.2f} ",l->valores[i].n1);
        }
        printf("]\n");
    }
}

int inserirposicao(lista *l, aluno it, int pos){
    int i;
    if (l == NULL){
        return 2;
    }
    if (l->total >= l->capacidade_maxima){
        return 1;
    }
    if (pos < 0 || pos > l->total || l->total >= l->capacidade_maxima){
        return 1;
    }
    for (i = l->total - 1; i >= pos; i--){
        l->valores[i + 1] = l->valores[i];
    }
    l->valores[pos] = it;
    l->total++;
    return 0;
}


int removerposicao(lista *l, int pos){
    int i;
    if (l == NULL) return 2;
    if (pos < 0 || pos > l->total){
        return 1;
    }
    if (listavazia(l) == 0){
        return 1;
    }else{
        for (i = pos; i < l->total - 1; i++){
            l->valores[i] = l->valores[i + 1];
        }
        l->total--;
        return 0;
    }
}

int removeritem(lista *l, aluno it){
    int i, j, flag = 0;
    if (l == NULL) return 2;
    if (listavazia(l) == 0){
        return 1;
    }else{
        for (i = 0; i < l->total; i++){
            if (l->valores[i].mat == it.mat){
                for (j = i; j < l->total - 1; j++){
                    l->valores[j] = l->valores[j + 1];
                }
                flag++;
                l->total--;
                i--;
            }
        }
        if (flag == 0){
            return 1;
        }else{
          return 0;
        }
    }
}

int buscarposicao(lista *l, int posicao, aluno *it){
    int i;
    if (l == NULL) return 2;
    if (listavazia(l) == 0){
        return 1;
    }
    if (posicao < 0 || posicao >= l->total){
        return 1;
    }else{
        *it = l->valores[posicao];
        return 0;
    }
}

int tamanho(lista *l){
    return l->total;
}

int contemitem(lista *l, aluno *it){
    int i;
    if (l == NULL) return 2;
    if (listavazia(l) == 0){
        return 1;
    }
    for (i = 0; i < l->total; i++){
        if (l->valores[i].mat == it->mat){
            return 0;
        }
    }
    return 1;
}

lista* reversa(lista *l){
    int i, j = 0;
    if (l == NULL) return 2;
    if (listavazia(l) == 0){
        return 1;
    }
    lista *auxiliar = criar(l->capacidade_maxima);
    for (i = l->total-1; i >= 0; i--, j++){
        auxiliar->valores[j] = l->valores[i];
        auxiliar->total++;
    }
    return auxiliar;
}

int contaitem(lista *l, aluno *it){
    int i, cont = 0;
    if (l == NULL) return 2;
    if (listavazia(l) == 0){
        return 1;
    }
    for (i = 0; i < l->total; i++){
        if (l->valores[i].mat == it->mat){
            cont++;
        }
    }
    return cont;
}
