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
            parent[b] = a; // une e aumenta rank
            rank[a]++;
        }
    }
}

int main() {
    int n, m;

    while (1) {
        scanf("%d %d", &n, &m); // lê número de cidades e estradas
        if (n == 0 && m == 0) break; // condição de parada

        Aresta *arestas = malloc(m * sizeof(Aresta)); // vetor de arestas

        for (int i = 0; i < m; i++)
            scanf("%d %d %d", &arestas[i].u, &arestas[i].v, &arestas[i].w); // lê aresta

        qsort(arestas, m, sizeof(Aresta), compara); // ordena por peso

        int *parent = malloc(n * sizeof(int)); // DSU parent
        int *rank = calloc(n, sizeof(int)); // DSU rank

        for (int i = 0; i < n; i++) parent[i] = i; // inicializa DSU

        int peso_mst = 0; // soma da MST

        for (int i = 0; i < m; i++) {
            if (find(arestas[i].u, parent) != find(arestas[i].v, parent)) { // se não forma ciclo
                unite(arestas[i].u, arestas[i].v, parent, rank); // une conjuntos
                peso_mst += arestas[i].w; // adiciona peso
            }
        }

        free(parent); // libera parent
        free(rank); // libera rank
        free(arestas); // libera arestas

        printf("%d\n", peso_mst); // imprime somente o custo da MST
    }

    return 0;
}
