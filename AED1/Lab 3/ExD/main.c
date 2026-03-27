#include <stdio.h>

/*d) Construa uma função que receba dois valores inteiros a e b, e retorne o quociente e o resto da divisão de a por b. Utilize
passagem de parâmetro por referência para retornar os resultados. A função deve retornar -1 caso não seja possível
realizar as operações e 0 caso seja possível. Crie um programa que utilize a função criada, tratando o retorno da função.*/

int dividir(int a, int b, int *quociente, int *resto) {
    if(b == 0){
        return -1;
    }
    *quociente=a/b;
    *resto=a%b;
    return 0;
}

int main() {
    int a, b, quociente, resto;
    printf("Digite o valor de a: ");
    scanf("%d", &a);
    printf("Digite o valor de b: ");
    scanf("%d", &b);
    int resultado=dividir(a, b, &quociente, &resto);
    if (resultado==0){
        printf("Quociente: %d\n", quociente);
        printf("Resto: %d\n", resto);
    } else{
        printf("Não é possível realizar as operações.\n");
    }
    return 0;
}
