#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;   // área de dados
    int top;     // índice do topo (-1 se vazia)
} Stack;

Stack* createStack(int cap) {
    Stack *s = malloc(sizeof(Stack));
    s->data = malloc(cap * sizeof(int));
    s->top = -1;
    return s;
}

void freeStack(Stack *s) {
    free(s->data);
    free(s);
}

int emptyStack(Stack *s) {
    return s->top < 0;
}

void pushStack(Stack *s, int x) {
    s->top++;
    s->data[s->top] = x;
}

int topStack(Stack *s) {
    return s->data[s->top];
}

void popStack(Stack *s) {
    if (!emptyStack(s)) s->top--;
}

typedef struct {
    int *data; // área de dados
    int front; // índice do elemento da frente
    int rear; // índice livre para inserir (posição seguinte ao último)
    int size; // número de elementos
    int cap; // capacidade
} Queue;

Queue* createQueue(int cap) {
    Queue *q = malloc(sizeof(Queue));
    q->data = malloc(cap * sizeof(int));
    q->front = 0;
    q->rear = 0;
    q->size = 0;
    q->cap = cap;
    return q;
}

void freeQueue(Queue *q) {
    free(q->data);
    free(q);
}

int emptyQueue(Queue *q) {
    return q->size == 0;
}

void pushQueue(Queue *q, int x) {
    if (q->size < q->cap) {
        q->data[q->rear] = x;
        q->rear = (q->rear + 1) % q->cap;
        q->size++;
    }
}

int frontQueue(Queue *q) {
    return q->data[q->front];
}

void popQueue(Queue *q) {
    if (!emptyQueue(q)) {
        q->front = (q->front + 1) % q->cap;
        q->size--;
    }
}

typedef struct {
    int *data;   // array do heap
    int size;    // número de elementos
    int cap;     // capacidade
} Heap;

Heap* createHeap(int cap) {
    Heap *h = malloc(sizeof(Heap));
    h->data = malloc(cap * sizeof(int));
    h->size = 0;
    h->cap = cap;
    return h;
}

void freeHeap(Heap *h) {
    free(h->data);
    free(h);
}

int emptyHeap(Heap *h) {
    return h->size == 0;
}

void pushHeap(Heap *h, int x) {
    if (h->size >= h->cap) return;
    int i = h->size++;
    h->data[i] = x;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (h->data[p] >= h->data[i]) break;
        int tmp = h->data[p];
        h->data[p] = h->data[i];
        h->data[i] = tmp;
        i = p;
    }
}

int topHeap(Heap *h) {
    return h->data[0];
}

void popHeap(Heap *h) {
    if (h->size == 0) return;
    h->size--;
    if (h->size == 0) return;
    h->data[0] = h->data[h->size];
    int i = 0;
    while (1) {
        int l = 2*i + 1;
        int r = 2*i + 2;
        int largest = i;
        if (l < h->size && h->data[l] > h->data[largest]) largest = l;
        if (r < h->size && h->data[r] > h->data[largest]) largest = r;
        if (largest == i) break;
        int tmp = h->data[i];
        h->data[i] = h->data[largest];
        h->data[largest] = tmp;
        i = largest;
    }
}

int main() {
    int n;

    while (scanf("%d", &n) != EOF) {
        // cria estruturas com capacidade n (n operações é suficiente)
        Stack *s = createStack(n);
        Queue *q = createQueue(n);
        Heap  *h = createHeap(n);

        int isStack = 1, isQueue = 1, isHeap = 1;

        for (int i = 0; i < n; i++) {
            int op, x;
            if (scanf("%d %d", &op, &x) != 2) { // segurança de leitura
                op = 0; x = 0;
            }

            if (op == 1) {
                // inserir nas estruturas (sempre inserir)
                if (isStack) pushStack(s, x);
                else {
                    // mesmo se já impossível, manter estado consistente:
                    // podemos optar por não executar push para economia,
                    // mas não é necessário; deixo sem push.
                }

                if (isQueue) pushQueue(q, x);
                if (isHeap) pushHeap(h, x);
            } else {
                // remoção: validar cada estrutura somente se ainda possível
                if (isStack) {
                    if (emptyStack(s) || topStack(s) != x) {
                        isStack = 0; // marca impossível e para validar pilha
                    } else {
                        popStack(s); // remove corretamente
                    }
                }if (isQueue) {
                    if (emptyQueue(q) || frontQueue(q) != x) {
                        isQueue = 0; // marca impossível
                    } else {
                        popQueue(q); // remove corretamente
                    }
                }if (isHeap) {
                    if (emptyHeap(h) || topHeap(h) != x) {
                        isHeap = 0; // marca impossível
                    } else {
                        popHeap(h); // remove corretamente
                    }
                }
            }
        }

        int sum = isStack + isQueue + isHeap;
        if (sum == 0) printf("impossible\n");
        else if (sum > 1) printf("not sure\n");
        else if (isStack) printf("stack\n");
        else if (isQueue) printf("queue\n");
        else printf("priority queue\n");

        // libera memória
        freeStack(s);
        freeQueue(q);
        freeHeap(h);
    }

    return 0;
}