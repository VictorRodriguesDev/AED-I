#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF 2000000000

typedef struct {
    int to, w;
    struct Edge *next;
} Edge;

Edge *adj[2505]; // lista de adjacência

// adiciona aresta dirigida
void addEdge(int u, int v, int w) {
    Edge *e = malloc(sizeof(Edge)); // aloca nó da aresta
    e->to = v; // destino
    e->w = w; // peso
    e->next = adj[u]; // liga na lista
    adj[u] = e; // atualiza lista
}

int dijkstra(int N, int start, int target) {
    int *dist = malloc((N+1)*sizeof(int)); // vetor de distâncias
    int *vis = malloc((N+1)*sizeof(int)); // vetor de visitados

    for (int i = 0; i <= N; i++) {
        dist[i] = INF; // inicia distância infinita
        vis[i] = 0; // marca como não visitado
    }

    dist[start] = 0; // origem distância zero

    for (int i = 0; i < N; i++) {

        int u = -1, best = INF;

        for (int j = 0; j <= N; j++) {
            if (!vis[j] && dist[j] < best) { // encontra menor distância
                best = dist[j];
                u = j;
            }
        }

        if (u == -1) break; // nenhum alcançável
        vis[u] = 1; // marca visitado

        if (u == target) break; // já chegou

        for (Edge *e = adj[u]; e; e = e->next) {
            int v = e->to;
            if (dist[v] > dist[u] + e->w) dist[v] = dist[u] + e->w; // relaxação
        }
    }

    int ans = dist[target]; // armazena resposta

    free(dist); // libera distâncias
    free(vis); // libera visitados

    return ans;
}

int main() {
    int N, M, C, K;

    while (1) {
        scanf("%d %d %d %d", &N, &M, &C, &K);

        if (N == 0 && M == 0 && C == 0 && K == 0) return 0; // fim

        for (int i = 0; i <= N; i++) adj[i] = NULL; // limpa listas

        for (int i = 0; i < M; i++) {
            int u, v, p;
            scanf("%d %d %d", &u, &v, &p);

            if (u < C && v < C) {
                // ambas especiais
                if (u + 1 == v) addEdge(u, v, p); // direção obrigatória
                if (v + 1 == u) addEdge(v, u, p); // sentido reverso permitido
            }
            else if (u < C && v >= C) {
                addEdge(v, u, p); // normal -> especial (permitido)
            }
            else if (v < C && u >= C) {
                addEdge(u, v, p); // normal -> especial
            }
            else {
                addEdge(u, v, p); // normais: bidirecional
                addEdge(v, u, p);
            }
        }

        int result = dijkstra(N, K, C-1); // pesquisa menor caminho

        printf("%d\n", result); // imprime resposta
    }

    return 0;
}
