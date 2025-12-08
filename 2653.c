#include <stdio.h>
#include <stdlib.h>

typedef struct TrieNode {
    struct TrieNode* child[2]; // 0 para '(', 1 para ')'
    int isEnd;
} TrieNode;

TrieNode* createNode() {
    TrieNode* node = (TrieNode*) malloc(sizeof(TrieNode));
    node->child[0] = node->child[1] = NULL;
    node->isEnd = 0;
    return node;
}

int insert(TrieNode* root, char* str) {
    TrieNode* curr = root;
    for (int i = 0; str[i]; i++) {
        int idx = (str[i] == '(') ? 0 : 1;
        if (curr->child[idx] == NULL) {
            curr->child[idx] = createNode();
        }
        curr = curr->child[idx];
    }
    if (curr->isEnd) {
        // Já existia essa string
        return 0;
    } else {
        curr->isEnd = 1;
        return 1; // Inseriu uma nova string distinta
    }
}

void freeTrie(TrieNode* root) {
    if (!root) return;
    freeTrie(root->child[0]);
    freeTrie(root->child[1]);
    free(root);
}

int main() {
    TrieNode* root = createNode();
    char buffer[1000005]; // suficiente para as strings grandes
    int distinct = 0;

    while (fgets(buffer, sizeof(buffer), stdin)) {
        // Remove \n
        for (int i = 0; buffer[i]; i++) {
            if (buffer[i] == '\n') {
                buffer[i] = 0;
                break;
            }
        }
        if (buffer[0] == 0) continue; // linha vazia ignora

        distinct += insert(root, buffer);
    }

    printf("%d\n", distinct);

    freeTrie(root);
    return 0;
}
