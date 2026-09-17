%option noyywrap
%option outfile="Lexer.c" header-file="Lexer.h"

%{
#define YYSTYPE double
#include "y.tab.h"
#include <stdlib.h>
%}
DIGITO [0-9]
NUM    {DIGITO}+([.]{DIGITO}+)?

%%

[ \t]   { /* ignora espaços e tabulações */ }
{NUM}   { yylval = atof(yytext); return NUM; }
\n      { return '\n'; }
.       { return yytext[0]; }
%%