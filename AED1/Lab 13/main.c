#include <stdio.h>
#include <stdlib.h>
#include "TAD.h"

void mostrarMenu(){
    printf("Menu:\n");
    printf("1. Mostrar exercicio A\n");
    printf("2. Mostrar exercicio B\n");
    printf("3. Mostrar exercicio C\n");
    printf("4. Mostrar exercicio D\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");

}

int main(){
    Pilha *minhaPilha=criar();
    Pilha *novaPilha=criar();
    int opcao, num;
    do{
        mostrarMenu();
        scanf("%d", &opcao);
        setbuf(stdin, NULL);
        switch (opcao){
           case 1:{
                push(minhaPilha, 11);
                mostrar(minhaPilha);
                push(minhaPilha,34);
                mostrar(minhaPilha);
                pop(minhaPilha,34);
                mostrar(minhaPilha);
                pop(minhaPilha,11);
                mostrar(minhaPilha);
                push(minhaPilha,23);
                mostrar(minhaPilha);
                push(minhaPilha,45);
                mostrar(minhaPilha);
                pop(minhaPilha,45);
                mostrar(minhaPilha);
                push(minhaPilha,121);
                mostrar(minhaPilha);
                push(minhaPilha,22);
                pop(minhaPilha,22);
                mostrar(minhaPilha);
                pop(minhaPilha,121);
                mostrar(minhaPilha);
                break;
            }
            case 2:
                push(minhaPilha, 5);
                push(minhaPilha, 8);
                push(minhaPilha,41);
                push(minhaPilha,78);
                push(novaPilha,5);
                push(novaPilha,8);
                push(novaPilha,41);
                push(novaPilha,78);
                if(compare(minhaPilha, novaPilha)==0) printf("Iguais.\n");
                else printf("Diferentes.\n");
                break;
            case 3:{
                char str[100];
                int n;
                printf("Digite a string: ");
                scanf("%s", str);
                if(testar(str) == 0) printf("\nValida.\n");
                else printf("\nInvalida.\n");
            }
            case 4:

                break;
            case 0:
                printf("Saindo do programa.\n");
                exit(0);
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }

    }while(opcao != 4);
    free(minhaPilha);
    return 0;
}
