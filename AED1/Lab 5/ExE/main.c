#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*e)Escreva um programa que leia 50 números sorteados pela Lotomania e em seguida
leia os 50 números apostados pelo usuário. O programa deve então comparar quantos
números o jogador acertou, e alocar espaço para um vetor de tamanho igual a
quantidade de números corretos, guardando esses números corretos nesse vetor.
Finalmente, o programa deve exibir na tela os números sorteados, os números que
o usuário acertou, e a porcentagem de acerto.*/

int main(){
    srand(time(NULL));//inicializa a semente do gerador de números aleatórios
    int numerosSorteados[50];
    int numerosApostados[50];
    int numerosCorretos[50];//para armazenar os números corretos
    int acertos = 0;//contador para a quantidade de acertos
    printf("Digite seus numeros apostados (entre 1 e 100):\n");
    for (int i=0;i<50;i++){
        scanf("%d", &numerosApostados[i]);
    }
    int j=0;//compara e guarda os números corretos
    for(int i=0;i<50;i++) {
        for(int k=0;k<50;k++){
            if(numerosSorteados[i]==numerosApostados[k]) {
                numerosCorretos[j]=numerosSorteados[i];
                acertos++;
                j++;
                break;
            }
        }
    }
    printf("Numeros sorteados: ");
    for(int i=0;i<50;i++){
        printf("%d ", numerosSorteados[i]);
    }
    printf("\nNumeros corretos: ");
    for(int i=0;i<acertos;i++){
        printf("%d ", numerosCorretos[i]);
    }
    float porcentagemAcerto=(float)acertos/50*100;
    printf("\nPorcentagem de acerto: %.2f%%\n", porcentagemAcerto);
    return 0;
}
