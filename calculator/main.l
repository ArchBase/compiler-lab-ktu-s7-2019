LEX PROGRAM:
%{
#include "y.tab.h"
#include <stdlib.h>
%}

%%
[0-9]+ { yylval = atoi(yytext); return NUMBER; }
[+\-*/^] { return yytext[0]; }
[()] { return yytext[0]; }
\n { return NL; }
[\t ] { /* skip whitespace */ }
. { return yytext[0]; }

%%

int yywrap() {
    return 1;
}

int main() {
    printf("Enter an expression: ");
    yyparse();
    return 0;
}