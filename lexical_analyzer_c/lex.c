#include <stdio.h>
#include <stdlib.h>
#include <string.h> // We still need this for strcmp and strlen, which are fundamental.
// Removed include for <ctype.h>
// Removed include for <stdbool.h>

// --- Configuration ---
// List of keywords supported by this simple analyzer
const char *keywords[] = {
    "int", "float", "if", "else", "while", "return", "void", "for"
};
const int NUM_KEYWORDS = sizeof(keywords) / sizeof(keywords[0]);

// List of simple operators
const char *operators = "+-*/=";

// List of simple special characters
const char *special_chars = ";(),{}[]";

// --- Custom Character Classification Functions (replacing ctype.h) ---

/*
 * Custom check for common whitespace characters (space, tab, newline, carriage return).
 * Returns 1 if it is whitespace, 0 otherwise.
 */
int my_isspace(char c) {
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

/*
 * Custom check for alphabetic characters.
 * Returns 1 if it is an alphabet, 0 otherwise.
 */
int my_isalpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

/*
 * Custom check for numeric digits.
 * Returns 1 if it is a digit, 0 otherwise.
 */
int my_isdigit(char c) {
    return (c >= '0' && c <= '9');
}

/*
 * Custom check for alphanumeric characters.
 * Returns 1 if it is alphanumeric, 0 otherwise.
 */
int my_isalnum(char c) {
    return my_isalpha(c) || my_isdigit(c);
}


// --- Lexical Analyzer Helper Functions ---

/*
 * Checks if a given string is a predefined keyword.
 * Returns 1 if the string is a keyword, 0 otherwise.
 */
int is_keyword(const char *str) {
    for (int i = 0; i < NUM_KEYWORDS; i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return 1; // True
        }
    }
    return 0; // False
}

/*
 * Checks if a character is a simple operator.
 * Replaces strchr with a manual loop.
 * Returns 1 if it is an operator, 0 otherwise.
 */
int is_operator(char c) {
    int i = 0;
    while (operators[i] != '\0') {
        if (operators[i] == c) {
            return 1; // True
        }
        i++;
    }
    return 0; // False
}

/*
 * Checks if a character is a simple special character.
 * Replaces strchr with a manual loop.
 * Returns 1 if it is a special character, 0 otherwise.
 */
int is_special_char(char c) {
    int i = 0;
    while (special_chars[i] != '\0') {
        if (special_chars[i] == c) {
            return 1; // True
        }
        i++;
    }
    return 0; // False
}

/*
 * Performs the lexical analysis on the input string.
 */
void analyze_lexemes(const char *input) {
    int len = strlen(input);
    int i = 0;

    printf("--- Lexical Analysis Output ---\n");

    while (i < len) {
        // 1. Skip whitespace using custom function
        if (my_isspace(input[i])) {
            i++;
            continue;
        }

        // 2. Handle single-character tokens (Operators and Special Characters)
        if (is_operator(input[i])) {
            printf("%c - operator\n", input[i]);
            i++;
            continue;
        }
        
        if (is_special_char(input[i])) {
            printf("%c - special character\n", input[i]);
            i++;
            continue;
        }

        // 3. Handle Identifiers and Keywords
        if (my_isalpha(input[i]) || input[i] == '_') {
            char token[256]; // Buffer for the token
            int j = 0;
            
            // Read all alphanumeric characters (or underscore) using custom function
            while (i < len && (my_isalnum(input[i]) || input[i] == '_')) {
                token[j++] = input[i++];
            }
            token[j] = '\0'; // Null-terminate the token

            // Check if it's a keyword or an identifier
            if (is_keyword(token)) {
                printf("%s - keyword\n", token);
            } else {
                printf("%s - identifier\n", token);
            }
            continue;
        }

        // 4. Handle Numbers (Integers and Floats)
        // Check if current char is a digit, or if it's a decimal point followed by a digit.
        if (my_isdigit(input[i]) || (input[i] == '.' && my_isdigit(input[i+1]))) {
            char token[256]; // Buffer for the token
            int j = 0;
            int is_float = 0; // Use int for boolean logic (0 = false, 1 = true)

            // Read digits and a single decimal point
            while (i < len && (my_isdigit(input[i]) || input[i] == '.')) {
                if (input[i] == '.') {
                    is_float = 1; // Mark as float if decimal point is found (1 = true)
                }
                token[j++] = input[i++];
            }
            token[j] = '\0'; // Null-terminate the token
            
            // For simplicity, we just classify it as a number here
            printf("%s - number\n", token);
            
            continue;
        }

        // 5. Handle unexpected characters
        // If we reach here, it's an unrecognized character.
        fprintf(stderr, "Error: Unrecognized character or start of token: '%c' at position %d\n", input[i], i);
        i++; // Move past the error character
    }
}

int main() {
    // The input string specified by the user
    const char *source_code = "int a = b + 20.5;";

    printf("Input: %s\n\n", source_code);
    
    // Perform the analysis
    analyze_lexemes(source_code);
    
    return 0;
}
