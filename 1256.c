#include <stdio.h>
#include <stdlib.h>

int main() {
    int N; 
    scanf("%d", &N); // lê número de casos

    while (N--) { // processa cada caso
        int M, C;
        scanf("%d %d", &M, &C); // lê M (tamanho da tabela) e C (quantidade de chaves)

        int **hash = (int **)malloc(M * sizeof(int *)); // aloca tabela hash
        int *size = (int *)malloc(M * sizeof(int)); // armazena tamanhos das listas

        for (int i = 0; i < M; i++) {
            hash[i] = NULL; // inicia listas
            size[i] = 0; // tamanho inicial 0
        }

        for (int i = 0; i < C; i++) {
            int x;
            scanf("%d", &x); // lê chave
            int h = x % M; // calcula h(x) = x mod M

            size[h]++; // aumenta tamanho da lista
            hash[h] = (int *)realloc(hash[h], size[h] * sizeof(int)); // realoca lista
            hash[h][size[h] - 1] = x; // insere chave
        }

        for (int i = 0; i < M; i++) {
            printf("%d -> ", i); // imprime índice
            for (int j = 0; j < size[i]; j++) {
                printf("%d -> ", hash[i][j]); // imprime chaves encadeadas
            }
            printf("\\"); // marca final da lista
            printf("\n");
        }

        if (N) printf("\n"); // linha em branco entre casos

        for (int i = 0; i < M; i++) {
            free(hash[i]); // libera listas
        }
        free(hash); // libera tabela
        free(size); // libera vetor de tamanhos
    }

    return 0;
}
