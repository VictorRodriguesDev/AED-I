#include <stdio.h>
#include <stdlib.h>

int main() {
    int n; 
    scanf("%d", &n); // quantidade inicial

    int *fila = malloc(n * sizeof(int)); // ponteiro para fila
    int *p = fila; // cursor na fila

    // leitura usando ponteiros
    for (int i = 0; i < n; i++) {
        scanf("%d", (p + i)); // *(p + i) recebe valor
    }

    int r;
    scanf("%d", &r); // quantidade de removidos

    int *rem = malloc(r * sizeof(int)); // ponteiro para removidos
    int *q = rem; // cursor dos removidos

    // leitura dos removidos usando ponteiros
    for (int i = 0; i < r; i++) {
        scanf("%d", (q + i));
    }

    int first = 1; // controla espaços

    // percorre fila usando ponteiros
    for (int i = 0; i < n; i++) {
        int x = *(p + i); // pega aluno atual
        int drop = 0; // marca se deve remover

        // verifica se x está em rem
        for (int j = 0; j < r; j++) {
            if (x == *(q + j)) { // compara por ponteiros
                drop = 1;
                break;
            }
        }

        if (!drop) { // se não deve remover
            if (!first) printf(" "); // adiciona espaço
            printf("%d", x); // imprime aluno
            first = 0;
        }
    }

    printf("\n");

    free(fila); // libera fila
    free(rem);  // libera removidos

    return 0;
}
