#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Node {
    char value;
    struct Node *left, *right;
    int connector; // unique number for internal nodes
} Node;

int connectorCount = 0;

// Create a new node
Node* newNode(char value) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->value = value;
    n->left = n->right = NULL;
    n->connector = 0;
    return n;
}

// Recursive parser
Node* parse(char **expr) {
    if (**expr == '(') {
        (*expr)++; // skip '('
        Node* left = parse(expr);
        char op = *(*expr)++;
        Node* right = parse(expr);
        (*expr)++; // skip ')'
        Node* root = newNode(op);
        root->left = left;
        root->right = right;
        root->connector = ++connectorCount; // assign connector id
        return root;
    } else {
        char val = *(*expr)++;
        return newNode(val);
    }
}

// Print the connections
void printConnections(Node* root) {
    if (!root || !root->left || !root->right) return;

    printf("%c <- %%%d(%c) -> %c\n",
           root->left->value,
           root->connector,
           root->value,
           root->right->value);

    // recurse down both sides
    printConnections(root->left);
    printConnections(root->right);
}

// Free memory
void freeTree(Node* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    char expr1[] = "(d=(a+(b*c)))";
    char *p = expr1;

    Node* tree = parse(&p);

    printf("Connections for: %s\n\n", expr1);
    printConnections(tree);

    freeTree(tree);
    return 0;
}
