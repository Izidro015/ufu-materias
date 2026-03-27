#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

void mostrarMenu() {
    printf("Menu:\n");
    printf("1. Inserir aluno no inicio\n");
    printf("2. Inserir aluno no fim\n");
    printf("3. Inserir aluno em uma posicao\n");
    printf("4. Remover aluno do inicio\n");
    printf("5. Remover aluno do fim\n");
    printf("6. Remover aluno de uma posicao\n");
    printf("7. Buscar aluno por matricula\n");
    printf("8. Verificar se a lista contem um aluno\n");
    printf("9. Mostrar lista\n");
    printf("10. Limpar lista\n");
    printf("11. Remover central\n");
    printf("12. Interseccao\n");
    printf("13. Inserir fim sem repeticao\n");
    printf("14. Sair\n");
    printf("Escolha uma opcao: ");
}

int main(){
    Lista *minhaLista = criar();
    Lista *l2;
    int opcao;
    do{
        mostrarMenu();
        scanf("%d", &opcao);
        setbuf(stdin, NULL);
        switch (opcao){
            case 1:{
                Aluno novoAluno;
                printf("Digite a matricula, nome e nota do aluno: ");
                scanf("%d %s %f", &novoAluno.mat, novoAluno.nome, &novoAluno.n1);
                inseririnicio(minhaLista, novoAluno);
                printf("Aluno inserido no inicio da lista.\n");
                break;
            }
            case 2:{
                Aluno novoAluno;
                printf("Digite a matricula, nome e nota do aluno: ");
                scanf("%d %s %f", &novoAluno.mat, novoAluno.nome, &novoAluno.n1);
                inserirfim(minhaLista, novoAluno);
                printf("Aluno inserido no fim da lista.\n");
                break;
            }
            case 3:{
                Aluno novoAluno;
                int posicao;
                printf("Digite a matricula, nome e nota do aluno: ");
                scanf("%d %s %f", &novoAluno.mat, novoAluno.nome, &novoAluno.n1);
                printf("Digite a posicao de insercao: ");
                scanf("%d", &posicao);
                inserirposicao(minhaLista, novoAluno, posicao);
                printf("Aluno inserido na posicao %d da lista.\n", posicao);
                break;
            }
            case 4:
                removerinicio(minhaLista);
                printf("Aluno removido do inicio da lista.\n");
                break;
            case 5:
                removerfim(minhaLista);
                printf("Aluno removido do fim da lista.\n");
                break;
            case 6:{
                int posicao;
                printf("Digite a posicao de remocao: ");
                scanf("%d", &posicao);
                removerposicao(minhaLista, posicao);
                printf("Aluno removido da posicao %d da lista.\n", posicao);
                break;
            }
            case 7:{
                int matricula;
                Aluno encontrado;
                printf("Digite a matricula a ser buscada: ");
                scanf("%d", &matricula);
                if (buscaritem(minhaLista, matricula, &encontrado) == 0) {
                    printf("Aluno encontrado:\n");
                    printf("Matricula: %d\n", encontrado.mat);
                    printf("Nome: %s\n", encontrado.nome);
                    printf("Nota: %.2f\n", encontrado.n1);
                }else{
                    printf("Aluno com a matricula %d nao encontrado.\n", matricula);
                }
                break;
            }
            case 8:{
                Aluno alunoBusca;
                printf("Digite a matricula do aluno a ser verificado: ");
                scanf("%d", &alunoBusca.mat);
                if (buscaritem(minhaLista, alunoBusca.mat, &alunoBusca) == 0) {
                    printf("A lista contem o aluno com matricula %d.\n", alunoBusca.mat);
                }else{
                    printf("A lista nao contem o aluno com matricula %d.\n", alunoBusca.mat);
                }
                break;
            }
                break;
            case 9:
                mostrar(minhaLista);
                break;
            case 10:
                limpar(minhaLista);
                printf("Lista limpa.\n");
                break;
            case 11:
                removercentral(minhaLista);
                printf("\nElemento central removido.");
                break;
            case 12:
                l2=criar();
                printf("\nVamos preencher a lista 2 com 3 alunos: ");
                for(int i = 0; i < 3; i++){
                    Aluno novoAluno;
                    setbuf(stdin,NULL);
                    printf("Digite a matricula, nome e nota do aluno: ");
                    scanf("%d %s %f", &novoAluno.mat, novoAluno.nome, &novoAluno.n1);
                    novoAluno.nome[strcspn(novoAluno.nome, "\n")] = '\0';
                   inseririnicio(l2, novoAluno);
                }
                Lista *result = interseccao(minhaLista, l2);
                mostrar(result);
                break;
            case 13:{
                    Aluno novoAluno2;
                    setbuf(stdin, NULL);
                    printf("Digite a matricula, nome e nota do aluno: ");
                    scanf("%d %s %f", &novoAluno2.mat, novoAluno2.nome, &novoAluno2.n1);
                    inserirfimII(minhaLista, novoAluno2);
                    break;
                }
                case 14:
                printf("Saindo do programa.\n");
                exit(0);
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    }while(opcao != 12);
    free(minhaLista);
    return 0;
}
