#include <stdio.h>
#include <stdlib.h>

/*b) Crie uma função que receba um vetor de caracteres (String), seu tamanho
e um caractere como parâmetros, e substitua todas as ocorrências desse caractere
por ‘*’. A função deve retornar a quantidade de substituições realizadas.*/

void func(int tamanho,char caractere, char *str){
    int troca=0;
    for(int i=0; i<tamanho; i++){
        if(caractere==str[i]){
            str[i]='*';
            troca++;
        }
        printf("%c", str[i]);
    }printf("Trocou a letra %c %d vezes", caractere,troca);
}

int main(){
    char *str;
    char caractere;
    int n;
    printf("Informe quantos caracteres tera, mais dois: ");
    scanf("%d", &n);
    str=(char*)malloc(n*sizeof(char));
    printf("Digite a setenca: ");
    setbuf(stdin,NULL);
    fgets(str,n,stdin);
    setbuf(stdin,NULL);
    printf("Digite um caractere: ");
    setbuf(stdin,NULL);
    scanf("%c", &caractere);
    func(n, caractere, str);
    return 0;
}
