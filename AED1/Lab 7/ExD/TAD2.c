#include "TAD2.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 100

typedef struct aluno {
    int mat;
    char nome[30];
    float n1;
} aluno;

typedef struct lista {
    int total;
    aluno *valores;
} lista;

lista *criar() {
    lista *l = (lista *)malloc(sizeof(lista));
    if (l != NULL) {
        l->valores = (aluno *)malloc(MAX * sizeof(aluno));
        l->total = 0;
    }
    return l;
}

void limpar(lista *l) {
    if (l != NULL) {
        free(l->valores);
        l->total = 0;
        free(l);
    }
}

void leraluno(aluno *it) {
    printf("Digite a matricula do aluno: ");
    scanf("%d", &(it->mat));
    printf("Digite o nome do aluno: ");
    setbuf(stdin, NULL);
    fgets(it->nome, sizeof(it->nome), stdin);
    it->nome[strcspn(it->nome, "\n")] = '\0';
    printf("Digite a nota do aluno: ");
    scanf("%f", &(it->n1));
}

int inseririnicio(lista *l, aluno it) {
    if (l == NULL || l->total >= MAX) {
        return 1;
    }
    for (int i = l->total; i > 0; i--) {
        l->valores[i] = l->valores[i - 1];
    }
    l->valores[0] = it;
    l->total++;
    return 0;
}

int inserirfim(lista *l, aluno it) {
    if (l == NULL || l->total >= MAX) {
        return 1;
    }
    l->valores[l->total] = it;
    l->total++;
    return 0;
}

int buscaritemchave(lista *l, int chave, aluno *retorno) {
    if (l == NULL || l->total == 0) {
        return -1;
    }
    for (int i = 0; i < l->total; i++) {
        if (l->valores[i].mat == chave) {
            *retorno = l->valores[i];
            return 0;
        }
    }
    return 1;
}

int listavazia(lista *l) {
    if (l == NULL || l->total == 0) {
        return 1;
    }
    return 0;
}

int removerinicio(lista *l) {
    if (l == NULL || l->total == 0) {
        return 1;
    }
    for (int i = 0; i < l->total - 1; i++) {
        l->valores[i] = l->valores[i + 1];
    }
    l->total--;
    return 0;
}

int removerfim(lista *l) {
    if (l == NULL || l->total == 0) {
        return 1;
    }
    l->total--;
    return 0;
}

int listacheia(lista *l) {
    if (l == NULL || l->total >= MAX) {
        return 1;
    }
    return 0;
}

void mostrar(lista *l) {
    if (l != NULL) {
        printf("[");
        for (int i = 0; i < l->total; i++) {
            printf(" {%d, %s, %.2f} ", l->valores[i].mat, l->valores[i].nome, l->valores[i].n1);
        }
        printf("]\n");
    }
}

int inserirposicao(lista *l, aluno it, int pos) {
    if (l == NULL || pos < 0 || pos > l->total || l->total >= MAX) {
        return 1;
    }
    for (int i = l->total - 1; i >= pos; i--) {
        l->valores[i + 1] = l->valores[i];
    }
    l->valores[pos] = it;
    l->total++;
    return 0;
}

int removerposicao(lista *l, int pos) {
    if (l == NULL || pos < 0 || pos >= l->total || l->total == 0) {
        return 1;
    }
    for (int i = pos; i < l->total - 1; i++) {
        l->valores[i] = l->valores[i + 1];
    }
    l->total--;
    return 0;
}

int removeritem(lista *l, aluno it) {
    if (l == NULL || l->total == 0) {
        return 1;
    }
    int flag = 0;
    for (int i = 0; i < l->total; i++) {
        if (l->valores[i].mat == it.mat) {
            for (int j = i; j < l->total - 1; j++) {
                l->valores[j] = l->valores[j + 1];
            }
            flag++;
            l->total--;
            i--;
        }
    }

    if (flag == 0) {
        return 1;
    } else {
        return 0;
    }
}

int buscarposicao(lista *l, int posicao, aluno *it) {
    if (l == NULL || posicao < 0 || posicao >= l->total || l->total == 0) {
        return 1;
    }
    *it = l->valores[posicao];
    return 0;
}

int tamanho(lista *l) {
    if (l == NULL) {
        return 0;
    }
    return l->total;
}

int contemitem(lista *l, aluno *it) {
    if (l == NULL || l->total == 0) {
        return 1;
    }
    for (int i = 0; i < l->total; i++) {
        if (l->valores[i].mat == it->mat) {
            return 0;
        }
    }
    return 1;
}

lista *reversa(lista *l) {
    if (l == NULL || l->total == 0) {
        return NULL;
    }
    lista *auxiliar = criar();
    for (int i = l->total - 1; i >= 0; i--) {
        inserirfim(auxiliar, l->valores[i]);
    }
    return auxiliar;
}

int contaitem(lista *l, aluno *it) {
    if (l == NULL || l->total == 0) {
        return 0;
    }
    int cont = 0;
    for (int i = 0; i < l->total; i++) {
        if (l->valores[i].mat == it->mat) {
            cont++;
        }
    }
    return cont;
}
