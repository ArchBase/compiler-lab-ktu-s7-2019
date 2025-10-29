%{
#include <stdio.h>

int chars = 0;
int words = 0;
int lines = 0;
%}

%%
\n          { lines++; chars++; }
[^ \t\n]+   { words++; chars += yyleng; }
.           { chars++; }

%%
int main(int argc, char *argv[]) {
    printf("Starting analysis. Press Ctrl+D (or Ctrl-Z on Windows) to finish input.\n");
    yylex();

    printf("\n--- Results ---\n");
    printf("Lines: %d\n", lines);
    printf("Words: %d\n", words);
    printf("Characters: %d\n", chars);

    return 0;
}

int yywrap() {
    return 1;
}
