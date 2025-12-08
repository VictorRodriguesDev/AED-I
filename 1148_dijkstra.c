#include <stdio.h>
#include <stdlib.h>

#define INF 1000000000

int w[505][505];
int dist[505];
int vis[505];
int N;

// Dijkstra simples
int dijkstra(int O, int D) {
    for (int i = 1; i <= N; i++) {
        dist[i] = INF; //inicia distancia
        vis[i] = 0; //não visitado
    }
    dist[O] = 0; 

    for (int i = 1; i <= N; i++) {
        int u = -1, best = INF;

        for (int j = 1; j <= N; j++) {
            if (!vis[j] && dist[j] < best) { //acha menor nó
                best = dist[j];
                u = j;
            }
        }

        if (u == -1) break;
        vis[u] = 1;

        for (int v = 1; v <= N; v++) {
            if (w[u][v] < INF) { //se há aresta
                if (dist[v] > dist[u] + w[u][v])
                    dist[v] = dist[u] + w[u][v];
            }
        }
    }

    return dist[D];
}

int main() {
    int E;

    while (1) {
        scanf("%d %d", &N, &E);

        if (N == 0 && E == 0) break;

        // inicializa matriz de pesos
        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= N; j++)
                w[i][j] = INF; //sem aresta

        // lê acordos
        while (E--) {
            int X, Y, H;
            scanf("%d %d %d", &X, &Y, &H);

            if (w[Y][X] != INF) { //existe inversa
                w[X][Y] = 0;
                w[Y][X] = 0; 
            } else {
                w[X][Y] = H; //normal
            }
        }

        int K;
        scanf("%d", &K);

        while (K--) {
            int O, D;
            scanf("%d %d", &O, &D);

            int r = dijkstra(O, D); //calcula caminho

            if (r >= INF)
                printf("Nao e possivel entregar a carta\n");
            else
                printf("%d\n", r);
        }

        printf("\n"); //linha em branco
    }

    return 0;
}
