#include <stdio.h>
#include <stdlib.h>

// nó da pilha
typedef struct cel {
    int value;
    struct cel *next;
} cel;

// empilha elemento
void push(cel **top, int x) {
    cel *p = malloc(sizeof(cel)); // cria nó
    p->value = x; // guarda valor
    p->next = *top; // liga nó
    *top = p; //guarda o topo
}

// desempilha elemento
void pop(cel **top) {
    cel *p = *top; // nó atual
    *top = p->next; // move topo
    free(p); // libera memória
}

int main() {
    int n; // quantidade de trens

    while (1) {
        scanf("%d", &n); // lê n
        if (n == 0) break; // fim

        while (1) {
            int first;
            scanf("%d", &first); // lê primeiro da sequência

            if (first == 0) { // fim do bloco
                printf("\n");
                break;
            }

            int *seq = malloc(n * sizeof(int)); // guarda sequência
            seq[0] = first;

            for (int i = 1; i < n; i++) scanf("%d", &seq[i]); // lê o resto

            cel *stack = NULL; // pilha
            int next = 1; // próximo trem de entrada
            int ok = 1; // controla se é possível

            for (int i = 0; i < n; i++) {
                int x = seq[i];

                while (next <= x) { // empilha até chegar no desejado
                    push(&stack, next);
                    next++;
                }
                if (stack->value == x) { // topo é o desejado
                    pop(&stack);
                } else {
                    ok = 0; // impossível
                    break;
                }
            }
            // limpeza
            while (stack != NULL) pop(&stack);
            free(seq);

            if (ok) printf("Yes\n");
            else    printf("No\n");
        }
    }

    return 0;
}
