#include <stdio.h>
#include <string.h>
#include <ctype.h>

int tempCount = 1;

// Create new temporary variable name
char *newTemp() {
    static char temp[10];
    sprintf(temp, "t%d", tempCount++);
    return temp;
}

// Forward declaration
char *generateTAC(char expr[], int *i);

// Parse one operand: either variable, digit, or bracketed expression
char *parseOperand(char expr[], int *i) {
    if (expr[*i] == '(') {
        (*i)++; // skip '('
        return generateTAC(expr, i);
    } else {
        static char op[10];
        sprintf(op, "%c", expr[*i]);
        (*i)++;
        return op;
    }
}

// Recursively generate TAC for a sub-expression inside parentheses
char *generateTAC(char expr[], int *i) {
    char *arg1 = parseOperand(expr, i);
    char op = expr[*i];
    (*i)++;
    char *arg2 = parseOperand(expr, i);

    if (expr[*i] == ')')
        (*i)++; // skip ')'

    char *temp = newTemp();
    printf("%s = %s %c %s\n", temp, arg1, op, arg2);
    return temp;
}

// Main
int main() {
    char expr[] = "((a+b)*(c-d))";
    int i = 0;
    generateTAC(expr, &i);
    return 0;
}
