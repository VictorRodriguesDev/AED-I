#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int val;
    struct Node *left, *right;
} Node;

// Cria novo nó
Node* newNode(int val) {
    Node* node = (Node*) malloc(sizeof(Node));
    node->val = val;
    node->left = node->right = NULL;
    return node;
}

// Insere na BST
Node* insert(Node* root, int val) {
    if (root == NULL) return newNode(val);
    if (val < root->val)
        root->left = insert(root->left, val);
    else if (val > root->val)
        root->right = insert(root->right, val);
    // Se valor já existe, não insere duplicado
    return root;
}

// Busca na BST
int search(Node* root, int val) {
    if (root == NULL) return 0;
    if (val == root->val) return 1;
    else if (val < root->val) return search(root->left, val);
    else return search(root->right, val);
}

// Busca maior valor na subárvore (antecessor)
Node* maxValueNode(Node* node) {
    Node* current = node;
    while (current && current->right != NULL)
        current = current->right;
    return current;
}

// Remove elemento da BST
Node* removeNode(Node* root, int val) {
    if (root == NULL) return NULL;

    if (val < root->val)
        root->left = removeNode(root->left, val);
    else if (val > root->val)
        root->right = removeNode(root->right, val);
    else {
        // Achou o nó a remover
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        } else {
            // Nó com dois filhos: substitui pelo antecessor (maior da esquerda)
            Node* temp = maxValueNode(root->left);
            root->val = temp->val;
            root->left = removeNode(root->left, temp->val);
        }
    }
    return root;
}

// Percurso INFIXA (em ordem)
void inorder(Node* root, int* first) {
    if (root == NULL) return;
    inorder(root->left, first);
    if (*first) {
        printf("%d", root->val);
        *first = 0;
    } else {
        printf(" %d", root->val);
    }
    inorder(root->right, first);
}

// Percurso PREFIXA (pré-ordem)
void preorder(Node* root, int* first) {
    if (root == NULL) return;
    if (*first) {
        printf("%d", root->val);
        *first = 0;
    } else {
        printf(" %d", root->val);
    }
    preorder(root->left, first);
    preorder(root->right, first);
}

// Percurso POSFIXA (pós-ordem)
void postorder(Node* root, int* first) {
    if (root == NULL) return;
    postorder(root->left, first);
    postorder(root->right, first);
    if (*first) {
        printf("%d", root->val);
        *first = 0;
    } else {
        printf(" %d", root->val);
    }
}

// Libera memória da árvore
void freeTree(Node* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    Node* root = NULL;
    char cmd[10];
    int val;

    while (scanf("%s", cmd) != EOF) {
        if (strcmp(cmd, "I") == 0) {
            scanf("%d", &val);
            root = insert(root, val);
        } else if (strcmp(cmd, "R") == 0) {
            scanf("%d", &val);
            // Remove só se existir para evitar imprimir algo
            if (search(root, val)) {
                root = removeNode(root, val);
            }
        } else if (strcmp(cmd, "P") == 0) {
            scanf("%d", &val);
            if (search(root, val))
                printf("%d existe\n", val);
            else
                printf("%d nao existe\n", val);
        } else if (strcmp(cmd, "INFIXA") == 0) {
            int first = 1;
            inorder(root, &first);
            printf("\n");
        } else if (strcmp(cmd, "PREFIXA") == 0) {
            int first = 1;
            preorder(root, &first);
            printf("\n");
        } else if (strcmp(cmd, "POSFIXA") == 0) {
            int first = 1;
            postorder(root, &first);
            printf("\n");
        }
    }

    freeTree(root);
    return 0;
}
