#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int u, v;
    int w;
} Aresta;

int compara(const void *a, const void *b) {
    return ((Aresta*)a)->w - ((Aresta*)b)->w; // ordena por peso crescente
}

int find(int x, int *parent) {
    if (parent[x] != x) parent[x] = find(parent[x], parent); // path compression
    return parent[x];
}

void unite(int a, int b, int *parent, int *rank) {
    a = find(a, parent); // encontra líder de a
    b = find(b, parent); // encontra líder de b
    if (a != b) {
        if (rank[a] < rank[b]) parent[a] = b; // une pelo rank
        else if (rank[a] > rank[b]) parent[b] = a;
        else {
            parent[b] = a;
            rank[a]++; // aumenta rank
        }
    }
}

int main() {
    while (1) {
        int m, n;
        scanf("%d %d", &m, &n); // lê número de casas e estradas
        if (m == 0 && n == 0) break; // condição de parada

        Aresta *arestas = malloc(n * sizeof(Aresta)); // vetor de arestas
        int soma_total = 0; // soma total dos pesos

        for (int i = 0; i < n; i++) {
            scanf("%d %d %d", &arestas[i].u, &arestas[i].v, &arestas[i].w); // lê aresta
            soma_total += arestas[i].w; // soma o peso total
        }

        qsort(arestas, n, sizeof(Aresta), compara); // ordena arestas por peso

        int *parent = malloc(m * sizeof(int)); // DSU parent
        int *rank = calloc(m, sizeof(int)); // DSU rank

        for (int i = 0; i < m; i++) parent[i] = i; // inicializa DSU

        int custo_mst = 0; // custo final da MST

        for (int i = 0; i < n; i++) {
            int u = arestas[i].u;
            int v = arestas[i].v;

            if (find(u, parent) != find(v, parent)) { // se não formam ciclo
                unite(u, v, parent, rank); // une conjuntos
                custo_mst += arestas[i].w; // adiciona peso à MST
            }
        }

        free(parent); // libera estrutura DSU
        free(rank); // libera vetor de ranks
        free(arestas); // libera vetor de arestas

        printf("%d\n", soma_total - custo_mst); // economia total
    }

    return 0;
}
