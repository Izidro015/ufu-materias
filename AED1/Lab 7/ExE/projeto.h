#ifndef PROJETO_H_INCLUDED
#define PROJETO_H_INCLUDED

typedef struct tad{
	char letra;
	int contagem;
}tad;

typedef struct lista lista;

lista *criar();

void leitura(lista *l);

void busca(lista *l);

void exibe(lista *l);

#endif // PROJETO_H_INCLUDED
