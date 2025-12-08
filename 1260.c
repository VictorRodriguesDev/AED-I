#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode {
    char name[35];
    int count;
    struct TreeNode *left, *right;
} TreeNode;

// Insere ou incrementa
TreeNode* insert(TreeNode* root, char *name) {
    if (root == NULL) {
        TreeNode* node = malloc(sizeof(TreeNode));
        strcpy(node->name, name);
        node->count = 1;
        node->left = node->right = NULL;
        return node;
    }
    int cmp = strcmp(name, root->name);
    if (cmp == 0) {
        root->count++;
    } else if (cmp < 0) {
        root->left = insert(root->left, name);
    } else {
        root->right = insert(root->right, name);
    }
    return root;
}

// Conta total de árvores (soma counts)
int totalTrees = 0;

// Imprime em ordem alfabética (infixa)
void inorderPrint(TreeNode* root) {
    if (root == NULL) return;
    inorderPrint(root->left);
    printf("%s %.4lf\n", root->name, (root->count * 100.0) / totalTrees);
    inorderPrint(root->right);
}

void freeTree(TreeNode* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    int T;
    scanf("%d\n", &T);

    for (int t = 0; t < T; t++) {
        TreeNode* root = NULL;
        totalTrees = 0;

        char line[35];
        while (fgets(line, sizeof(line), stdin)) {
            if (line[0] == '\n') break;
            line[strcspn(line, "\n")] = 0;

            root = insert(root, line);
            totalTrees++;
        }

        if (t > 0) printf("\n");
        inorderPrint(root);

        freeTree(root);
    }

    return 0;
}
