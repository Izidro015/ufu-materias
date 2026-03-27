#ifndef STRING_H_INCLUDED
#define STRING_H_INCLUDED

typedef struct manipulastring manipulastring;

manipulastring *criar();

void associa(manipulastring *s);

int calculatamanho(manipulastring *s);

int contagem(manipulastring *s, char c);

void exibe(manipulastring *s);

#endif // STRING_H_INCLUDED
