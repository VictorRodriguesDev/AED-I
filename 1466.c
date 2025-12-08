#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    struct No *esq, *dir;
} No;

No* inserir(No *raiz, int v) {
    if (raiz == NULL) {
        raiz = (No*) malloc(sizeof(No)); // aloca novo nó
        raiz->valor = v; // define valor
        raiz->esq = raiz->dir = NULL; // inicializa filhos
        return raiz;
    }

    if (v < raiz->valor) raiz->esq = inserir(raiz->esq, v); // insere esquerda
    else raiz->dir = inserir(raiz->dir, v); // insere direita

    return raiz; // retorna raiz atualizada
}

void nivel(No *raiz) {
    if (raiz == NULL) return; // árvore vazia

    No **fila = (No**) malloc(2000 * sizeof(No*)); // fila para BFS
    int ini = 0, fim = 0; // ponteiros fila

    fila[fim++] = raiz; // coloca raiz na fila
    int primeiro = 1; // controla espaço

    while (ini < fim) {
        No *atual = fila[ini++]; // retira da fila

        if (primeiro) { // primeiro elemento
            printf("%d", atual->valor); // imprime sem espaço
            primeiro = 0; 
        } else {
            printf(" %d", atual->valor); // imprime com espaço
        }

        if (atual->esq != NULL) fila[fim++] = atual->esq; // adiciona esquerda
        if (atual->dir != NULL) fila[fim++] = atual->dir; // adiciona direita
    }

    free(fila); // libera fila
}

void liberar(No *raiz) {
    if (raiz == NULL) return; // caso base
    liberar(raiz->esq); // libera esquerda
    liberar(raiz->dir); // libera direita
    free(raiz); // libera nó atual
}

int main() {
    int C;
    scanf("%d", &C); // lê número de casos

    for (int caso = 1; caso <= C; caso++) {
        int N;
        scanf("%d", &N); // lê quantidade de valores

        No *raiz = NULL; // raiz começa vazia

        for (int i = 0; i < N; i++) {
            int v;
            scanf("%d", &v); // lê valor
            raiz = inserir(raiz, v); // insere na árvore
        }

        printf("Case %d:\n", caso); // imprime caso
        nivel(raiz); // percorre em nível
        printf("\n\n"); // quebra linha dupla

        liberar(raiz); // libera memória da árvore
    }

    return 0; // fim do programa
}
