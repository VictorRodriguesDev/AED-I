#include <stdio.h>
#include <stdlib.h>

/* nó da lista de adjacência */
typedef struct node {
    int v; // vértice
    struct node *next; // próximo
} Node;

/* cria grafo com n listas vazias */
Node** createGraph(int n) {
    Node **g = (Node**) malloc(n * sizeof(Node*));
    for (int i = 0; i < n; i++) *(g + i) = NULL;
    return g;
}

/* adiciona aresta não direcionada a <-> b */
void addEdge(Node **g, int a, int b) {
    Node *p = (Node*) malloc(sizeof(Node));
    p->v = b;
    p->next = *(g + a);
    *(g + a) = p;

    Node *q = (Node*) malloc(sizeof(Node));
    q->v = a;
    q->next = *(g + b);
    *(g + b) = q;
}

/* ordena inteiros por selection sort (usando ponteiros) */
void sortInts(int *arr, int sz) {
    for (int i = 0; i < sz - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < sz; j++) {
            if (*(arr + j) < *(arr + minIdx)) minIdx = j;
        }
        if (minIdx != i) {
            int tmp = *(arr + i);
            *(arr + i) = *(arr + minIdx);
            *(arr + minIdx) = tmp;
        }
    }
}

int main() {
    int T;
    if (scanf("%d", &T) != 1) return 0;

    for (int caso = 1; caso <= T; caso++) {
        int n, m;
        scanf("%d %d", &n, &m);

        Node **graph = createGraph(n);

        for (int i = 0; i < m; i++) {
            char ca, cb;
            scanf(" %c %c", &ca, &cb);
            int u = ca - 'a';
            int v = cb - 'a';
            addEdge(graph, u, v);
        }

        int *vis = (int*) calloc(n, sizeof(int)); // visitados
        int *stack = (int*) malloc(n * sizeof(int)); // pilha para DFS
        int *comp = (int*) malloc(n * sizeof(int)); // armazena vértices de um componente

        printf("Case #%d:\n", caso);

        int components = 0;

        for (int i = 0; i < n; i++) {
            if (*(vis + i)) continue;

            // inicia DFS iterativa para coletar componente
            int top = 0;
            *(stack + top) = i;
            top++;
            *(vis + i) = 1;

            int compSize = 0;

            while (top > 0) {
                top--;
                int u = *(stack + top);

                // guarda no componente
                *(comp + compSize) = u;
                compSize++;

                // percorre vizinhos
                Node *p = *(graph + u);
                while (p != NULL) {
                    int w = p->v;
                    if (!*(vis + w)) {
                        *(vis + w) = 1;
                        *(stack + top) = w;
                        top++;
                    }
                    p = p->next;
                }
            }

            // ordena os vértices do componente e imprime no formato requerido
            sortInts(comp, compSize);
            for (int k = 0; k < compSize; k++) {
                printf("%c,", 'a' + *(comp + k)); // nota: vírgula SEM espaço
            }
            printf("\n");

            components++;
        }

        printf("%d connected components\n\n", components); // linha em branco após cada caso

        // libera memória do grafo
        for (int v = 0; v < n; v++) {
            Node *p = *(graph + v);
            while (p != NULL) {
                Node *tmp = p;
                p = p->next;
                free(tmp);
            }
        }
        free(graph);
        free(vis);
        free(stack);
        free(comp);
    }

    return 0;
}
