%{
#include <stdio.h>
%}

%%

"//".*                         { /* swallow single-line comment */ }

"/*"([^*]|\*+[^*/])*\*+"/"     { /* swallow C-style block comment */ }

.|\n                           { ECHO; }

%%

int main(void)
{
    yyin = fopen("abc.txt", "r");
    if (!yyin) {
        perror("abc.txt");
        return 1;
    }
    yylex();
    fclose(yyin);
    return 0;
}
int yywrap(){
    return 1;
}