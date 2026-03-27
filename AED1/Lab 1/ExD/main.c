#include <stdio.h>
#include <stdlib.h>

/*d) Faça um programa que receba três notas de um aluno, calcule e mostre a média aritmética. Considerando que, se o aluno tirar média entre 0 e 3, ele está REPROVADO, se ele tirar entre 3 e 7, ele está de EXAME FINAL, e se ele
tirar entre 7 e 10, ele está APROVADO, calcule, para alunos de EXAME FINAL, qual deverá ser a nota tirada neste exame, para que o aluno seja aprovado, considerando que a média entre a nota do exame e a média ao longo do semestre deve ser 6,0.*/

int main(){
    float n1,n2,n3;//n=nota
    printf("Digite a nota da p1: ");
    scanf("%f", &n1);//nota 1
    if(n1<0||n1>10){
        printf("Numero invalido");
        exit(0);
    }
    printf("Digite a nota da p2: ");
    scanf("%f", &n2);//nota 2
    if(n2<0||n2>10){
        printf("Numero invalido");
        exit(0);
    }
    printf("Digite a nota da p3: ");
    scanf("%f", &n3);//nota 3
    if(n3<0||n3>10){
        printf("Numero invalido");
        exit(0);
    }
    float media_arit;
    media_arit=(n1+n2+n3)/3;
    printf("A media final eh: %0.2f\n", media_arit);//calcula a media
    if(media_arit<=3){
        printf("\nReprovado\n");
    }else if(media_arit>3 && media_arit<7){
        printf("\nExame final\n");
        float nota_necessaria;
        nota_necessaria=(12-media_arit);
        printf("A nota necessaria no exame para passar eh: %0.2f", nota_necessaria);
    }else{
        printf("\nAprovado\n");
    }
    return 0;
}
