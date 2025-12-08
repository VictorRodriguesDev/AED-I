#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

typedef struct {
    int u, v; // extremidades
    int w;    // peso/distância
} Edge;

int cmpEdge(const void *a, const void *b) {
    Edge *ea = (Edge*) a;
    Edge *eb = (Edge*) b;
    return ea->w - eb->w; // ordena por peso crescente
}

int find_set(int *parent, int x) {
    if (*(parent + x) != x) *(parent + x) = find_set(parent, *(parent + x)); // path compression
    return *(parent + x);
}

void union_set(int *parent, int *rankv, int a, int b) {
    a = find_set(parent, a); // líder de a
    b = find_set(parent, b); // líder de b
    if (a == b) return; // já no mesmo conjunto

    if (*(rankv + a) < *(rankv + b)) *(parent + a) = b; // anexa a em b
    else if (*(rankv + a) > *(rankv + b)) *(parent + b) = a; // anexa b em a
    else {
        *(parent + b) = a; // anexa b em a
        *(rankv + a) += 1; // aumenta rank
    }
}

int main() {
    int M, N; // M = número de cidades, N = número de caminhos

    while (scanf("%d %d", &M, &N) == 2) {
        if (M == 0 && N == 0) break; // fim da entrada

        // aloca vetor de arestas dinamicamente
        Edge *edges = (Edge*) malloc(N * sizeof(Edge)); // N arestas
        if (edges == NULL) return 0; // falha alocação (defensivo)

        int i;
        for (i = 0; i < N; i++) {
            int x, y, z;
            scanf("%d %d %d", &x, &y, &z); // lê aresta
            edges[i].u = x; // vértice X
            edges[i].v = y; // vértice Y
            edges[i].w = z; // peso Z
        }

        // ordena arestas por peso
        qsort(edges, N, sizeof(Edge), cmpEdge);

        // prepara Union-Find
        int *parent = (int*) malloc(M * sizeof(int)); // pai de cada vértice
        int *rankv  = (int*) calloc(M, sizeof(int));  // rank de cada vértice
        if (parent == NULL || rankv == NULL) return 0; // segurança

        for (i = 0; i < M; i++) *(parent + i) = i; // cada nó é seu próprio pai

        // Kruskal
        ll total = 0; // soma das arestas da MST
        int used = 0; // arestas usadas na MST

        for (i = 0; i < N && used < M - 1; i++) {
            int u = edges[i].u;
            int v = edges[i].v;
            int pu = find_set(parent, u);
            int pv = find_set(parent, v);

            if (pu != pv) { // se não cria ciclo
                union_set(parent, rankv, pu, pv); // une conjuntos
                total += (ll) edges[i].w; // adiciona peso
                used++; // conta aresta usada
            }
        }

        // imprime resultado
        printf("%lld\n", total);

        // libera memória
        free(edges); // libera vetor de arestas
        free(parent); // libera parent
        free(rankv); // libera rank
    }

    return 0; // fim do programa
}
