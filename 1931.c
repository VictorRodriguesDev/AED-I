#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int v, peso;
    struct Node *next;
} Node;

void addEdge(Node **grafo, int u, int v, int w) {
    Node *novo = (Node *)malloc(sizeof(Node));
    novo->v = v; 
    novo->peso = w;
    novo->next = grafo[u];
    grafo[u] = novo;
}

typedef struct {
    int node, dist, paridade;
} HeapNode;

void swap(HeapNode *a, HeapNode *b) {
    HeapNode tmp = *a; 
    *a = *b; 
    *b = tmp;
}

void heapUp(HeapNode heap[], int idx) {
    while (idx > 1 && heap[idx].dist < heap[idx/2].dist) {
        swap(&heap[idx], &heap[idx/2]); 
        idx /= 2;
    }
}

void heapDown(HeapNode heap[], int size, int idx) {
    int menor = idx;

    int left = idx * 2;
    if (left <= size && heap[left].dist < heap[menor].dist)
        menor = left;

    int right = idx * 2 + 1;
    if (right <= size && heap[right].dist < heap[menor].dist)
        menor = right;

    if (menor != idx) {
        swap(&heap[idx], &heap[menor]); 
        heapDown(heap, size, menor);
    }
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    Node **grafo = (Node **)calloc(N + 1, sizeof(Node *)); // lista de adj
    int i;

    for (i = 0; i < M; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        addEdge(grafo, u, v, w); // adiciona aresta u->v
        addEdge(grafo, v, u, w); // adiciona aresta v->u
    }

    int dist[N + 1][2]; // distâncias por paridade (0=par, 1=ímpar)
    for (i = 1; i <= N; i++) {
        dist[i][0] = INT_MAX;
        dist[i][1] = INT_MAX;
    }

    dist[1][0] = 0; // começa na cidade 1 com paridade 0 (0 arestas)

    HeapNode *heap = (HeapNode *)malloc(sizeof(HeapNode) * (2000000));
    int heapSize = 0;

    heap[++heapSize] = (HeapNode){1, 0, 0}; // empilha origem
    heapUp(heap, heapSize);

    while (heapSize > 0) {
        HeapNode top = heap[1];
        heap[1] = heap[heapSize--];
        heapDown(heap, heapSize, 1);

        int u = top.node;
        int du = top.dist;
        int pu = top.paridade;

        if (du > dist[u][pu]) continue; // descarta pior caminho

        Node *ptr = grafo[u];
        while (ptr != NULL) {
            int v = ptr->v;
            int w = ptr->peso;

            int novaParidade = pu ^ 1; // alterna paridade

            if (du + w < dist[v][novaParidade]) {
                dist[v][novaParidade] = du + w;

                heap[++heapSize] = (HeapNode){v, dist[v][novaParidade], novaParidade}; // empilha v
                heapUp(heap, heapSize);
            }

            ptr = ptr->next;
        }
    }

    if (dist[N][0] == INT_MAX)
        printf("-1\n"); // sem caminho de paridade par
    else
        printf("%d\n", dist[N][0]); // menor caminho válido

    for (i = 1; i <= N; i++) {
        Node *ptr = grafo[i];
        while (ptr) {
            Node *tmp = ptr;
            ptr = ptr->next;
            free(tmp); // libera lista
        }
    }

    free(grafo); // libera grafo
    free(heap);  // libera heap

    return 0;
}
