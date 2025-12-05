#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int v; // vértice armazenado
    struct node *next; // ponteiro para próximo da lista
} Node;

Node** createGraph(int n) {
    Node **g = (Node**) malloc(n * sizeof(Node*)); // vetor de ponteiros
    for (int i = 0; i < n; i++)
        g[i] = NULL; // inicializa listas vazias
    return g;
}

void addEdge(Node **g, int a, int b) {
    Node *n1 = (Node*) malloc(sizeof(Node)); // nó da lista
    n1->v = b; //
    n1->next = g[a]; //
    g[a] = n1; //

    Node *n2 = (Node*) malloc(sizeof(Node)); // grafo não direcionado
    n2->v = a; //
    n2->next = g[b]; //
    g[b] = n2; //
}

void dfs(Node **g, int u, int *visited, int *count) {
    visited[u] = 1; // marca como visitado
    Node *p = g[u]; // percorre vizinhos

    while (p != NULL) {
        if (!visited[p->v]) { //
            *count += 2; // ida + volta
            dfs(g, p->v, visited, count); //
        }
        p = p->next; //
    }
}

int main() {
    int t; // número de casos
    scanf("%d", &t); //

    while (t--) {
        int start, n, e; //
        scanf("%d", &start); //
        scanf("%d %d", &n, &e); //

        Node **graph = createGraph(n); // cria grafo
        int *visited = (int*) calloc(n, sizeof(int)); // vetor de visitados

        for (int i = 0; i < e; i++) {
            int a, b; //
            scanf("%d %d", &a, &b); //
            addEdge(graph, a, b); //
        }

        int count = 0; //
        dfs(graph, start, visited, &count); //
        printf("%d\n", count); //

        // libera memória
        for (int i = 0; i < n; i++) {
            Node *p = graph[i]; //
            while (p != NULL) {
                Node *tmp = p; //
                p = p->next; //
                free(tmp); //
            }
        }
        free(graph); //
        free(visited); //
    }

    return 0; //
}
