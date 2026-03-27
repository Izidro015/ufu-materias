#include <stdio.h>
#include <stdlib.h>

/*d) Faça uma função que receba um texto de até 400 caracteres, e retorne dois vetores,
um contendo cada um dos caracteres digitados (sem repetição), e outro contendo quantas vezes cada
caractere presente no primeiro vetor aparece. O vetor não precisa estar em ordem alfabética.
Faça um programa que utilize a função e mostre essas informações na tela*/

void semrep(char* str){
    int *carep;
    carep=(int *)calloc(52,sizeof(int));
    for(int i=0;i<strlen(str);i++){
        if(str[i]==' ')
            continue;
        carep[str[i]-64]++;
    }
    for(int i=0;i<52;i++){
        if(carep[i]==0)
            continue;
        printf("o caractere %c aparece %d vezes;\n", i+64,carep[i]);

    }
}

int main(){
    char str[401];
    printf("Digite o texto: ");
    fgets(str,400,stdin);
    semrep(str);
    return 0;
}
