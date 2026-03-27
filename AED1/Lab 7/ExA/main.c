#include "implement.h"
#include <stdio.h>
#include <string.h>

int main() {
    lista *l = criar();

    int opcao, posicao, matricula, resultado;
    aluno alunox, encontrado;

    while (1) {
        printf("\nMenu:\n");
        printf("1 - Inserir aluno no inicio\n");
        printf("2 - Inserir aluno no fim\n");
        printf("3 - Inserir aluno em uma posicao\n");
        printf("4 - Remover aluno do inicio\n");
        printf("5 - Remover aluno do fim\n");
        printf("6 - Remover aluno de uma posicao\n");
        printf("7 - Mostrar lista\n");
        printf("8 - Buscar aluno por matricula\n");
        printf("9 - Verificar se a lista esta vazia\n");
        printf("10 - Verificar se a lista esta cheia\n");
        printf("11 - Tamanho da lista\n");
        printf("12 - Contem aluno na lista\n");
        printf("13 - Reverter a lista\n");
        printf("14 - Contar ocorrencias de um aluno\n");
        printf("15 - Remover aluno pela matricula\n");
        printf("16 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
            case 1:

                leraluno(&alunox);

                inseririnicio(l, alunox);

                printf("Aluno inserido no inicio da lista.\n");

                break;

            case 2:

                leraluno(&alunox);

                inserirfim(l, alunox);

                printf("Aluno inserido no fim da lista.\n");

                break;
            case 3:
                leraluno(&alunox);

                int pos;

                printf("Digite a posicao para inserir o aluno: ");

                scanf("%d", &pos);

                if (inserirposicao(l, alunox, pos) == 0)
                {
                    printf("Aluno inserido na posicao %d da lista.\n", pos);
                }
                else
                {
                    printf("Falha ao inserir aluno na posicao %d da lista.\n", pos);
                }
                break;
            case 4:
                if (removerinicio(l) == 0)
                {
                    printf("Aluno removido do inicio da lista.\n");
                }
                else
                {
                    printf("Falha ao remover aluno do inicio da lista.\n");
                }
                break;
            case 5:
                if (removerfim(l) == 0)
                {
                    printf("Aluno removido do fim da lista.\n");
                } else
                {
                    printf("Falha ao remover aluno do fim da lista.\n");
                }
                break;

            case 6:

                printf("Digite a posicao para remover o aluno: ");

                scanf("%d", &posicao);

                if (removerposicao(l, posicao) == 0)
                {
                    printf("Aluno removido da posicao %d da lista.\n", posicao);
                }
                else
                {
                    printf("Falha ao remover aluno da posicao %d da lista.\n", posicao);
                }
                break;

            case 7:

                printf("Conteudo da lista:\n");

                mostrar(l);

                break;

            case 8:


                printf("Digite a matricula a ser buscada: ");

                scanf("%d", &matricula);

                if (buscaritemchave(l, matricula, &encontrado) == 0)
                {
                    printf("Aluno encontrado: %d, %s, %.2lf\n", encontrado.mat, encontrado.nome, encontrado.n1);
                }
                else
                {
                    printf("Aluno nao encontrado.\n");
                }
                break;
            case 9:
                if (listavazia(l) == 0)
                {
                    printf("A lista esta vazia.\n");
                }
                else
                {
                    printf("A lista nao esta vazia.\n");
                }
                break;
            case 10:
                if (listacheia(l) == 0)
                {
                    printf("A lista esta cheia.\n");
                }
                else
                {
                    printf("A lista nao esta cheia.\n");
                }
                break;

            case 11:

                printf("Tamanho da lista: %d\n", tamanho(l));

                break;

            case 12:

                leraluno(&alunox);

                if (contemitem(l, &alunox) == 0)
                {
                    printf("A lista contem o aluno.\n");
                }
                else
                {
                    printf("A lista nao contem o aluno.\n");
                }
                break;

            case 13:

                l = reversa(l);

                printf("Lista revertida com sucesso.\n");

                break;

            case 14:

                leraluno(&alunox);

                int ocorrencias = contaitem(l, &alunox);

                printf("O aluno com a matricula %d ocorre %d vezes na lista.\n", alunox.mat, ocorrencias);

                break;

            case 15:
                printf("\nDigite a matricula de um aluno que deseja remover: ");
                scanf("%d", &matricula);

                alunox.mat = matricula;

                resultado = removeritem(l, alunox);
                if (resultado == 0) {
                    printf("\nAluno removido.");
                } else if (resultado == 1) {
                    printf("\nAluno não encontrado.");
                } else {
                    printf("\nErro na lista.");
                }
                break;


            case 16:
                free(l);
                return 0;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    }

    return 0;
}
