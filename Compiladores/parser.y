%{
#include <stdio.h>
#include "Lexer.h"
#define YYSTYPE double
void yyerror (char *);
int yylex();
%}

%token NUM
%left '+' '-'
%left '*' '/'
%right NEGAR

%%
lines : lines expr '\n'  { printf("= %.2f\n", $2); }
      | lines '\n'
      | /* vazio */
      | error '\n'       { yyerror("Erro na ultima linha"); yyerrok; }
      ;
expr  : expr '+' expr    { $$ = $1 + $3; printf("+ "); }
      | expr '-' expr    { $$ = $1 - $3; printf("- "); }
      | expr '*' expr    { $$ = $1 * $3; printf("* "); }
      | expr '/' expr    { $$ = $1 / $3; printf("/ "); }
      | '(' expr ')'     { $$ = $2; }
      | '-' expr %prec NEGAR { $$ = -$2; printf("(-) "); }
      | NUM              { $$ = $1; printf("%.2f ", $1); }
      ;
%%

void yyerror(char * s) { fprintf (stderr, "%s\n", s); }

int main(void) {
    printf("Digite a expressao desejada:\n");
    return yyparse();
}