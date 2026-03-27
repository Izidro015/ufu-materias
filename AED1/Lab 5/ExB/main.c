#include <stdio.h>
#include <stdlib.h>

/*b)Escreva um programa que lê um vetor de inteiros (a leitura pára quando o usuário digita-1),
remove valores consecutivos repetidos e mostra o vetor atualizado. O programa deve alocar
memória dinamicamente para utilizar o vetor, e o vetor de veter ao final da operação sempre
o tamanho exato dos elementos presentes nele. Permita ao usuário informar mais conjuntos de
números, e defina uma condição para o usuário parar a criação de novos vetores. O programa
deve, ao final de cada operação, mostrar o seu tamanho final.*/

int* removeRepetidos(int *vetor, int tamanho, int *novoTamanho) {
    int *vetorSemRepeticao = (int *)malloc(tamanho * sizeof(int));  // Aloca memória para o novo vetor
    int i,j,contem;
    int k=0;
    if (vetorSemRepeticao==NULL) {
        printf("Erro na alocacao de memoria.\n");
        exit(1);
    }
    for(i=0;i<tamanho;i++){
        contem=0;
        for(j=0;j<k;j++){
            if (vetor[i]==vetorSemRepeticao[j]) {
                contem=1;
                break;
            }
        }
        if(!contem){
            vetorSemRepeticao[k++]=vetor[i];
        }
    }
    *novoTamanho=k;
    return vetorSemRepeticao;
}

int main(){
    int tamanhoMaximo=1000;// Tamanho máximo para o vetor
    int *vetor=(int *)malloc(tamanhoMaximo*sizeof(int));
    int tamanhoAtual=0;
    if(vetor==NULL){
        printf("Erro na alocacao de memoria.\n");
        exit(1);
    }
    int continuar=1;
    while(continuar){
        int input;
        printf("Digite um valor para o vetor (-1 para parar): ");
        scanf("%d", &input);
        while(input!=-1){
            vetor[tamanhoAtual]=input;
            tamanhoAtual++;
            printf("Digite um valor para o vetor (-1 para parar): ");
            scanf("%d", &input);
        }
        int novoTamanho;
        int *vetorSemRepeticao = removeRepetidos(vetor, tamanhoAtual, &novoTamanho);
        printf("Vetor atualizado sem repeticoes:\n");
        for(int i=0;i<novoTamanho;i++){
            printf("%d ", vetorSemRepeticao[i]);
        }
        printf("\nTamanho final do vetor: %d\n", novoTamanho);
        free(vetorSemRepeticao);
        printf("Deseja adicionar mais um vetor? (1 para sim, 0 para nao): ");
        scanf("%d", &continuar);
        tamanhoAtual=0;
    }
    free(vetor);
    return 0;
}
