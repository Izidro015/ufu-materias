#include <stdio.h>
#include <stdlib.h>
#include "TAD.h"

void mostrarMenu()
{
    printf("Menu:\n");
    printf("1. Inserir\n");
    printf("2. Mostrar lista\n");
    printf("3. Mostrar exercicio A\n");
    printf("4. Mostrar exercicio B\n");
    printf("5. Mostrar exercicio C\n");
    printf("6. Mostrar exercicio D\n");
    printf("7. Mostrar Exercicio E\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}

int main() {
    lista *minhaLista = criar();
    lista *novaLista = criar();
    int opcao, num;
    do{
        mostrarMenu();
        scanf("%d", &opcao);
        setbuf(stdin, NULL);
        switch (opcao){
            case 1:{
                int novoNum;
                printf("Digite o numero: ");
                scanf("%d",&novoNum);
                inseririnicio(minhaLista, novoNum);
                printf("Numero inserido no inicio da lista.\n");
                break;
            }
            case 2:
                mostrar(minhaLista);
                printf("\n");
                break;
            case 3:
                recursaoA(minhaLista, &num);
                printf("%d\n", num);
                break;
            case 4:
                printf("%d\n", soma(minhaLista));
                break;
            case 5:
                inverte(minhaLista);
                printf("\n");
                break;
            case 6:
                printf("Digite o numero a ser removido: ");
                scanf("%d", &num);
                removeint(minhaLista, num);
                mostrar(minhaLista);
                printf("\n");
                break;
            case 7:
               printf("\nDigitar um numero binario!!!\n ");
                for(int i=0; i<8; i++){
                    printf("\nDigite um digito do numero binario: ");
                    scanf("%d", &num);
                    inseririnicio(novaLista,num);
                }
                printf("\nDigite um inteiro para somar: " );
                scanf("%d", &num);
                for(int i=0;i<num;i++){
                    incrementa(novaLista);
                }
                inverte(novaLista);
                printf("\n");
                break;
            case 0:
                printf("Saindo do programa.\n");
                exit(0);
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }

    }while(opcao != 7);
    free(minhaLista);
    return 0;
}
