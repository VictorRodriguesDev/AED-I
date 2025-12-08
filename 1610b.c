#include <stdio.h>
#include <stdlib.h>

#define WHITE 0
#define GRAY 1
#define BLACK 2

int ciclo; // indica ciclo encontrado

void dfs(int u, int *cor, int **adj, int *tam) {
    *(cor + u) = GRAY; // marca visitando

    int i = 0; // índice dos vizinhos
    while (i < *(tam + u)) {
        int v = *(*(adj + u) + i); // pega vizinho via ponteiro

        if (*(cor + v) == GRAY) ciclo = 1; // encontrou ciclo
        else if (*(cor + v) == WHITE) dfs(v, cor, adj, tam); // continua dfs

        i++; // próximo vizinho
    }

    *(cor + u) = BLACK; // marca finalizado
}

int main() {
    int T;
    scanf("%d", &T); // número de casos

    while (T--) {
        int N, M;
        scanf("%d %d", &N, &M); // lê nós e arestas

        int **adj = (int **)malloc(N * sizeof(int *)); // ponteiro p/ listas
        int *tam = (int *)calloc(N, sizeof(int)); // tamanho de cada lista
        int *cor = (int *)malloc(N * sizeof(int)); // cor dos nós

        int i = 0;
        while (i < N) {
            *(adj + i) = NULL; // inicia listas
            *(cor + i) = WHITE; // inicia cor
            i++;
        }

        int k = 0;
        while (k < M) {
            int a, b;
            scanf("%d %d", &a, &b);
            a--; b--; // 0-based

            *(tam + a) += 1; // aumenta tamanho

            *(adj + a) = (int *)realloc(*(adj + a), (*(tam + a)) * sizeof(int)); // realoca

            *(*(adj + a) + (*(tam + a) - 1)) = b; // insere vizinho via ponteiro

            k++;
        }

        ciclo = 0; // sem ciclo inicialmente

        int u = 0;
        while (u < N && !ciclo) {
            if (*(cor + u) == WHITE) dfs(u, cor, adj, tam); // inicia DFS
            u++;
        }

        if (ciclo) printf("SIM\n"); // grafo tem ciclo
        else printf("NAO\n"); // acíclico

        int j = 0;
        while (j < N) {
            free(*(adj + j)); // libera lista
            j++;
        }

        free(adj); // libera ponteiro de listas
        free(tam); // libera tamanhos
        free(cor); // libera cores
    }

    return 0;
}
