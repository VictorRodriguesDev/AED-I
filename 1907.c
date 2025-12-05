#include <stdio.h>
#include <stdlib.h>

/*
  Solução para o problema de componentes ('.') em matriz n x m.
  - DFS iterativo com pilha dinâmica de (i,j).
  - Matrizes armazenadas em blocos contíguos e acessadas por ponteiros.
*/

int main() {
    int n, m; // dimensões
    if (scanf("%d %d", &n, &m) != 2) return 0; // lê dimensões

    // aloca bloco contíguo para o mapa (n * m chars)
    char *map = (char*) malloc(n * m * sizeof(char));
    if (!map) return 1;

    // buffer temporário para ler cada linha (m chars + '\0')
    char *buf = (char*) malloc((m + 1) * sizeof(char));
    if (!buf) { free(map); return 1; }

    // lê linha por linha e copia para bloco contíguo
    for (int i = 0; i < n; i++) {
        scanf("%s", buf); // lê string da linha (sem espaços)
        for (int j = 0; j < m; j++) {
            *(map + i * m + j) = *(buf + j); // copia por ponteiro
        }
    }

    free(buf); // não precisamos mais do buffer

    // aloca vetor de visitados contíguo (n * m ints) e inicializa com 0
    int *vis = (int*) calloc(n * m, sizeof(int));
    if (!vis) { free(map); return 1; }

    // pilha dinâmica para DFS: armazenará pares (i,j) como inteiros
    // capacidade máxima n*m
    int maxsz = n * m;
    int *stack = (int*) malloc(2 * maxsz * sizeof(int)); // cada elemento = (i,j)
    if (!stack) { free(map); free(vis); return 1; }

    int components = 0;

    // deslocamentos (4 direções)
    const int di[4] = { -1, 1, 0, 0 };
    const int dj[4] = { 0, 0, -1, 1 };

    // percorre todos os vértices
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {

            // ponteiro para caractere atual e visited
            char cur = *(map + i * m + j);
            if (cur == '.' && *(vis + i * m + j) == 0) {
                // nova componente encontrada
                components++;

                // inicia DFS iterativo a partir de (i,j)
                int top = 0; // pilha vazia
                *(stack + 2 * top + 0) = i; // empilha linha
                *(stack + 2 * top + 1) = j; // empilha coluna
                top++;

                // marca visitado
                *(vis + i * m + j) = 1;

                while (top > 0) {
                    // pop
                    top--;
                    int ci = *(stack + 2 * top + 0);
                    int cj = *(stack + 2 * top + 1);

                    // explora 4 vizinhos
                    for (int k = 0; k < 4; k++) {
                        int ni = ci + di[k];
                        int nj = cj + dj[k];

                        // checa limites
                        if (ni < 0 || ni >= n || nj < 0 || nj >= m) continue;

                        // se ponto '.' e não visitado, empilha e marca
                        if (*(map + ni * m + nj) == '.' && *(vis + ni * m + nj) == 0) {
                            *(vis + ni * m + nj) = 1; // marca
                            *(stack + 2 * top + 0) = ni; // empilha ni
                            *(stack + 2 * top + 1) = nj; // empilha nj
                            top++;
                        }
                    }
                }
            }
        }
    }

    // imprime resultado
    printf("%d\n", components);

    // libera memória
    free(stack);
    free(vis);
    free(map);

    return 0;
}
