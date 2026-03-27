#include <stdio.h>
#define MAX_LIVROS 5

/*i) Faça um programa que cria uma estrutura livro, que contém os elementos título, ano de edição, número de páginas
e preço. Criar uma variável dessa estrutura que é um vetor de 5 elementos. Ler os valores para a estrutura e
imprimir a média do número de páginas do livros*/

struct Livro {
    char titulo[100];
    int ano_edicao;
    int num_paginas;
    float preco;
};

int main() {
    struct Livro livros[MAX_LIVROS];
    int total_paginas = 0;
    printf("Digite os dados dos %d livros:\n", MAX_LIVROS);
    for(int i=0;i<MAX_LIVROS;i++){// Le os valores para a estrutura livro.
        printf("Livro %d:\n", i + 1);
        printf("Título: ");
        fgets(livros[i].titulo, sizeof(livros[i].titulo), stdin);
        printf("Ano de edição: ");
        scanf("%d", &livros[i].ano_edicao);
        printf("Número de páginas: ");
        scanf("%d", &livros[i].num_paginas);
        printf("Preço: ");
        scanf("%f", &livros[i].preco);
        while (getchar() != '\n');
    }

    for(int i=0;i<MAX_LIVROS;i++){// Calcula a média do número de páginas dos livros
        total_paginas += livros[i].num_paginas;
    }
    float media_paginas = (float)total_paginas / MAX_LIVROS;
    printf("A média do número de páginas dos livros é: %.2f\n", media_paginas);
    return 0;
}
