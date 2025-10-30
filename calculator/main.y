
%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
%}

%token NUMBER NL
%right '^'
%left '*' '/'
%left '+' '-'
%%

stmt : expr NL { printf("Valid Expression\nResult = %d\n", $1); return 0; }
     ;

expr : expr '^' expr { $$ = (int)pow((double)$1, (double)$3); }
     | expr '*' expr { $$ = $1 * $3; }
     | expr '/' expr { $$ = $1 / $3; }
     | expr '+' expr { $$ = $1 + $3; }
     | expr '-' expr { $$ = $1 - $3; }
     | '(' expr ')' { $$ = $2; }
     | NUMBER { $$ = $1; }
     ;

%%

yyerror(char *s) {
    printf("Invalid Expression\n");
}