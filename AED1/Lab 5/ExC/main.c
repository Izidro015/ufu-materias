#include <stdio.h>
#include <stdlib.h>

/*c) Escreva um programa que aloque dinamicamente uma matriz (de inteiros) de dimensões definidas pelo usuário, e
preencha a matriz com valores informados pelo usuário. O programa deve então construir um outro vetor que contenha
exatamente os números que aparecem na matriz. Por exemplo, caso a matriz seja [[1,3,5],[2,3,1],[1,1,6]], o vetor
resultante será [1,3,5,2,6]. O vetor não precisa estar ordenado ao final da execução, e seu tamanho deve coincidir com
o necessário para o resultado.*/

int main(){
    int linhas, colunas, i, j;
    printf("Digite a quantidade de linhas da matriz: ");
    scanf("%d", &linhas);
    printf("Digite a quantidade de colunas da matriz: ");
    scanf("%d", &colunas);
    int **mat=(int **)malloc(linhas*sizeof(int *));//aloca memória para as linhas da matriz
    if (mat==NULL){
        printf("Erro na alocação de memória.\n");
        exit(1);//encerra o programa em caso de falha na alocação
    }
    for(i=0;i<linhas;i++){
        mat[i]=(int *)malloc(colunas*sizeof(int));//aloca memória para cada coluna da matriz
        if (mat[i]==NULL){
            printf("Erro na alocação de memória.\n");
            exit(1);
        }
    }
    for(i=0;i<linhas;i++){
        for(j=0;j<colunas;j++){
            printf("Digite um valor: ");
            scanf("%d", &mat[i][j]);
        }
    }
    // Cria um vetor auxiliar para verificar duplicatas
    int *vetorAux = (int *)calloc(10000, sizeof(int));  // Supondo que os valores da matriz estão entre 0 e 9999
    // Constrói um vetor para armazenar os números únicos da matriz
    int *vetor=(int *)malloc(linhas*colunas*sizeof(int));
    int k=0;//indice para percorrer o vetor
    for(i=0;i<linhas;i++){
        for(j=0;j<colunas;j++){
            int valor=mat[i][j];
            if(!vetorAux[valor]){
                vetor[k]=valor;
                vetorAux[valor]=1;//marca o valor como adicionado
                k++;
            }
        }
    }
    printf("Vetor resultante:\n");
    for(i=0;i<k;i++){
        printf("%d ", vetor[i]);
    }
    printf("\n");
    for (i=0;i<linhas;i++){
        free(mat[i]);
    }
    free(mat);
    free(vetor);
    free(vetorAux);
    return 0;
}
