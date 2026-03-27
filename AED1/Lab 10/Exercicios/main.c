#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

int main(){
    Lista *l = criar ();
    aluno a;
    int tam, p1, p2;
    int opcao, retorno;
    while (1){
        printf ("\nMENU");
        printf ("\n(1) cadastrar aluno");
        printf ("\n(2) remover aluno");
        printf ("\n(3) listar alunos cadastrados");
        printf ("\n(4) mostrar dados do aluno com maior nota");
        printf ("\n(5) remover todos os alunos");
        printf ("\n(6) trocar os alunos de lugar");
        printf ("\n(7) comparar alunos");
        printf ("\n(8) sair");
        printf ("\n\nopcao escolhida: ");
        scanf ("%d", &opcao);
        if (opcao == 8){
            printf ("\n\nencerrando o programa...");
            free (l);
            break;
        }
        switch (opcao){
            case 1:
                printf ("\n\ndigite o nome do aluno: ");
                setbuf (stdin, NULL);
                fgets (a.nome, 30, stdin);
                a.nome[strcspn(a.nome, "\n")] = '\0';
                printf ("digite a matricula do aluno: ");
                scanf ("%d", &a.mat);
                printf ("digite a nota do aluno: ");
                scanf ("%f", &a.nota);
                retorno = cadastraraluno (l, a);
                if (retorno == 2)
                    printf ("\nerro: lista nao alocada");
                if (retorno == 0)
                    printf ("\naluno cadastrado");

                break;
            case 2:
                printf ("\n\ndigite a matricula do aluno: ");
                scanf ("%d", &a.mat);
                retorno = removeraluno (l, a.mat);
                if (retorno == 2)
                    printf ("\nerro: lista nao alocada");
                if (retorno == 1)
                    printf ("\nerro: lista vazia");
                if (retorno == 0)
                    printf ("\naluno removido");
                if (retorno == -2)
                    printf ("\naluno nao encontrado");
                break;
            case 3:
                printf ("\n\nLISTA DE ALUNOS CADASTRADOS:\n");
                listarcadastrados (l);
                break;
            case 4:
                printf ("\n\nALUNO COM MAIOR NOTA:\n");
                    retorno = maiornota (l, &a);
                    printf ("\nnome: %s", a.nome);
                    printf ("\nmatricula: %d", a.mat);
                    printf ("\nnota: %.2f", a.nota);
                break;
            case 5:
                printf ("\n\nremovendo alunos...");
                limparlista (l);
                printf ("\nalunos removidos");
                break;
            case 6:
                tam = (tamanho (l) - 1);
                if (tam == 0){
                    printf ("\n\nerro: lista vazia");
                    break;
                }do{
                    printf ("\n\ndigite uma posicao (0-%d): ", tam);
                    scanf ("%d", &p1);
                    printf ("digite outra posicao (0-%d): ", tam);
                    scanf ("%d", &p2);
                    if ((p1 < 0) || (p1 > tam) || (p2 < 0) || (p2 > tam) || (p1 == p2))
                        printf ("posicoes invalidas");
                } while ((p1 < 0) || (p1 > tam) || (p2 < 0) || (p2 > tam) || (p1 == p2));
                retorno = trocaposicao (l, p1, p2);
                if (retorno == 2)
                    printf ("\nerro: lista nao alocada");
                if (retorno == 0)
                    printf ("\nposicoes trocaddas");
                break;

            case 7:
                printf ("\n\ncomparando listas...");
                retorno = verificarIgualdade(&l,&a);
                if (retorno == 2)
                    printf ("\nerro: lista(s) nao alocada(s)");
                if (retorno == -1)
                    printf ("\nerro: lista(s) vazia(s)");
                if (retorno == 0)
                    printf ("\nas listas sao iguais");
                if (retorno == 3)
                    printf ("\nas listas nao sao iguais");
                break;

            default:
                printf ("\n\nopcao invalida, tente novamente");
                break;
        }
    }
    return 0;
}
