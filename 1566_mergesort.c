#include <stdio.h>
#include <stdlib.h>

/* Combina duas metades ordenadas: v[l..m] e v[m+1..r] */
void merge(int *v, int l, int m, int r) {
    int i = l; // ponteiro da metade esquerda
    int j = m + 1; // ponteiro da metade direita
    int k = 0; // índice do vetor auxiliar

    int tam = r - l + 1; // tamanho do bloco
    int *aux = malloc(tam * sizeof(int));

    while (i <= m && j <= r) {
        if (*(v + i) <= *(v + j)) {
            *(aux + k) = *(v + i);
            i++;
        } else {
            *(aux + k) = *(v + j);
            j++;
        }
        k++;
    }

    while (i <= m) {
        *(aux + k) = *(v + i);
        i++;
        k++;
    }

    while (j <= r) {
        *(aux + k) = *(v + j);
        j++;
        k++;
    }

    /* copia de volta para o vetor original */
    for (i = 0; i < tam; i++) {
        *(v + l + i) = *(aux + i);
    }

    free(aux);
}

void mergeSort(int *v, int l, int r) {
    if (l >= r) return;

    int m = (l + r) / 2;

    mergeSort(v, l, m); // ordena metade esquerda
    mergeSort(v, m + 1, r); // ordena metade direita
    merge(v, l, m, r); // intercala
}

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        int n;
        scanf("%d", &n);

        int *alturas = malloc(n * sizeof(int));

        for (int i = 0; i < n; i++) {
            scanf("%d", (alturas + i));
        }

        mergeSort(alturas, 0, n - 1);

        for (int i = 0; i < n; i++) {
            printf("%d", *(alturas + i));
            if (i < n - 1) printf(" ");
        }
        printf("\n");

        free(alturas);
    }

    return 0;
}
