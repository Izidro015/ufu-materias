#include <stdio.h>
#include <stdlib.h>
#include "TAD.h"

void mostrarMenu(){
    printf("Menu:\n");
    printf("1. Inserir\n");
    printf("2. Remover\n");
    printf("3. Consultar\n");
    printf("4. Mostrar a fila\n");
    printf("5. Mostrar tamanho\n");
    printf("6. Mostrar exercicio A\n");
    printf("7. Mostrar exercicio B\n");
    printf("8. Mostrar Exercicio C\n");
    printf("9. Mostrar Exercicio D\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");

}

int main(){
    Fila *minhaFila=criar();
    Fila *novaFila=criar();
    Fila *f3=criar();
    int opcao, num, novoNum;
    do{
        mostrarMenu();
        scanf("%d", &opcao);
        setbuf(stdin, NULL);
        switch (opcao){
           case 1:{
                printf("Digite o numero: ");
                scanf("%d",&novoNum);
                inserir(minhaFila, novoNum);
                printf("Numero inserido no fim da lista.\n");
                break;
            }
            case 2:
                remover(minhaFila);
                printf("Primeiro componente removido com sucesso!\n");
                break;
            case 3:
                printf("%s", consultar(minhaFila, num));
                printf("\n");
                break;
            case 4:
                mostrar(minhaFila);
                printf("\n");
                break;
            case 5:
                printf("Tem %d elementos na fila.", tamanho(minhaFila));
                printf("\n");
                break;
            case 6:
                inserir(minhaFila, 10);
                mostrar(minhaFila);
                printf("\n");
                inserir(minhaFila, 20);
                mostrar(minhaFila);
                printf("\n");
                remover(minhaFila);
                mostrar(minhaFila);
                printf("\n");
                inserir(minhaFila, 30);
                mostrar(minhaFila);
                printf("\n");
                inserir(minhaFila, 45);
                mostrar(minhaFila);
                printf("\n");
                inserir(minhaFila, 21);
                mostrar(minhaFila);
                printf("\n");
                remover(minhaFila);
                mostrar(minhaFila);
                printf("\n");
                remover(minhaFila);
                mostrar(minhaFila);
                printf("\n");
                zerar(minhaFila);
                break;
            case 7:{
                int n;
                printf("Digite um numero: ");
                scanf("%d", &n);
                inserir(minhaFila, n);
                inserir(minhaFila, n);
                printf("Numero inserido no fim da lista 1.\n");
                int num2;
                printf("Digite um numero: ");
                scanf("%d", &num2);
                inserir(novaFila,num2);
                inserir(novaFila,num2);
                inserir(novaFila,num2);
                printf("Numero inserido no fim da lista 2.\n");
                intercalaFila(minhaFila,novaFila,f3);
                mostrar(f3);
                free(minhaFila);
                free(novaFila);
                free(f3);
            }
                break;
            case 8:{
                Fila *f = criar();
                int quant, n;
                printf("Deseja inserir quantos elementos na lista?\nR: ");
                scanf("%d", &quant);
                for(int i=0;i<quant;i++){
                    printf("Digite o numero: ");
                    scanf("%d",&n);
                    inserir(f, n);
                    printf("Numero inserido no fim da lista.\n");
                }
                int retorno = remover_negativos(f);
                if (retorno == -2) printf ("\nerro: lista nao alocada");
                if (retorno == -1) printf ("\nerro: lista vazia");
                if (retorno == 0) printf ("\nnumero(s) removido(s)");
                mostrar(f);
                break;
            }
            case 9:{
                char r;
                do{
                    printf("\nHa pacientes esperando?\n[S\\N]\nR: ");
                    scanf("%c",&r);
                    setbuf(stdin,NULL);
                    if(r!='N'&&r!='n'){
                        char nome[30];
                        printf("Digite seu nome: ");
                        fgets(nome,30,stdin);
                        altera_string(nome);
                        inserir(minhaFila, nome);
                        printf("%d", atendimento(minhaFila));
                        mostrar(minhaFila);
                    }else{
                        printf("\nFim do atendimento.\n");
                    }
                }while(r!='N'&&r!='n');
            }
                break;
            case 0:
                printf("Saindo do programa.\n");
                exit(0);
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    }while(opcao != 9);
    free(minhaFila);
    return 0;
}
