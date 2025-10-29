
%{
#include <stdio.h>

int pos = 0, posf = 0, neg = 0, negf = 0;
%}
%%
[0-9]+            { pos++; }
-[0-9]+           { neg++; }
[0-9]+\.[0-9]+    { posf++; }
-[0-9]+\.[0-9]+   { negf++; }
%%
int main()
{
    FILE *fp = fopen("abc.txt", "r");

    yyin = fp;
    yylex();
    fclose(fp);

    printf("POSITIVE NOS: %d\n", pos);
    printf("POSITIVE FRACTION NOS: %d\n", posf);
    printf("NEGATIVE NOS: %d\n", neg);
    printf("NEGATIVE FRACTION NOS: %d\n", negf);

    return 0;
}

int yywrap(){
    return 1;
}