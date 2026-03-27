#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tad.h"


int main ( )
{
    lista *la = criar ( );
    lista *lb = criar ( );

    aluno a;

    int op1, op2, retorno, tam;
    int p1, p2;

    while (1)
    {
        printf ("\n\nMENU\n");
        printf ("\n(1) cadastrar aluno");
        printf ("\n(2) remover aluno");
        printf ("\n(3) listar alunos cadastrados");
        printf ("\n(4) mostrar dados do aluno com maior nota");
        printf ("\n(5) remover todos os alunos");
        printf ("\n(6) trocar posicoes");
        printf ("\n(7) comparar listas");
        printf ("\n(8) remover repeticoes");
        printf ("\n(9) sair");

        printf ("\n\nopcao escolhida: ");
        scanf ("%d", &op1);

        if (op1 == 9)
        {
            printf ("\n\nencerrando o programa...");
            free (la);
            free (lb);
            break;
        }

        switch (op1)
        {
            case 1:
                printf ("\n\nescolha a lista:");
                printf ("\n1 - lista A, 2 - lista B\n");
                scanf ("%d", &op2);

                if ((op2 != 1) && (op2 != 2))
                {
                    printf ("lista invalida");
                    break;
                }

                printf ("\n\ndigite o nome do aluno: ");
                setbuf (stdin, NULL);
                fgets (a.nome, 30, stdin);
                a.nome[strcspn(a.nome, "\n")] = '\0';

                printf ("digite a matricula do aluno: ");
                scanf ("%d", &a.mat);

                printf ("digite a nota do aluno: ");
                scanf ("%f", &a.nota);

                if (op2 == 1)
                {
                    retorno = inserir_aluno (la, a);
                    if (retorno == 2)
                        printf ("\nerro: lista nao alocada");
                    if (retorno == 0)
                        printf ("\naluno cadastrado");

                    break;
                } else {
                    retorno = inserir_aluno (lb, a);
                    if (retorno == 2)
                        printf ("\nerro: lista nao alocada");
                    if (retorno == 0)
                        printf ("\naluno cadastrado");

                    break;
                }

            case 2:
                printf ("\n\nescolha a lista:");
                printf ("\n1 - lista A, 2 - lista B\n");
                scanf ("%d", &op2);

                if ((op2 != 1) && (op2 != 2))
                {
                    printf ("lista invalida");
                    break;
                }

                printf ("\n\ndigite a matricula do aluno: ");
                scanf ("%d", &a.mat);

                if (op2 == 1)
                {
                    retorno = remover_aluno (la, a.mat);
                    if (retorno == 2)
                        printf ("\nerro: lista nao alocada");
                    if (retorno == 1)
                        printf ("\nerro: lista vazia");
                    if (retorno == 0)
                        printf ("\naluno removido");
                    if (retorno == -2)
                        printf ("\naluno nao encontrado");
                    break;
                } else {
                    retorno = remover_aluno (lb, a.mat);
                    if (retorno == 2)
                        printf ("\nerro: lista nao alocada");
                    if (retorno == 1)
                        printf ("\nerro: lista vazia");
                    if (retorno == 0)
                        printf ("\naluno removido");
                    if (retorno == -2)
                        printf ("\naluno nao encontrado");
                    break;
                }

            case 3:
                printf ("\n\nescolha a lista:");
                printf ("\n1 - lista A, 2 - lista B\n");
                scanf ("%d", &op2);

                if ((op2 != 1) && (op2 != 2))
                {
                    printf ("lista invalida");
                    break;
                }

                printf ("\n\nLISTA DE ALUNOS CADASTRADOS:\n");

                if (op2 == 1)
                    mostrar (la);
                else mostrar (lb);

                break;

            case 4:
                printf ("\n\nescolha a lista:");
                printf ("\n1 - lista A, 2 - lista B\n");
                scanf ("%d", &op2);

                if ((op2 != 1) && (op2 != 2))
                {
                    printf ("lista invalida");
                    break;
                }

                printf ("\n\nALUNO COM MAIOR NOTA:\n");

                if (op2 == 1)
                {
                    retorno = maior_nota (la, &a);
                    if (retorno == 2)
                        printf ("\nerro: lista nao alocada");
                    if (retorno == 1)
                        printf ("\nerro: lista vazia");
                    if (retorno == 0)
                    {
                        printf ("\nnome: %s", a.nome);
                        printf ("\nmatricula: %d", a.mat);
                        printf ("\nnota: %.2f", a.nota);
                    }

                    break;
                } else {
                    retorno = maior_nota (lb, &a);
                    if (retorno == 2)
                        printf ("\nerro: lista nao alocada");
                    if (retorno == 1)
                        printf ("\nerro: lista vazia");
                    if (retorno == 0)
                    {
                        printf ("\nnome: %s", a.nome);
                        printf ("\nmatricula: %d", a.mat);
                        printf ("\nnota: %.2f", a.nota);
                    }

                    break;
                }

            case 5:
                printf ("\n\nescolha a lista:");
                printf ("\n1 - lista A, 2 - lista B\n");
                scanf ("%d", &op2);

                if ((op2 != 1) && (op2 != 2))
                {
                    printf ("lista invalida");
                    break;
                }

                printf ("\n\nremovendo alunos...");

                if (op2 == 1)
                    limpar (la);
                else limpar (lb);

                printf ("\nalunos removidos");

                break;

            case 6:
                printf ("\n\nescolha a lista:");
                printf ("\n1 - lista A, 2 - lista B\n");
                scanf ("%d", &op2);

                if ((op2 != 1) && (op2 != 2))
                {
                    printf ("lista invalida");
                    break;
                }

                if (op2 == 1)
                {
                    tam = tamanho (la) - 1;
                    if (tam == 0)
                    {
                        printf ("\n\nerro: lista vazia");
                        break;
                    }

                    do
                    {
                        printf ("\n\ndigite uma posicao (0-%d): ", tam);
                        scanf ("%d", &p1);

                        printf ("digite outra posicao (0-%d): ", tam);
                        scanf ("%d", &p2);

                        if ((p1 < 0) || (p1 > tam) || (p2 < 0) || (p2 > tam) || (p1 == p2))
                            printf ("posicoes invalidas");

                    } while ((p1 < 0) || (p1 > tam) || (p2 < 0) || (p2 > tam) || (p1 == p2));

                    retorno = trocar_posicao (la, p1, p2);
                    if (retorno == 2)
                        printf ("\nerro: lista nao alocada");
                    if (retorno == 0)
                        printf ("\nposicoes trocaddas");

                    break;
                } else {
                    tam = tamanho (lb) - 1;
                    if (tam == 0)
                    {
                        printf ("\n\nerro: lista vazia");
                        break;
                    }

                    do
                    {
                        printf ("\n\ndigite uma posicao (0-%d): ", tam);
                        scanf ("%d", &p1);

                        printf ("digite outra posicao (0-%d): ", tam);
                        scanf ("%d", &p2);

                        if ((p1 < 0) || (p1 > tam) || (p2 < 0) || (p2 > tam) || (p1 == p2))
                            printf ("posicoes invalidas");

                    } while ((p1 < 0) || (p1 > tam) || (p2 < 0) || (p2 > tam) || (p1 == p2));

                    retorno = trocar_posicao (lb, p1, p2);
                    if (retorno == 2)
                        printf ("\nerro: lista nao alocada");
                    if (retorno == 0)
                        printf ("\nposicoes trocaddas");

                    break;
                }

            case 7:
                printf ("\n\ncomparando listas...");

                retorno = analisa_listas (la, lb);
                if (retorno == 2)
                    printf ("\nerro: lista(s) nao alocada(s)");
                if (retorno == 3)
                    printf ("\nerro: lista(s) vazia(s)");
                if (retorno == 0)
                    printf ("\nas listas sao iguais");
                if (retorno == 1)
                    printf ("\nas listas nao sao iguais");

                break;

            case 8:
                printf ("\n\nescolha a lista:");
                printf ("\n1 - lista A, 2 - lista B\n");
                scanf ("%d", &op2);

                if ((op2 != 1) && (op2 != 2))
                {
                    printf ("lista invalida");
                    break;
                }

                printf ("\n\ndigite a matricula do aluno: ");
                scanf ("%d", &a.mat);

                if (op2 == 1)
                {
                    retorno = remover_repetido (la, a.mat);
                    if (retorno == 2)
                        printf ("\nerro: lista nao alocada");
                    if (retorno == 1)
                        printf ("\nerro: lista vazia");
                    if (retorno == 0)
                        printf ("\nrepeticoes removidas");

                    break;
                } else {
                    retorno = remover_repetido (lb, a.mat);
                    if (retorno == 2)
                        printf ("\nerro: lista nao alocada");
                    if (retorno == 1)
                        printf ("\nerro: lista vazia");
                    if (retorno == 0)
                        printf ("\nrepeticoes removidas");

                    break;
                }

            default:
                printf ("\n\nopcao invalida, tente novamente");
                break;
        }
    }

    return 0;
}
