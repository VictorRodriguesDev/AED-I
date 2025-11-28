#include <stdio.h>
#include <stdlib.h>

// estrutura do nó da fila
typedef struct node {
    int value; // valor da carta
    struct node *next; // próximo nó
} Node;

// insere no final da fila
void enqueue(Node **front, Node **rear, int value) {
    Node *newNode = (Node*) malloc(sizeof(Node)); // cria novo nó
    newNode->value = value; // define valor
    newNode->next = NULL; // próximo é NULL

    if (*rear == NULL) { // fila vazia
        *front = newNode; // frente aponta para novo nó
        *rear = newNode; // traseira aponta para novo nó
    } else {
        (*rear)->next = newNode; // liga último ao novo
        *rear = newNode; // atualiza traseira
    }
}

// remove do início da fila
int dequeue(Node **front, Node **rear) {
    if (*front == NULL) return -1; // fila vazia

    Node *temp = *front; // nó a ser removido
    int value = temp->value; // captura valor
    *front = temp->next; // avança ponteiro frente

    if (*front == NULL) { // se fila ficou vazia
        *rear = NULL; // traseira vira NULL
    }

    free(temp); // libera nó removido
    return value; // retorna carta removida
}

int main() {
    int n; // número de cartas

    while (scanf("%d", &n) && n != 0) { // lê até n = 0
        Node *front = NULL; // frente da fila
        Node *rear = NULL; // traseira da fila

        for (int i = 1; i <= n; i++) { // insere cartas
            enqueue(&front, &rear, i); // insere carta na fila
        }

        printf("Discarded cards:"); // título das descartadas

        while (front != rear) { // enquanto houver mais de 1 carta
            int discarded = dequeue(&front, &rear); // descarta carta
            printf(" %d", discarded); // imprime descartada

            if (front != rear) { // se ainda não for a última
                printf(","); // coloca vírgula entre valores
            }

            int move = dequeue(&front, &rear); // pega carta do topo
            enqueue(&front, &rear, move); // devolve para o final
        }

        printf("\nRemaining card: %d\n", front->value); // imprime última carta

        free(front); // libera último nó
    }

    return 0; // fim do programa
}
