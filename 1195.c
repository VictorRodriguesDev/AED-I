#include <stdio.h>
#include <stdlib.h>

// estrutura do nó
typedef struct node {
    int value; // valor armazenado no nó
    struct node *left; // ponteiro para filho esquerdo
    struct node *right; // ponteiro para filho direito
} Node;

// cria um novo nó
Node* createNode(int value) {
    Node *newNode = (Node*) malloc(sizeof(Node)); // aloca memória para novo nó
    newNode->value = value; // define valor do nó
    newNode->left = NULL; // inicia filho esquerdo
    newNode->right = NULL; // inicia filho direito
    return newNode; // retorna nó criado
}

// insere valor na árvore
Node* insert(Node *root, int value) {
    if (root == NULL) { // se árvore estiver vazia
        return createNode(value); // cria nó inicial
    }
    if (value < root->value) { // vai para esquerda
        root->left = insert(root->left, value); // insere recursivamente
    } else { // vai para direita
        root->right = insert(root->right, value); // insere recursivamente
    }
    return root; // retorna raiz atualizada
}

// percurso pré-ordem
void preOrder(Node *root) {
    if (root == NULL) return; // caso base
    printf(" %d", root->value); // visita nó
    preOrder(root->left); // percorre esquerda
    preOrder(root->right); // percorre direita
}

// percurso em ordem
void inOrder(Node *root) {
    if (root == NULL) return; // caso base
    inOrder(root->left); // percorre esquerda
    printf(" %d", root->value); // visita nó
    inOrder(root->right); // percorre direita
}

// percurso pós-ordem
void postOrder(Node *root) {
    if (root == NULL) return; // caso base
    postOrder(root->left); // percorre esquerda
    postOrder(root->right); // percorre direita
    printf(" %d", root->value); // visita nó
}

int main() {
    int C; // número de casos
    scanf("%d", &C); // lê quantidade de casos

    for (int t = 1; t <= C; t++) { // loop dos casos
        int N; // quantidade de valores
        scanf("%d", &N); // lê N

        int *values = (int*) malloc(N * sizeof(int)); // aloca vetor dinamicamente

        for (int i = 0; i < N; i++) { // leitura dos valores
            scanf("%d", (values + i)); // armazena usando ponteiro
        }

        Node *root = NULL; // árvore inicia vazia

        for (int i = 0; i < N; i++) { // insere cada valor
            root = insert(root, *(values + i)); // insere usando ponteiro
        }

        printf("Case %d:\n", t); // imprime cabeçalho

        printf("Pre.:"); // prefixo
        preOrder(root); // imprime pré-ordem
        printf("\n"); // nova linha

        printf("In..:"); // prefixo
        inOrder(root); // imprime em ordem
        printf("\n"); // nova linha

        printf("Post:"); // prefixo
        postOrder(root); // imprime pós-ordem
        printf("\n\n"); // linha em branco

        free(values); // libera vetor
    }

    return 0; // fim
}
