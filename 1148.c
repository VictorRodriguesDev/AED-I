#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct adj {
    int v, w;
    struct adj *next;
} Adj;

typedef struct {
    Adj **lista;
    int n;
} Grafo;

Adj* novoAdj(int v, int w) {
    Adj *no = (Adj*) malloc(sizeof(Adj));
    no->v = v;
    no->w = w;
    no->next = NULL;
    return no;
}

Grafo* criaGrafo(int n) {
    Grafo *g = (Grafo*) malloc(sizeof(Grafo));
    g->n = n;
    g->lista = (Adj**) malloc(n * sizeof(Adj*));

    for (int i = 0; i < n; i++)
        g->lista[i] = NULL;

    return g;
}

void addAresta(Grafo *g, int u, int v, int w) {
    Adj *no = novoAdj(v, w);
    no->next = g->lista[u];
    g->lista[u] = no;
}

int bellmanFord(Grafo *g, int origem, int destino) {
    int n = g->n;
    int *dist = (int*) malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
        dist[i] = INT_MAX;

    dist[origem] = 0;

    // Relaxa N - 1 vezes
    for (int k = 0; k < n - 1; k++) {
        int mudou = 0;

        for (int u = 0; u < n; u++) {
            if (dist[u] == INT_MAX) continue;

            Adj *p = g->lista[u];
            while (p != NULL) {
                int v = p->v;
                int w = p->w;

                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    mudou = 1;
                }
                p = p->next;
            }
        }

        // Se não houve mudanças, pode parar cedo
        if (!mudou) break;
    }

    int resposta = dist[destino];
    free(dist);

    return resposta;
}

int main() {
    int N, E;

    while (1) {
        scanf("%d %d", &N, &E);
        if (N == 0 && E == 0) break;

        Grafo *g = criaGrafo(N);

        for (int i = 0; i < E; i++) {
            int X, Y, H;
            scanf("%d %d %d", &X, &Y, &H);
            X--; Y--;

            int reciproco = 0;

            // checa se já existe aresta (Y->X)
            for (Adj *p = g->lista[Y]; p != NULL; p = p->next)
                if (p->v == X)
                    reciproco = 1;

            if (reciproco) {
                addAresta(g, X, Y, 0);
                addAresta(g, Y, X, 0);
            } else {
                addAresta(g, X, Y, H);
            }
        }

        int K;
        scanf("%d", &K);

        while (K--) {
            int X, Y;
            scanf("%d %d", &X, &Y);
            X--; Y--;

            int r = bellmanFord(g, X, Y);

            if (r == INT_MAX)
                printf("Nao e possivel entregar a carta\n");
            else
                printf("%d\n", r);
        }

        printf("\n");

        // libera memória
        for (int i = 0; i < N; i++) {
            Adj *p = g->lista[i];
            while (p != NULL) {
                Adj *tmp = p;
                p = p->next;
                free(tmp);
            }
        }

        free(g->lista);
        free(g);
    }

    return 0;
}
