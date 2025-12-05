#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char value; //
    struct node *left; //
    struct node *right; //
} Node;

Node* createNode(char v) {
    Node *n = (Node*) malloc(sizeof(Node)); //
    n->value = v; //
    n->left = NULL; //
    n->right = NULL; //
    return n; //
}

Node* insert(Node *root, char v) {
    if (root == NULL) return createNode(v); //
    if (v < root->value) root->left = insert(root->left, v); //
    else if (v > root->value) root->right = insert(root->right, v); //
    return root; //
}

int search(Node *root, char v) {
    if (root == NULL) return 0; //
    if (v == root->value) return 1; //
    if (v < root->value) return search(root->left, v); //
    return search(root->right, v); //
}

void printPre(Node *root, int *first) {
    if (!root) return; //
    if (!*first) printf(" "); else *first = 0; //
    printf("%c", root->value); //
    printPre(root->left, first); //
    printPre(root->right, first); //
}

void printIn(Node *root, int *first) {
    if (!root) return; //
    printIn(root->left, first); //
    if (!*first) printf(" "); else *first = 0; //
    printf("%c", root->value); //
    printIn(root->right, first); //
}

void printPos(Node *root, int *first) {
    if (!root) return; //
    printPos(root->left, first); //
    printPos(root->right, first); //
    if (!*first) printf(" "); else *first = 0; //
    printf("%c", root->value); //
}

void freeTree(Node *root) {
    if (!root) return; //
    freeTree(root->left); //
    freeTree(root->right); //
    free(root); //
}

int main() {
    Node *root = NULL; //
    char cmd[20]; //

    while (scanf("%s", cmd) != EOF) { //
        
        if (strcmp(cmd, "I") == 0) { //
            char v; //
            scanf(" %c", &v); //
            root = insert(root, v); //
        }
        else if (strcmp(cmd, "P") == 0) { //
            char v; //
            scanf(" %c", &v); //
            if (search(root, v)) printf("%c existe\n", v); //
            else printf("%c nao existe\n", v); //
        }
        else if (strcmp(cmd, "PREFIXA") == 0) { //
            int first = 1; //
            printPre(root, &first); //
            printf("\n"); //
        }
        else if (strcmp(cmd, "INFIXA") == 0) { //
            int first = 1; //
            printIn(root, &first); //
            printf("\n"); //
        }
        else if (strcmp(cmd, "POSFIXA") == 0) { //
            int first = 1; //
            printPos(root, &first); //
            printf("\n"); //
        }
    }

    freeTree(root); //
    return 0; //
}
